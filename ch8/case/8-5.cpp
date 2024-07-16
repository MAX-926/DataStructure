#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

//定制链表栈
//linkedStack
//正如前面的arrayStack一样，脱离继承自链式线性表而得到的链栈有更好的时间性能

#include"8-1.h"
#include"../../Tool.h"
#include<sstream>
#include"E:\DataStructure\ch6\case\6-1.h"
using namespace std;

// template<class T>
// struct chainNode
// {
//     //constructor
//     chainNode(const T& theElement, chainNode<T>* theNext = nullptr):element(theElement), next(theNext){}
//     T element;
//     chainNode<T>* next;
// };

template<class T>
class linkedStack:public stack<T>
{
    public:
        //constructor, copy-constructor and destructor
        linkedStack(int initialCapacity = 10);
        linkedStack(const linkedStack<T>&);
        ~linkedStack();
        //ADT methods:
        bool empty()const{return stackSize == 0;}
        int size()const{return stackSize;}
        T& top();
        void pop();
        void push(const T& theElement);
    protected://如果这个类还会进行派生，可以成员数据的访问控制设置为protected
        int stackSize;//栈中元素个数
        chainNode<T>* stackTop;//栈顶指针
};

template<class T>
linkedStack<T>::linkedStack(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "intialCapacity = " << initialCapacity << " must be > 0"; 
        throw illegalParameter(s.str());
    }
    stackSize = 0;
    stackTop = nullptr;
}

template<class T>
linkedStack<T>::linkedStack(const linkedStack<T>& ls)
{
    stackSize = ls.stackSize;
    chainNode<T>* currentNode = ls.stackTop;
    stackTop = new chainNode<T>(currentNode->element, nullptr);
    chainNode<T>* thisCurrentNode = stackTop;
    currentNode = currentNode->next;
    while(currentNode != nullptr)
    {
        thisCurrentNode->next = new chainNode<T>(currentNode->element, nullptr);
        thisCurrentNode = thisCurrentNode->next;
        currentNode = currentNode->next;
    }
}

template<class T>
linkedStack<T>::~linkedStack()
{
    while(stackTop != nullptr)
    {
        chainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

// template<class T>
// bool linkedStack<T>::empty()const
// {
//     return stackTop == nullptr;
// }

// template<class T>
// int linkedStack<T>::size()const
// {
//     return stackSize;
// }

template<class T>
T& linkedStack<T>::top()
{
    if(stackTop == nullptr)
        throw stackEmpty();
    return stackTop->element;
}

template<class T>
void linkedStack<T>::pop()
{
    if(stackTop == nullptr)
        throw stackEmpty();
    chainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    --stackSize;
}

template<class T>
void linkedStack<T>::push(const T& theElement)
{
    stackTop = new chainNode<T>(theElement, stackTop);
    ++stackSize;
}

#endif //LINKEDSTACK_H
// int main()
// {
//     linkedStack<int> ls;
//     for(int i = 0; i < 5; i++)
//        ls.push(i);
//     linkedStack<int> lsCpy(ls);
//     for(int i = 0; i < 5; i++)
//     {
//         cout << lsCpy.top() << endl;
//         lsCpy.pop();
//     }
// }