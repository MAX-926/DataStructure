#include"9-1.h"
#include"../../Tool.h"
#include<sstream>
#include<iostream>
using namespace std;

template<class T>
class arrayQueue:public queue<T>
{//数组队列：一种受限线性表，对队列的操作在队列的两端进行，队首执行删除操作，队尾执行压入操作。
    public:
        //constructor,copy-constructor and destructor
        arrayQueue(int initialCapacity = 10);//初始化数组长度为10
        arrayQueue(const arrayQueue<T>& aq);
        ~arrayQueue(){if(queue) delete[] queue;}//O(arrayLength)
        //ADT methods:
        bool empty()const{return queueFront == theRear;}//O(1)
        int size()const{return (arrayLength + theRear - queueFront)%arrayLength;}//O(1)
        T& front();
        T& back();
        void pop();
        void push(const T& theElement);
        //test tools:
        // void showCapacity()const{cout << arrayLength << endl;}
        // void showQueueFront()const{cout << queueFront << endl;}
        // void showTheRear()const{cout << theRear << endl;}
        
        //5.1）
        // //ii：输出一个队列
        void outputQueue(ostream&)const;
        //iii:把一个队列分解成两个新队列，一个队列包含原来的1,3,5...个元素，另一个队列包含其余的元素
        // void split(arrayQueue<T>& A, arrayQueue<T>& b);
        //iv:把两个队列合并成一个新队列。从队列1开始，轮流从两个队列选择元素插入新队列。若某个队列空了，则将另一个队列中的剩余元素插入新队列。合并前后，每一个队列的元素相对顺序不变。
        // void merge(arrayQueue<T>& a, arrayQueue<T>& b);
    protected:
        T* queue;//队列对象
        int arrayLength;//数组长度
        int queueFront;//指向队首元素位置的前一个区域
        int theRear;//队尾元素位置
};

//test Tools:
template<class T>
void arrayQueue<T>::outputQueue(ostream& out)const
{
    if(empty())
        throw queueEmpty();
    for(int i = 1; i < arrayLength; i++)
        out << queue[i] << " ";
    return;
}

template<class T>
ostream& operator<<(ostream& out, const arrayQueue<T>& aq)
{
    aq.outputQueue(out);
    return out;
}

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity):queue<T>()//O(1) or O(arrayLength)
{
    if(initialCapacity < 1)//O(1)
    {
        ostringstream s;
        s << "initialCapacity = " << initialCapacity << " must be > 0";
        throw illegalParameter(s.str());
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];//O(1) or O(arrayLength)
    queueFront = 0;
    theRear = 0;
}

template<class T>
arrayQueue<T>::arrayQueue(const arrayQueue<T>& aq)//O(arrayLength)
{
    arrayLength = aq.arrayLength;
    queue = new T[arrayLength];//O(1) or O(arrayLength)
    copy(aq.queue, aq.queue + arrayLength, queue);//O(arrayLength)
    queueFront = aq.queueFront;
    theRear = aq.theRear;
}

template<class T>
T& arrayQueue<T>::front()//O(1)
{//返回queue的首元素
    if(queueFront == theRear)//O(1)
        throw queueEmpty();
    return queue[(queueFront+1)%arrayLength];//O(1)
}

template<class T>
T&  arrayQueue<T>::back()//O(1)
{
    if(queueFront == theRear)//O(1)
        throw queueEmpty();
    return queue[theRear];//O(1)
}

template<class T>
void arrayQueue<T>::pop()//O(1)
{//从queue的队首删除元素
    if(queueFront == theRear)//O(1)
        throw queueEmpty();
    queueFront = (queueFront + 1)%arrayLength;
    queue[queueFront].~T();//给T析构（因为当T是有析构函数的数据，需要调用析构函数释放数据占用的空间，但系统分配给的内存不会因此无法访问与使用（这需要使用delete关键字实现内存回收！！！））
}

template<class T>
void arrayQueue<T>::push(const T& theElement)//O(1) or [O(queueSize) or O(queueSize + arrayLength)]
{//在队尾加入元素，若空间不够则扩容
    if(queueFront == (theRear+1)%arrayLength)//O(queueSize) or O(queueSize + arrayLength)
    {//队列满了，需要扩容。将队列数组容量扩充为原来的2倍
        T* newQueue = new T[arrayLength*2];//O(1) or O(arrayLength)
        int queueSize = (theRear - queueFront + arrayLength) % arrayLength;
        for(int i = 1; i <= queueSize; i++)//O(queueSize)
            newQueue[i] = queue[((queueFront + i) % arrayLength)];
        queueFront = 0;
        theRear = queueSize;
        arrayLength *= 2;
        delete[] queue;//O(1) or O(arrayLength)
        queue = newQueue;
    }
    queue[(theRear+1)%arrayLength] = theElement;
    theRear = (theRear + 1) % arrayLength;
}

// int main()
// {
//     arrayQueue<int> aq;
//     for(int i = 0; i < 10; i++)
//         aq.push(i);
//     // aq.showQueue();
//     for(int i = 0; i < 10; i++)
//     {
//         cout << aq.front() << " ";
//         aq.pop();
//     }
// }
// //     aq.push(1);
//     cout << endl << "queueFront:\n";
//     aq.showQueueFront();
//     cout << "TheRear:\n";
//     aq.showTheRear();
//     aq.showCapacity();
// }