#include"../case/linkedQueue.cpp"
#include"../case/9-1.h"

template<class T>
class extendedLinkedQueue;
template<class T>
class extendedQueueL:public queue<T>
{
    public:
        virtual ~extendedQueueL(){}
        //NEW methods:
        //5.1）
        //i：输入一个队列
        // virtual void inputQueue() = 0;
        //ii：输出一个队列
        virtual void outputQueue()const = 0;
        //iii:把一个队列分解成两个新队列，一个队列包含原来的1,3,5...个元素，另一个队列包含其余的元素
        virtual void split(extendedLinkedQueue<T>& A, extendedLinkedQueue<T>& b) = 0;
        //iv:把两个队列合并成一个新队列。从队列1开始，轮流从两个队列选择元素插入新队列。若某个队列空了，则将另一个队列中的剩余元素插入新队列。合并前后，每一个队列的元素相对顺序不变。
        virtual void merge(extendedLinkedQueue<T>& a, extendedLinkedQueue<T>& b) = 0;
};

template<class T>
class extendedLinkedQueue:public extendedQueueL<T>, public linkedQueue<T>
{
    public:
        //constructor, copy-constructor and destructor
        extendedLinkedQueue():extendedQueueL<T>(), linkedQueue<T>(){}
        extendedLinkedQueue(extendedLinkedQueue<T>& elq):linkedQueue<T>(elq){}
        virtual ~extendedLinkedQueue(){}
        //ADT methods:
        bool empty()const{return linkedQueue<T>::queueSize == 0;}
        int size()const{return linkedQueue<T>::queueSize;}
        T& front(){if(linkedQueue<T>::queueSize == 0) throw queueEmpty(); return linkedQueue<T>::queueFront->data;}
        T& back(){if(linkedQueue<T>::queueSize == 0) throw queueEmpty(); return linkedQueue<T>::queueBack->data;}
        void push(const T& theElement);
        void pop();
        void outputQueue()const;
        void split(extendedLinkedQueue<T>&, extendedLinkedQueue<T>&);
        void merge(extendedLinkedQueue<T>&, extendedLinkedQueue<T>&);
};

template<class T>
void extendedLinkedQueue<T>::push(const T& theElement)
{
    chainNode<T>* newNode = new chainNode<T>(theElement);
    if(linkedQueue<T>::queueFront == nullptr)
        linkedQueue<T>::queueFront = newNode;
    else
        linkedQueue<T>::queueBack->next = newNode;
    linkedQueue<T>::queueBack = newNode;
    linkedQueue<T>::queueSize++;       
}

template<class T>
void extendedLinkedQueue<T>::pop()
{
    if(linkedQueue<T>::queueSize == 0)
        throw queueEmpty();
    chainNode<T>* nextNode = linkedQueue<T>::queueFront->next;
    delete linkedQueue<T>::queueFront;
    linkedQueue<T>::queueFront = nextNode; 
    linkedQueue<T>::queueSize--;
}

template<class T>
void extendedLinkedQueue<T>::outputQueue()const
{//从队首打印到队尾
    if(linkedQueue<T>::queueSize == 0)
    {
        cout << "Empty queue\n";
        return;
    }
    chainNode<T>* iter = linkedQueue<T>::queueFront;
    while(iter != nullptr)
    {
        cout << iter->data << " ";
        iter = iter->next;
    }
    cout << "output complete" << endl;
}
template<class T>
void extendedLinkedQueue<T>::split(extendedLinkedQueue<T>& a, extendedLinkedQueue<T>& b)
{//原地拆分，不产生新节点
    //初始化工作：清空a，b队列
    a.clear();
    b.clear();
    //如果源列表为空，则直接返回
    if(linkedQueue<T>::queueFront == nullptr)
    {
        cout << "source queue is empty\n";
        return;
    }
    
    chainNode<T>* iter = linkedQueue<T>::queueFront;

    a.queueFront = iter;
    a.queueSize++;
    //若源列表只有一个元素，直接返回
    if(iter->next == nullptr)
        return;
    
    iter = iter->next;
    b.queueFront = iter;
    b.queueSize++;

    //此时iter指向源列表第3个元素
    iter = iter->next;

    chainNode<T>* iterA = a.queueFront;
    chainNode<T>* iterB = b.queueFront;
    bool tag = true;
    while(iter != nullptr)
    {
        if(tag)
        {//奇数序号的元素加入队列a
            iterA->next = iter;
            iter = iter->next;
            a.queueSize++;
            iterA = iterA->next;
            tag = false;
        }
        else
        {//偶数序号的元素加入队列b
            iterB->next = iter;
            iter = iter->next;
            b.queueSize++;
            iterB = iterB->next;
            tag = true;
        }
    }
    iterA->next = nullptr;
    iterB->next = nullptr;
    a.queueBack = iterA;
    b.queueBack = iterB;

    //初始化源列表的状态
    linkedQueue<T>::queueSize = 0;
    linkedQueue<T>::queueFront = nullptr;
    linkedQueue<T>::queueBack = nullptr;
    return;
}

template<class T>
void extendedLinkedQueue<T>::merge(extendedLinkedQueue<T>& a, extendedLinkedQueue<T>& b)
{
    linkedQueue<T>::clear();
    if(a.empty() && b.empty()) return;
    else if(a.empty() && !b.empty())
    {
        linkedQueue<T>::queueSize = b.queueSize;
        linkedQueue<T>::queueFront = b.queueFront;
        linkedQueue<T>::queueBack = b.queueBack;

        b.queueFront = nullptr;
        b.queueBack = nullptr;
        b.queueSize = 0;
        return;
    }
    else if(!a.empty() && b.empty())
    {
        linkedQueue<T>::queueSize = a.queueSize;
        linkedQueue<T>::queueFront = a.queueFront;
        linkedQueue<T>::queueBack = a.queueBack;

        a.queueFront = nullptr;
        a.queueBack = nullptr;
        a.queueSize = 0;
        return;
    }
    else
    {//先a后b，交替加入
        bool tag = false;//true指代序号为奇数时，false指代序号为偶数时
        linkedQueue<T>::queueFront = a.linkedQueue<T>::queueFront;
        // a.linkedQueue<T>::queueFront = a.linkedQueue<T>::queueFront->next;
        a.queueFront = a.queueFront->next;
        chainNode<T>* iter = linkedQueue<T>::queueFront;
        while(a.queueFront != nullptr && b.queueFront != nullptr)
        {
            if(tag)
            {
                iter->next = a.linkedQueue<T>::queueFront;
                a.linkedQueue<T>::queueFront = a.linkedQueue<T>::queueFront->next;
                iter = iter->next;
                tag = false;
            }
            else
            {
                iter->next = b.linkedQueue<T>::queueFront;
                b.linkedQueue<T>::queueFront = b.linkedQueue<T>::queueFront->next;
                iter = iter->next;
                tag = true;
            }
        }
        while(a.linkedQueue<T>::queueFront != nullptr)
        {
            iter->next = a.queueFront;
            a.linkedQueue<T>::queueFront = a.linkedQueue<T>::queueFront->next;
            iter = iter->next;
            if(iter->next == nullptr)
                linkedQueue<T>::queueBack = iter;
        }
        while(b.linkedQueue<T>::queueFront != nullptr)
        {
            iter->next = b.queueFront;
            b.linkedQueue<T>::queueFront = b.linkedQueue<T>::queueFront->next;
            iter = iter->next;
            if(iter->next == nullptr)
                linkedQueue<T>::queueBack = iter;
        }
        linkedQueue<T>::queueSize = a.linkedQueue<T>::queueSize + b.linkedQueue<T>::queueSize;
        a.linkedQueue<T>::queueSize = 0;
        b.linkedQueue<T>::queueSize = 0;
        a.linkedQueue<T>::queueBack = nullptr;
        b.linkedQueue<T>::queueBack = nullptr;
    }
}

// int main()
// {
//     extendedLinkedQueue<int> a, b, c;
//     for(int i = 0 ; i < 9; i++)
//     {
//         a.push(i);
//         // b.push(i);
//         // c.push(i);
//     }
//     for(int i = 0; i < 20; i++)
//     {
//         b.push(i+9);
//     }
//     c.merge(a, b);
//     // c.split(a, b);

//     // for(int i = 0; i < 5; i++)
//     // {
//     //     cout << a.front() << " ";
//     //     a.pop();
//     // }

//     cout << endl;

//     // for(int i = 0; i < 4; i++)
//     // {
//     //     cout << b.front() << " ";
//     //     b.pop();
//     // }

//     // cout << "a.size = " << a.size() << endl << "b.size = " << b.size() << endl;
//     // cout << "c.size = " << c.size() << endl;
//     // cout << c.front();
//     for(int i = 0; i < 29; i++)
//     {
//         cout << c.front() << " ";
//         c.pop();
//     }
// }