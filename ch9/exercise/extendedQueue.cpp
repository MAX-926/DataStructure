#include"extendedQueue.h"
#include"../case/9-2.cpp"

template<class T>
class extendedarrayQueue:public extendedQueue<T>, private arrayQueue<T>
{
    public:
    //constructor, copy-constructor and destructor
        extendedarrayQueue(int initialCapacity = 10);
        extendedarrayQueue(const extendedarrayQueue<T>&);
        ~extendedarrayQueue(){if(queue) delete[] queue;}
        //ADT methods:
        bool empty()const{return queueFront == theRear;}
        int size()const{return (arrayLength + theRear - queueFront)%arrayLength;}
        T& front();
        T& back();
        void pop();
        void push(const T& theElement);
        //清空队列
        void clear();
        //i：输入一个队列
        // void inputQueue();
        //ii：输出一个队列
        void outputQueue()const;
        //iii:把一个队列分解成两个新队列，一个队列包含原来的1,3,5...个元素，另一个队列包含其余的元素
        void split(extendedarrayQueue<T>& A, extendedarrayQueue<T>& b);
        //iv:把两个队列合并成一个新队列。从队列1开始，轮流从两个队列选择元素插入新队列。若某个队列空了，则将另一个队列中的剩余元素插入新队列。合并前后，每一个队列的元素相对顺序不变。
        void merge(extendedarrayQueue<T>& a, extendedarrayQueue<T>& b);
    protected:
        T* queue;//队列对象
        int arrayLength;//数组长度
        int queueFront;//指向队首元素位置的前一个区域
        int theRear;//队尾元素位置
};


template<class T>
extendedarrayQueue<T>::extendedarrayQueue(int initialCapacity):extendedQueue<T>(), arrayQueue<T>(initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "initialCapacity = " << initialCapacity << " must be > 0";
        throw illegalParameter(s.str());
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    queueFront = 0;
    theRear = 0;
}

template<class T>
extendedarrayQueue<T>::extendedarrayQueue(const extendedarrayQueue<T>& aq)
{
    arrayLength = aq.arrayLength;
    queue = new T[arrayLength];
    copy(aq.queue, aq.queue + arrayLength, queue);
    queueFront = aq.queueFront;
    theRear = aq.theRear;
}

template<class T>
void extendedarrayQueue<T>::clear()
{
    while(queueFront != theRear)
        pop();
}

template<class T>
T& extendedarrayQueue<T>::front()
{//返回queue的首元素
    if(queueFront == theRear)
        throw queueEmpty();
    return queue[(queueFront+1)%arrayLength];
}

template<class T>
T&  extendedarrayQueue<T>::back()
{
    if(queueFront == theRear)
        throw queueEmpty();
    return queue[theRear];
}

template<class T>
void extendedarrayQueue<T>::pop()
{//从queue的队首删除元素
    if(queueFront == (theRear+1) % arrayLength)
        throw queueEmpty();
    queueFront = (queueFront + 1)%arrayLength;
    queue[queueFront].~T();//给T析构（因为当T是有析构函数的数据，需要调用析构函数释放数据占用的空间，但系统分配给的内存不会因此无法访问与使用（这需要使用delete关键字实现内存回收！！！））
}

template<class T>
void extendedarrayQueue<T>::push(const T& theElement)
{//在队尾加入元素，若空间不够则扩容
    if(queueFront == (theRear+1)%arrayLength)
    {//队列满了，需要扩容。将队列数组容量扩充为原来的2倍
        T* newQueue = new T[arrayLength*2];
        int queueSize = (theRear - queueFront + arrayLength) % arrayLength;
        for(int i = 1; i <= queueSize; i++)
            newQueue[i] = queue[((queueFront + i) % arrayLength)];
        queueFront = 0;
        theRear = queueSize;
        arrayLength *= 2;
        delete[] queue;
        queue = newQueue;
    }
    queue[(theRear+1)%arrayLength] = theElement;
    theRear = (theRear + 1) % arrayLength;
}

template<class T>
void extendedarrayQueue<T>::outputQueue()const
{
    if(theRear == queueFront)
    {
        cout << "Queue is empty\n";
        return;
    }
    for(int i = (queueFront+1)%arrayLength; i != theRear; i = (i+1)%arrayLength)
        cout << queue[i] << " ";
    cout << queue[theRear] << endl;
    return;
}

template<class T>
void extendedarrayQueue<T>::split(extendedarrayQueue<T>& a, extendedarrayQueue<T>& b)
{//将数组队列拆分为a，b两个队列，a包含1,3,5...元素，b包含其余元素
    //如果a，b队列非空，则清空a，b
    a.clear();
    b.clear();
    bool tag = true;
    while(theRear != queueFront)
    {
        if(tag)
        {
            a.push(front());
            pop();
            tag = false;
        }
        else
        {
            b.push(front());
            pop();
            tag = true;
        }       
    }
}

template<class T>
void extendedarrayQueue<T>::merge(extendedarrayQueue<T>& a, extendedarrayQueue<T>& b)
{//交替合并a，b的数据
    //清除当前队列的数据
    clear();
    bool tag = true;
    while(!a.empty() && !b.empty())
    {
        if(tag)
        {
            push(a.front());
            a.pop();
            tag = false;
        }
        else
        {
            push(b.front());
            b.pop();
            tag = true;
        }
    }
    while(!a.empty())
    {
        push(a.front());
        a.pop();
    }
    while(!b.empty())
    {
        push(b.front());
        b.pop();
    }
}

int main()
{
    extendedarrayQueue<int> eaq;
    for(int i = 0; i < 16; i++)
        eaq.push(i);
    //测试split函数
    extendedarrayQueue<int> eaq1;
    extendedarrayQueue<int> eaq2;
    cout << "Before split:";
    eaq.outputQueue();
    eaq.split(eaq1, eaq2);
    cout << "After split:\n";
    eaq.outputQueue();
    eaq1.outputQueue();
    eaq2.outputQueue();
    //测试merge函数
    eaq.merge(eaq1, eaq2);
    cout << "After merge:\n";
    eaq.outputQueue();

}

// int main()
// {
//     extendedarrayQueue<int> eaq;
//     for(int i = 0; i < 10; i++)
//         eaq.push(i);
//     cout << "eaq:\n";
//     eaq.outputQueue();
//     extendedarrayQueue<int> eaqCoy = eaq;
//     cout << "eaqCpy:\n";
//     eaqCoy.outputQueue();
// }