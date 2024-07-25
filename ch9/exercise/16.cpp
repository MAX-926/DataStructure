//doubleLinkedsDeque
#include<iostream>
#include"../../Tool.h"
using namespace std;

template<class T>
struct chainNode
{//double linked type:
    //constructor
    chainNode(const T& data, chainNode<T>* previous = nullptr, chainNode<T>* next = nullptr)
    {
        this->data = data;
        this->previous = previous;
        this->next = next;
    }
    //data field
    T data;
    //pointer field
    chainNode<T>* next;
    chainNode<T>* previous;

};

template<class T>
class deque
{
    public:
        virtual ~deque(){}
        virtual bool empty()const = 0;//返回true，当且仅当deque为空
        virtual int size()const = 0;//返回双端队列中元素的个数
        virtual T& front() = 0;//返回队首的元素
        virtual T& back() = 0;//返回队尾的元素
        virtual T pop_back() = 0;//在队尾删除元素
        virtual T pop_front() = 0;//在队首删除元素
        virtual void push_back(const T& theElement) = 0;//在队尾压入元素theElement
        virtual void push_front(const T& theElement) = 0;//在队首压入元素theElement
};

template<class T>
class doubleLinkedDeque:deque<T>
{
    public:
    //constructor, copy-constructor and destructor
        //O(1)
        doubleLinkedDeque():deque<T>(){dequeSize = 0; dequeFront = nullptr; dequeBack = nullptr;}
        //O(1) or O(dlq.dequeSize)
        doubleLinkedDeque(const doubleLinkedDeque<T>&);
        //O(1) or O(dequeSize)
        virtual ~doubleLinkedDeque();
    //ADT methods:
        //O(1)
        bool empty()const{return dequeFront == nullptr;}
        //O(1)
        int size()const{return dequeSize;}
        //O(1)
        T& front();
        //O(1)
        T& back();
        //O(1)
        void push_front(const T&);
        //O(1)
        void push_back(const T&);
        //O(1)
        T pop_front();
        //O(1)
        T pop_back();
    //test tools:
        //O(1) or O(dequeSize)
        void outputDequeFrontToBack();
        //O(1) or O(dequeSize)
        void outputDequeBackToFront();
    protected:
        int dequeSize;
        chainNode<T>* dequeFront;
        chainNode<T>* dequeBack;
};

template<class T>
doubleLinkedDeque<T>::doubleLinkedDeque(const doubleLinkedDeque<T>& dlq)//O(1) or O(dequeSize)
{
    dequeSize = dlq.dequeSize;
    if(!dequeSize)//O(1)
    {
        dequeFront = nullptr;
        dequeBack = nullptr;
        return;
    }
    else//O(dequeSize)
    {
        chainNode<T>* iter = dlq.dequeFront;
        // chainNode<T>* preNode;
        dequeFront = new chainNode<T>(iter->data);
        // preNode = iter;
        iter = iter->next;
        chainNode<T>* iterMy = dequeFront;
        while(iter != nullptr)//O(dequeSize)
        {
            iterMy->next = new chainNode<T>(iter->data, iterMy);
            iterMy = iterMy->next;
            iter = iter->next;
        }
        dequeBack = iterMy;
    }
}

template<class T>
doubleLinkedDeque<T>::~doubleLinkedDeque()//O(1) or O(dequeSize)
{
    while(dequeFront != nullptr)//O(1) or O(dequeSize)
    {
        chainNode<T>* nextNode = dequeFront->next;
        delete dequeFront;
        dequeFront = nextNode; 
    }
}

template<class T>
T& doubleLinkedDeque<T>::front()//O(1)
{
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    return dequeFront->data;//O(1)
}

template<class T>
T& doubleLinkedDeque<T>::back()//O(1)
{
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    return dequeBack->data;//O(1)
}

template<class T>
void doubleLinkedDeque<T>::push_front(const T& theElement)//O(1)
{//将元素从队首插入
    chainNode<T>* newNode = new chainNode<T>(theElement);
    if(dequeFront != nullptr)//O(1)
    {
        newNode->next = dequeFront;
        dequeFront->previous = newNode;
        dequeFront = newNode;
    }
    else//O(1)
    {
        dequeFront = newNode;
        dequeBack = newNode;
    }
    dequeSize++;
}

template<class T>
void doubleLinkedDeque<T>::push_back(const T& theElement)//O(1)
{//尾差
    chainNode<T>* newNode = new chainNode<T>(theElement);
    if(dequeFront == nullptr)//O(1)
        dequeFront = newNode;
    else//O(1)
    {
        dequeBack->next = newNode;
        dequeBack->next->previous = dequeBack;
    }
    dequeBack = newNode;
    dequeSize++;
}

template<class T>
T doubleLinkedDeque<T>::pop_front()//O(1)
{//从队首删除
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    chainNode<T>* targetNode = dequeFront;
    dequeFront = dequeFront->next;
    if(dequeFront != nullptr)
        dequeFront->previous = nullptr;
    dequeSize--;
    T targetElement = targetNode->data;
    delete targetNode;
    return targetElement;
}

template<class T>
T doubleLinkedDeque<T>::pop_back()//O(1)
{//从队尾删除
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    chainNode<T>* targetNode = dequeBack;
    dequeBack = dequeBack->previous;
    if(dequeBack != nullptr)//有可能当前删除的节点是队列仅有的节点
        dequeBack->next = nullptr;
    dequeSize--;
    T targetElement = targetNode->data;
    delete targetNode;
    if(dequeSize == 0)
        dequeFront = nullptr;    
    return targetElement;
}

template<class T>
void doubleLinkedDeque<T>::outputDequeFrontToBack()//O(1) or O(dequeSize)
{
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    chainNode<T>* iter = dequeFront;
    while(iter != nullptr)//O(dequeSize)
    {
        cout << iter->data << " ";
        iter = iter->next;
    }
}

template<class T>
void doubleLinkedDeque<T>::outputDequeBackToFront()//O(1) or O(dequeSize)
{
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    chainNode<T>* iter = dequeBack;
    while(iter != nullptr)//O(dequeSize)
    {
        cout << iter->data << " ";
        iter = iter->previous;
    }

}

// int main()
// {
//     // doubleLinkedDeque<int> dlq;
//     // for(int i = 0; i < 10; i++)
//     //     // dlq.push_back(i);
//     //     dlq.push_front(i);
//     // doubleLinkedDeque<int> cpy(dlq);
//     // cout << "dlq.back = " << dlq.back() << endl;
//     // cout << "dlq.front = " << dlq.front() << endl;
//     // cout << "dlq.size = " << dlq.size() << endl;
//     // cout << "dlq.empty = " << dlq.empty() << endl;
//     // for(int i = 0; i < 10; i++)
//     // {
//     //     cout << dlq.front() << " ";
//     //     // cout << dlq.back() << " ";
//     //     dlq.pop_front();
//     //     // dlq.pop_back();
//     // }
//     // cout << "dlq.size = " << dlq.size() << endl;
//     // cout << "dlq.empty = " << dlq.empty() << endl;
//     // cout << "cpyTime:****************************\n";
//     // for(int i = 0; i < 10; i++)
//     // {
//     //     cout << cpy.back() << " ";
//     //     cpy.pop_back();
//     // }

//     doubleLinkedDeque<int> dlq;
//     for(int i = 0; i < 10; i++)
//         dlq.push_back(i);
//     dlq.outputDequeBackToFront();//增序
//     cout << endl;
//     dlq.outputDequeFrontToBack();//降序
//     cout << "dlq.front = " << dlq.front() << endl;
//     cout << "dlq.back = " << dlq.back() << endl;
//     cout << "dlq.size = " << dlq.size() << endl;
// }