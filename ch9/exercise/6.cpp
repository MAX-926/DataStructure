#include"../../Tool.h"
#include"../case/9-1.h"
#include<sstream>
using namespace std;

//使用索引公式9-2，经过若干次pop()操作，可能导致“内存泄漏”，即由于queueFront的移动，小于queueFront的索引值即使未使用，也无法存放队列的数据，只有当theRear触碰到数组空间的末端，程序才去移动队列元素至数组空间的左端
template<class T>
class slowArrayQueue:public queue<T>
{
    public:
        //constructor, copy-constructor and destructor
        slowArrayQueue(int initialCapacity = 10);
        slowArrayQueue(const slowArrayQueue<T>&saq);
        ~slowArrayQueue(){if(slowQueue) delete[] slowQueue;}
        //ADT methods:
        bool empty()const{return (queueFront == theRear + 1) || (theRear == -1);}
        int size()const{return (theRear - queueFront + 1);}
        T& front();
        T& back();
        void pop();
        void push(const T& theElement);
        //Test tools:
        void outputSlowQueue()const;
        void outputCapacity()const{cout << arrayLength << endl;}
        void outputQueueArray()const;
    private:
        T* slowQueue;
        int queueFront;
        int theRear;
        int arrayLength;
};

template<class T>
slowArrayQueue<T>::slowArrayQueue(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "initialCapacity = " << initialCapacity << " must be > 0";
        throw illegalParameter(s.str());
    }
    arrayLength = initialCapacity;
    slowQueue = new T[arrayLength];
    queueFront = 0;
    theRear = -1;
}

template<class T>
slowArrayQueue<T>::slowArrayQueue(const slowArrayQueue<T>& saq)
{
    arrayLength = saq.arrayLength;
    slowQueue = new T[arrayLength];
    if(saq.empty())
    {
        queueFront = saq.queueFront;
        theRear = saq.theRear;
        return;
    }
    //复制队列元素
    // int saqElementsNum = saq.theRear - saq.queueFront + 1;
    copy(saq.queueFront, saq.theRear+1, slowQueue + saq.queueFront);
    queueFront = saq.queueFront;
    theRear = saq.theRear;
}

template<class T>
T& slowArrayQueue<T>::front()
{
    if(theRear == -1 || queueFront == theRear + 1)
        throw queueEmpty();
    return slowQueue[queueFront];
}

template<class T>
T& slowArrayQueue<T>::back()
{
    if(theRear == -1 || (queueFront == theRear + 1))
        throw queueEmpty();
    return slowQueue[theRear];
}

template<class T>
void slowArrayQueue<T>::pop()
{
    if(theRear == -1 || queueFront == theRear + 1)
        throw queueEmpty();
    slowQueue[queueFront].~T();
    queueFront += 1;

}

template<class T>
void slowArrayQueue<T>::push(const T& theElement)
{
    //检查队列是否满，若满则扩容
    if(theRear == arrayLength-1)
    {
        if(queueFront == arrayLength)
        {//原始队列空
            queueFront = 0;
            theRear = -1;
        }
        else
        {//若原始队列不空，则需要移动数据
            int elementsNum = theRear - queueFront + 1;//需要移动的数据的个数
            if(elementsNum+1 <= arrayLength)
            {//不需要扩容，直接移动数据
                for(int i = 0; i < elementsNum; i++)
                {
                    slowQueue[i] = slowQueue[queueFront + i];
                    slowQueue[queueFront+i].~T();
                }
            }
            else
            {//移动数据，需要扩容            
                T* newSlowQueue = new T[arrayLength*2];
                copy(slowQueue + queueFront, slowQueue + theRear + 1, newSlowQueue);
                arrayLength *= 2;
                delete[] slowQueue;
                slowQueue = newSlowQueue;
            }
            queueFront = 0;
            theRear = elementsNum-1;
        }
    }
    slowQueue[++theRear] = theElement;
}

template<class T>
void slowArrayQueue<T>::outputSlowQueue()const
{
    int iter = queueFront;
    while(iter != theRear+1)
    {
        cout << slowQueue[iter] << " ";
        iter++;
    }
}

template<class T>
void slowArrayQueue<T>::outputQueueArray()const
{
    for(int i = 0; i < arrayLength; i++)
        cout << slowQueue[i] << " ";
    cout << "\noutput slowQueue array complete\n";
    return;
}

// int main()
// {
//     slowArrayQueue<int> saq;
//     for(int i = 0; i < 11; i++)
//         saq.push(26);
//     for(int i = 0; i < 5; i++)
//         saq.pop();
//     saq.outputSlowQueue();
//     cout << endl;
//     // saq.outputQueueArray();
//     for(int i = 0; i < 6; i++)
//         saq.push(i);
//     // saq.outputQueueArray();
//     saq.outputSlowQueue();
//     cout << endl;
//     for(int i = 0; i <= 11; i++)
//         saq.pop();
//     saq.outputSlowQueue();
// }

// int main()
// {
//     slowArrayQueue<int> saq;
//     for(int i = 0; i < 500; i++)
//         saq.push(i);
//     for(int i = 0; i < 500; i++)
//     {
//         cout << saq.front() << " ";
//         saq.pop();
//     }
//     cout << endl;
//     for(int i = 0; i < 500; i++)
//         saq.push(i);
//     for(int i = 0; i < 250; i++)
//     {
//         cout << saq.front() << " ";
//         saq.pop();
//     }
//     cout << endl;
//     for(int i = 0; i < 500; i++)
//         saq.push(i);

//     saq.outputSlowQueue();
//     // cout << saq.front() << " " << saq.back();
// }

// int main()
// {
//     slowArrayQueue<int> saq;
//     for(int i = 0; i < 10; i++)
//         saq.push(i);
//     cout << "将队列占满:\n";
//     saq.outputSlowQueue();
//     //将队列前5个元素出队
//     for(int i = 0; i < 5; i++)
//         saq.pop();
//     cout << endl;
//     saq.outputSlowQueue();
//     //测试队列需要扩容时的条件：
//     cout << "\nsourceCapacity:\n";
//     saq.outputCapacity();
//     cout << "打印slowQueue的所有存储空间:\n";
//     saq.outputQueueArray();
//     saq.push(26);
//     cout << "After push:\n";
//     saq.outputCapacity();
//     cout << "打印slowQueue的所有存储空间:\n";
//     saq.outputQueueArray();
//     for(int i = 0; i < 5; i++)
//     {
//         saq.push(i);
//     }
//     cout << "打印slowQueue的所有存储空间:\n";
//     saq.outputQueueArray();
//     cout << "\nsourceCapacity:\n";
//     saq.outputCapacity();

// }