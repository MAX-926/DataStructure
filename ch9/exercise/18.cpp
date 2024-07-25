//构建单向循环链表实现deque
#include"../../Tool.h"

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
class circularDeque:public deque<T>
{
    public:
        //constructor, copy-constructor and destructor
        //O(1)
        circularDeque():deque<T>(), dequeFront(nullptr), dequeBack(nullptr), dequeSize(0){}
        //O(1) or O(dequeSize)
        circularDeque(const circularDeque<T>&);
        //O(1) or O(dequeSize)
        ~circularDeque();
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
        //test tools:
        void circularPrintDeque(int times = 2)const;//默认打印2次，显示双端队列为循环队列
    protected:
        chainNode<T>* dequeFront;
        chainNode<T>* dequeBack;
        int dequeSize;
};

template<class T>
circularDeque<T>::circularDeque(const circularDeque<T>& ld)//O(1) or O(dequeSize)
{//拷贝构造函数
    dequeSize = ld.dequeSize;
    chainNode<T>* iter = ld.dequeFront;
    unsigned int count = 0;
    if(dequeSize == 0)//O(1)
    {
        dequeFront = nullptr;
        dequeBack = nullptr;
        return;
    }
    //复制第一个节点
    dequeFront = new chainNode<T>(iter->data);//将尾节点指向首节点
    iter = iter->next;
    count++;
    chainNode<T>* iterMy = dequeFront;
    while(count != dequeSize)//O(dequeSize)
    {
        iterMy->next = new chainNode<T>(iter->data);
        iterMy = iterMy->next;
        iter = iter->next;
        count++;
    }
    iterMy->next = new chainNode<T>(iter->data, dequeFront);
    dequeBack = iterMy->next;
}

template<class T>
circularDeque<T>::~circularDeque()//O(1) or O(dequeSize)
{
    while(dequeSize != 0)//O(1) or O(dequeSize)
    {
        chainNode<T>* nextNode = dequeFront->next;
        delete dequeFront;
        dequeFront = nextNode;
        dequeSize--;
    }
}

template<class T>
T& circularDeque<T>::front()//O(1)
{
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    return dequeFront->data;//O(1)
}

template<class T>
T& circularDeque<T>::back()//O(1)
{
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    return dequeBack->data;//O(1)
}

template<class T>
T circularDeque<T>::pop_back()//O(1) or [O(1) or O(dequeSize)]
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
    dequeBack->next = dequeFront;
    return targetElement;
}

template<class T>
T circularDeque<T>::pop_front()//O(1)
{//从队列头删除
    if(dequeFront == nullptr)//O(1)
        throw queueEmpty();
    T targetElement;
    chainNode<T>* nextNode = dequeFront->next;
    if(nextNode == dequeFront)//O(1)
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
    dequeBack->next = dequeFront;//更新尾节点对新首节点的连接
    return targetElement;
}

template<class T>
void circularDeque<T>::push_back(const T& theElement)//O(1)
{//将元素压入队尾
    chainNode<T>* newNode = new chainNode<T>(theElement);
    if(dequeFront == nullptr)//O(1)
    {
        dequeFront = newNode;
        dequeBack = dequeFront;
        dequeBack->next = dequeFront;//更新尾节点到首节点的连接
        dequeSize++;
        return;
    }
    dequeBack->next  = newNode;
    dequeSize++;
    dequeBack = newNode;
    dequeBack->next = dequeFront;//更新尾节点到首节点的连接
    return;
}

template<class T>
void circularDeque<T>::push_front(const T& theElement)//O(1)
{
    chainNode<T>* newNode = new chainNode<T>(theElement);
    if(dequeFront == nullptr)//O(1)
    {
        dequeFront = newNode;
        dequeBack = dequeFront;
        dequeBack->next = dequeFront;//更新尾节点到首节点的连接
        dequeSize++;
        return;
    }
    newNode->next = dequeFront;
    dequeFront = newNode;
    dequeBack->next = dequeFront;//更新尾节点到新首节点的连接
    dequeSize++;
    return;
}

template<class T>
void circularDeque<T>::circularPrintDeque(int times)const
{//循环打印dequetimes次，从front到back为一个周期
    int loopTimes = times*dequeSize;
    chainNode<T>* iter = dequeFront;
    if(dequeFront == nullptr)
        throw queueEmpty();
    for(int i = 0; i < loopTimes; i++)
    {
        cout << iter->data << " ";
        iter = iter->next;
    }
    cout << "\noutput complete\n";
}

// int main()
// {
//     circularDeque<int> cd;
//     for(int i = 0; i < 10; i++)
//         cd.push_back(i);
//     cd.circularPrintDeque(2);
// }

// int main()
// {//测试单链deque
//     circularDeque<int> ld;
//     for(int i = 0; i < 10; i++)
//         // ld.push_front(i);
//         ld.push_back(i);
//     circularDeque<int> cpy(ld);
//     cout << "ld.empty = " << ld.empty() << endl;
//     cout << "ld.size = " << ld.size() << endl;
//     cout << "cpy.size = " << cpy.size() << endl;
//     for(int i = 0 ;i < 10; i++)
//     {
//         // cout << ld.back() << " ";
//         // cout << ld.pop_back() << " ";
//         // cout << ld.front() << " ";
//         // cout << ld.pop_front() << " ";
//         // cout << cpy.pop_front() << " ";
//         // cout << cpy.pop_back() << " ";
//     }
//     cout << "ld.empty = " << ld.empty() << endl;
//     cout << "ld.size = " << ld.size() << endl;
//     cout << "cpy.size = " << cpy.size() << endl;

// }

// int main()
// {
//     circularDeque<int> cd;
//     cout << "cd.empty = " << cd.empty() << endl;
//     cout << "cd.size = " << cd.size() << endl;
//     circularDeque<int> cpy(cd);
//     cout << "cd.empty = " << cd.empty() << endl;
//     cout << "cd.size = " << cd.size() << endl;
//     for(int i = 0; i < 5; i++)
//     {
//         // cd.push_back(i);
//         cd.push_front(i);
//         // cpy.push_back(i+5);
//         cpy.push_front(i+5);
//     }
//     for(int i = 0; i < 5; i++)
//     {
//         cout << cd.pop_front() << " ";
//         // cout << cpy.pop_front() << " ";
//         // cd.pop_back();
//         // cpy.pop_back();
//     }
//     cd.push_back(26);
//     cd.circularPrintDeque(2);
//     cpy.push_back(26);
//     cpy.circularPrintDeque(2);
// }