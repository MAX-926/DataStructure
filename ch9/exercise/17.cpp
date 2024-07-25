#include<iostream>
#include"../../Tool.h"

using namespace std;

template<class T>
struct chainNode
{//单链节点
    //constructor:
    chainNode(const T& data, chainNode<T>* next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
    //data field:
    T data;
    //pointer field:
    chainNode<T>* next;
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
class linkedDeque:public deque<T>
{
    public:
        //constructor, copy-constructor and destructor
        //O(1)
        linkedDeque():deque<T>(), dequeFront(nullptr), dequeBack(nullptr), dequeSize(0){}
        //O(1) or O(dequeSize)
        linkedDeque(const linkedDeque<T>&);
        //O(1) or O(dequeSize)
        ~linkedDeque();
        //ADT methods:
        //O(1)
        bool empty()const{return dequeFront == nullptr;}
        //O(1)
        int size()const{return dequeSize;}
        //O(1)
        T& front();
        //O(1)
        T& back();
        //O(1) or [O(1) or O(dequeSize)]
        T pop_back();
        //O(1)
        T pop_front();
        //O(1)
        void push_back(const T&);
        //O(1)
        void push_front(const T&);
    protected:
        chainNode<T>* dequeFront;
        chainNode<T>* dequeBack;
        int dequeSize;
};

template<class T>
linkedDeque<T>::linkedDeque(const linkedDeque<T>& ld)//O(1) or O(dequeSize)
{//拷贝构造函数
    dequeSize = ld.dequeSize;
    chainNode<T>* iter = ld.dequeFront;
    if(iter == nullptr)//O(1)
        throw queueEmpty();
    //复制第一个节点
    dequeFront = new chainNode<T>(iter->data);
    iter = iter->next;
    chainNode<T>* iterMy = dequeFront;
    while(iter != nullptr)//O(dequeSize)
    {
        iterMy->next = new chainNode<T>(iter->data);
        iterMy = iterMy->next;
        iter = iter->next;
    }
    dequeBack = iterMy;
}

template<class T>
linkedDeque<T>::~linkedDeque()//O(1) or O(dequeSize)
{
    while(dequeFront != nullptr)//O(1) or O(dequeSize)
    {
        chainNode<T>* nextNode = dequeFront->next;
        delete dequeFront;
        dequeFront = nextNode;
    }
}

template<class T>
T& linkedDeque<T>::front()//O(1)
{
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    return dequeFront->data;//O(1)
}

template<class T>
T& linkedDeque<T>::back()//O(1)
{
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    return dequeBack->data;//O(1)
}

template<class T>
T linkedDeque<T>::pop_back()//O(1) or [O(1) or O(dequeSize)]
{//从队尾删除元素
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    chainNode<T>* iter = dequeFront;
    T targetElement;
    if(iter == dequeBack)//O(1)
    {
        targetElement = iter->data;
        delete dequeFront;
        dequeFront = nullptr;
        dequeBack = nullptr;
        dequeSize = 0;
        return targetElement;
    }
    while(iter->next != dequeBack)//O(dequeSize)
        iter = iter->next;
    targetElement = dequeBack->data;
    delete dequeBack;
    dequeSize--;
    dequeBack = iter;
    dequeBack->next = nullptr;
    return targetElement;
}

template<class T>
T linkedDeque<T>::pop_front()//O(1)
{//从队列头删除
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    T targetElement;
    chainNode<T>* nextNode = dequeFront->next;
    if(nextNode == nullptr)//O(1)
    {
        targetElement = dequeFront->data;
        delete dequeFront;
        dequeFront = nullptr;
        dequeBack = nullptr;
        dequeSize = 0;
        return targetElement;
    }
    targetElement = dequeFront->data;
    delete dequeFront;
    dequeFront = nextNode;
    dequeSize--;
    return targetElement;
}

template<class T>
void linkedDeque<T>::push_back(const T& theElement)//O(1)
{//将元素压入队尾
    chainNode<T>* newNode = new chainNode<T>(theElement);
    if(dequeFront == nullptr)//O(1)
    {
        dequeFront = newNode;
        dequeBack = dequeFront;
        dequeSize++;
        return;
    }
    dequeBack->next  = newNode;
    dequeSize++;
    dequeBack = newNode;
    return;
}

template<class T>
void linkedDeque<T>::push_front(const T& theElement)//O(1)
{
    chainNode<T>* newNode = new chainNode<T>(theElement);
    if(dequeFront == nullptr)//O(1)
    {
        dequeFront = newNode;
        dequeBack = dequeFront;
        dequeSize++;
        return;
    }
    newNode->next = dequeFront;
    dequeFront = newNode;
    dequeSize++;
    return;
}

// int main()
// {//测试单链deque
//     linkedDeque<int> ld;
//     for(int i = 0; i < 10; i++)
//         // ld.push_front(i);
//         ld.push_back(i);
//     cout << "ld.empty = " << ld.empty() << endl;
//     for(int i = 0 ;i < 10; i++)
//     {
//         // cout << ld.back() << " ";
//         // ld.pop_back();
//         cout << ld.front() << " ";
//         ld.pop_front();
//     }
//     cout << "ld.empty = " << ld.empty() << endl;
// }