//extendedLinkedStack,它派生于类linkedStack和抽象类extendedStack
#include"../case/8-1.h"
#include"../case/8-5.cpp"

//abstract class extendedStack

template<class T>
class extendedLinkedStack;

template<class T>
class extendedStack:stack<T>
{
    public:
        virtual ~extendedStack(){}
        //toString
        virtual string& toString()const = 0;
        //split
        virtual void split(extendedLinkedStack<T>&, extendedLinkedStack<T>&) = 0;
        //combine
        virtual void combine(extendedLinkedStack<T>&, extendedLinkedStack<T>&) = 0;
};

//target class
template<class T>
class extendedLinkedStack:public linkedStack<T>, public extendedStack<T>
{
    public:
        extendedLinkedStack(int initialCapacity = 10):linkedStack<T>(initialCapacity), extendedStack<T>(){}
        //Stack methos:
        bool empty()const{return linkedStack<T>::size() == 0;}
        int size()const{return linkedStack<T>::size();}
        T& top()
        {
            if(linkedStack<T>::size() == 0)
                throw stackEmpty();
            return linkedStack<T>::top();
        }
        void pop()
        {
            linkedStack<T>::pop();
        }
        void push(const T& theElement)
        {
            // linkedStack<T>::stackTop = new chainNode<T>(theElement, stackTop);
            // ++linkedStack<T>::stackSize;
            linkedStack<T>::push(theElement);
        }
        //extendedStack method:
        string& toString()const;
        //extendedStack method:
        void split(extendedLinkedStack<T>&, extendedLinkedStack<T>&);
        //extendedStack method:
        void combine(extendedLinkedStack<T>&, extendedLinkedStack<T>&);
        //Tools:
        void pushNode(chainNode<T>* theNode);
        chainNode<T>* popNode();
};

template<class T>
void extendedLinkedStack<T>::pushNode(chainNode<T>* theNode)
{//将节点推至表尾
    if(theNode == nullptr) return;
    if(linkedStack<T>::stackTop == nullptr)
    {
        linkedStack<T>::stackTop = theNode;
        theNode->next = nullptr;
        ++linkedStack<T>::stackSize;
        return;
    }
    chainNode<T>* currentNode = linkedStack<T>::stackTop;
    while(currentNode->next != nullptr)
        currentNode = currentNode->next;
    currentNode->next = theNode;
    theNode->next = nullptr;
    ++linkedStack<T>::stackSize;
}

template<class T>
chainNode<T>* extendedLinkedStack<T>::popNode()
{
    if(linkedStack<T>::stackTop == nullptr)
        throw stackEmpty();
    chainNode<T>* delNode = linkedStack<T>::stackTop;
    linkedStack<T>::stackTop = linkedStack<T>::stackTop->next;
    --linkedStack<T>::stackSize;
    return delNode;
}

template<class T>
string& extendedLinkedStack<T>::toString()const
{
    int index = linkedStack<T>::stackSize-1;
    T* theString = new T[linkedStack<T>::stackSize];
    chainNode<T>* currentNode = linkedStack<T>::stackTop;
    while(currentNode != nullptr)
    {
        theString[index--] = currentNode->element;
        currentNode = currentNode->next; 
    }
    // return string(theString);
}

template<class T>
void extendedLinkedStack<T>::split(extendedLinkedStack<T>& a, extendedLinkedStack<T>& b)
{//a:bottom-halfElements,b:left elements
    // int aSize = linkedStack<T>::stackSize/2;
    int aSize = linkedStack<T>::stackSize/2 >= (linkedStack<T>::stackSize - linkedStack<T>::stackSize/2) ? linkedStack<T>::stackSize/2 : (linkedStack<T>::stackSize - linkedStack<T>::stackSize/2);
    int bSize = linkedStack<T>::stackSize - aSize;
    chainNode<T>* theNode = nullptr;
    for(int i = 0; i < bSize; i++)
    {
        theNode = popNode();
        b.pushNode(theNode);
    }
    for(int i = 0; i < aSize; i++)
    {
        theNode = popNode();
        a.pushNode(theNode);
    }
    return;
}

template<class T>
void extendedLinkedStack<T>::combine(extendedLinkedStack<T>& a, extendedLinkedStack<T>& b)
{
    while(linkedStack<T>::stackTop != nullptr)
    {
        chainNode<T>* nextNode = linkedStack<T>::stackTop->next;
        delete linkedStack<T>::stackTop;
        linkedStack<T>::stackTop = nextNode;
    }
    //把a，b的元素压入栈中
    while(b.stackTop != nullptr)
        pushNode(b.popNode());
    while(a.stackTop != nullptr)
        pushNode(a.popNode());
}

int main()
{
    extendedLinkedStack<int> s;
    for(int i = 0; i < 1; i++)
        s.push(i);
    // for(int i = 0; i < 5; i++)
    // {
    //     cout << s.top();
    //     s.pop();
    // }
    extendedLinkedStack<int> a, b;
    s.split(a, b);
    cout << "output a, b:\n";
    for(int i = 0; i < 1; i++)
    {
        cout << a.top();
        a.pop();
    }
    for(int i = 0; i < 0; i++)
    {
        cout << b.top();
        b.pop();
    }
    // s.combine(a, b);
    // for(int i = 0; i < 1; i++)
    // {
    //     cout << s.top();
    //     s.pop();
    // }
}