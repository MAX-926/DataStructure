//pushNode(chainNode<T>* theNode),该方法把节点theNode压入栈
//popNode()把栈顶节点删除并返回

#include"../case/8-1.h"
#include"../../Tool.h"
#include"E:\DataStructure\ch6\case\6-1.h"
#include<time.h>

// template<class T>
// struct chainNode
// {
//     chainNode(const T& theElement, chainNode<T>* theNext = nullptr):element(theElement), next(theNext){}
//     T element;
//     chainNode<T>* next;
// };

template<class T>
class linkedStack:public stack<T>
{
    public:
        //constructor and destructor
        linkedStack(int initialCapacity = 10):stackTop(nullptr), stackSize(0){}
        ~linkedStack()
        {
            while(stackTop != nullptr)
            {
                chainNode<T>* nextNode = stackTop->next;
                delete stackTop;
                stackTop = nextNode;
            }
        }
        //ADT methods:
        bool empty()const{return stackSize == 0;}
        int size()const{return stackSize;}
        T& top()
        {
            if(stackSize == 0)
                throw stackEmpty();
            return stackTop->element;
        }
        void pop()
        {
            if(stackSize == 0)
                throw stackEmpty();
            chainNode<T>* nextNode = stackTop->next;
            delete stackTop;//调用析构函数
            stackTop = nextNode;
            --stackSize;
        }
        void push(const T& theElement)
        {
            stackTop = new chainNode<T>(theElement, stackTop);//分配内存，调用构造函数
            ++stackSize;
        }
        void pushNode(chainNode<T>* theNode)
        {//theNode 须是堆上创建的，不能是局部变量
            if(theNode == nullptr)
                return;
            theNode->next = stackTop;
            stackTop = theNode;
            ++stackSize;
        }
        chainNode<T>& popNode()
        {
            if(stackSize == 0)
                throw stackEmpty();
            chainNode<T>* pNode = stackTop;
            stackTop = stackTop->next;
            --stackSize;
            //防止用户通过pNode污染linkedStack
            pNode->next = nullptr;
            return *pNode;//不对删除的节点调用析构函数
        }
    private:
        chainNode<T>* stackTop;
        int stackSize;
};

// int main()
// {
//     time_t clocksPerMillions = CLOCKS_PER_SEC/1000;
//     time_t startTime;
//     long int n = 10000000;
//     cout << "it's a test on 10 000 000-list operation\n";
//     cout << "n" << "\t" << "time cost\n";
//     linkedStack<int> test;
//     startTime = clock();
//     for(int i = 0; i < 10000000; i++)
//     {
//         chainNode<int>* cn = new chainNode<int>(0);
//         test.pushNode(cn);
//         // test.push(i);
//     }
//     for(int i = 0; i < 10000000; i++)
//     {
//         test.top();
//         test.popNode();
//         // test.pop();
//     }
//     time_t endTime = clock();
//     double totalTiks = (double)(endTime - startTime);
//     double timeCost = totalTiks/clocksPerMillions;
//     cout << n << "\t" << timeCost << endl;
// }

/*
push, pop and top
it's a test on 10 000 000-list operation
n       time cost
10000000        167517

pushNode, popNode and top
it's a test on 10 000 000-list operation
n       time cost
10000000        7815
*/

// int main()
// {
//     linkedStack<int> ls;
//     chainNode<int>* cn1 = new chainNode<int>(26);
//     chainNode<int>* cn2 = new chainNode<int>(27);
//     chainNode<int>* cn3 = new chainNode<int>(28);

//     for(int i = 0; i < 5; i++)
//        ls.push(i);
//     // linkedStack<int> lsCpy(ls);
//     ls.pushNode(cn1);
//     ls.pushNode(cn2);
//     ls.pushNode(cn3);

//     ls.popNode();
//     ls.popNode();
//     ls.popNode();
//     for(int i = 0; i < 5; i++)
//     {
//         cout << ls.top() << endl;
//         ls.pop();
//     }   
// }