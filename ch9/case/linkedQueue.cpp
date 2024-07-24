#include"9-1.h"
#include"../../Tool.h"
template<class T>
struct chainNode
{//单向链表的节点
    //constructor
    chainNode(const T& data, chainNode<T>* next = nullptr)//O(1)
    {
        this->data = data;
        this->next = next;
    }
    //data field
    T data;
    //pointer field
    chainNode<T>* next;
};

template<class T>
class linkedQueue:public queue<T>
{
    public:
    //constructor, copy-constructor and destructor
        linkedQueue();//O(1)
        linkedQueue(const linkedQueue<T>&);//O(1) or O(elementsNum)
        ~linkedQueue();//O(elementsNum)
    //ADT methods:
        bool empty()const{return queueFront == nullptr;}//O(1)
        int size()const{return queueSize;}//O(1)
        T& front();//O(1)
        T& back();//O(1)
        void push(const T&);//O(1)
        void pop();//O(1)
    protected:
        chainNode<T>* queueFront;
        chainNode<T>* queueBack;
        int queueSize;
};

template<class T>
linkedQueue<T>::linkedQueue()
{
    queueFront = nullptr;
    queueBack = nullptr;
    queueSize = 0;
}

template<class T>
linkedQueue<T>::linkedQueue(const linkedQueue<T>& lq)
{
    if(lq.queueSize == 0)//O(1)
    {
        queueFront = nullptr;
        queueBack = nullptr;
        queueSize = 0;
        return;
    }
    else//O(elementsNum)
    {
        queueSize = lq.queueSize;
        chainNode<T>* sourceIter = lq.queueFront;
        queueFront = new chainNode<T>(sourceIter->data);
        chainNode<T>* iter = queueFront;
        sourceIter = sourceIter->next;
        while(sourceIter != nullptr)
        {
            iter->next = new chainNode<T>(sourceIter->data);
            iter = iter->next;
            sourceIter = sourceIter->next;
        }
    }
}

template<class T>
linkedQueue<T>::~linkedQueue()
{
    while(queueFront != nullptr)//O(elementsNum)
    {
        chainNode<T>* nextNode = queueFront->next;
        // cout << "call destructor for elements " << queueFront->data << endl;
        delete queueFront;
        queueFront = nextNode;
    }
}

template<class T>
T& linkedQueue<T>::front()
{
    if(queueFront == nullptr)//O(1)
        throw queueEmpty();
    return queueFront->data;//O(1)
}

template<class T>
T& linkedQueue<T>::back()
{
    if(queueSize == 0)//O(1)
        throw queueEmpty();
    return queueBack->data;//O(1)
}

template<class T>
void linkedQueue<T>::push(const T& theElement)
{
    chainNode<T>* tmp = new chainNode<T>(theElement);
    if(queueSize == 0)
        queueFront = tmp;
    else
        queueBack->next = tmp;
    queueSize++;
    queueBack = tmp;

    // if(queueSize == 0)//O(1)
    // {
    //     // queueFront = new chainNode<T>(theElement);
    //     queueFront = new chainNode<T>(theElement);
    //     queueBack = queueFront;
    //     queueSize++;
    //     return;
    // }
    // else//O(1)
    // {
    //     queueBack->next = new chainNode<T>(theElement);
    //     queueBack = queueBack->next;
    //     queueSize++;
    //     return;
    // }
}

template<class T>
void linkedQueue<T>::pop()
{
    if(queueSize == 0)//O(1)
        throw queueEmpty();
    chainNode<T>* nextNode = queueFront->next;
    delete queueFront;
    queueFront = nextNode;
    queueSize--;
}

// int main()
// {
//     linkedQueue<int> lq;
//     for(int i = 0; i < 20; i++)
//         lq.push(i);
//     linkedQueue<int> lqCppy(lq);
//     for(int i = 0; i < 20; i++)
//     {
//         cout << lqCppy.front() << " ";
//         lqCppy.pop();
//     }
//     cout << "lqCpy.size = " << lqCppy.size() << endl;
//     cout << "lq.size = " << lq.size() << endl;
// }
//     cout << "lqCpy.size = " << lqCppy.size() << endl;
//     cout << "\nlq.size = " << lq.size() << endl;
//     cout << "\n******************************\n";
//     for(int i = 0; i < 20; i++)
//     {
//         cout << lq.front() << " ";
//         lq.pop();
//     }
//     cout << "\nlq.size = " << lq.size() << endl;

//     // cout << "size = " << lq.size() << endl;
//     // cout << "empty? " << lq.empty() << endl;
//     // cout << "front: " << lq.front() << endl;
//     // cout << "back: " << lq.back() << endl;
//     // for(int i = 0; i < 20; i++)
//     // {
//     //     cout << lq.front() << " ";
//     //     lq.pop();
//     // }
//     // for(int i = 0; i < 5; i++)
//     //     lq.push(i);
//     // for(int i = 0; i < 5; i++)
//     // {
//     //     cout << lq.front() << " ";
//     //     lq.pop();
//     // }
//     // cout << "empty? " << lq.empty() << endl;
// }