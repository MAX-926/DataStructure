//修改类arrayQueue的描述方法，使得一个队列的容量与数组queue的大小相同。
//为此修改变量queueSize代替变量queueBack，queueSize表示队列大小。
//按习惯，队列首元素是queue[queueFront]。队列尾元素的位置可以用queueSize算出
#include"../../Tool.h"
#include"../case/9-1.h"
#include<sstream>

using namespace std;

template<class T>
class arrayQueueWithQueueSize:public queue<T>
{//环形队列
    public:
        //constructor, copy-constructor and destructor
        arrayQueueWithQueueSize(int initialCapacity = 10);
        arrayQueueWithQueueSize(const arrayQueueWithQueueSize<T>& aqwqs);
        ~arrayQueueWithQueueSize(){if(queue) delete[] queue;}
    //ADT methods：
        bool empty()const{return queueSize == 0;}
        int size()const{return queueSize;}
        T& front();
        T& back();
        void pop();
        void push(const T& theElement);
        void outputQueue()const;
        //tools:
        int getQueueFront()const{return queueFront;}
        int getQueueBack()const
        {
            int queueBack = queueSize + queueFront;
            if(queueBack >= arrayLength)
                queueBack -= arrayLength;
            return queueBack;
        }
        int getArrayLength()const{return arrayLength;}    
    private:
        T* queue;//数组队列
        int arrayLength;//队列的容量
        int queueSize;//队列的元素个数
        int queueFront;//队首的位置
        //queueBack由queueSize与queueFront计算出来
};

template<class T>
arrayQueueWithQueueSize<T>::arrayQueueWithQueueSize(int initialCapacity):queue<T>()//需要显示调用抽象基类的构造函数
{
    //初始化队列类arrayQueueWithQueueSize
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "initialCapacity = " << initialCapacity << " must be > 0";
        throw illegalParameter(s.str());
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    queueSize = 0;
    queueFront = 0;
}

//需要考虑
template<class T>
arrayQueueWithQueueSize<T>::arrayQueueWithQueueSize(const arrayQueueWithQueueSize<T>& aqwqs)
{//拷贝构造函数
    arrayLength = aqwqs.arrayLength;
    queue = new T[arrayLength];
    queueFront = aqwqs.queueFront;
    queueSize = aqwqs.queueSize;
    //计算队尾位置
    int queueBack = queueSize + queueFront;
    if(queueBack >= arrayLength)
        queueBack -= arrayLength;
    int i;
    for(i = queueFront; i != queueBack ; i = (i+1)%arrayLength)
    {
        queue[i] = aqwqs.queue[i];
    }
    //复制最后一个元素
    queue[i] = aqwqs.queue[i];
}

template<class T>
T& arrayQueueWithQueueSize<T>::front()
{//queueFront是一个置空的区域
    if(queueSize == 0)
        throw queueEmpty();
    return queue[(queueFront+1)%arrayLength];
}

template<class T>
T& arrayQueueWithQueueSize<T>::back()
{
    if(queueSize == 0)
        throw queueEmpty();
    int queueBack = queueSize + queueFront;
    if(queueBack >= arrayLength)
        queueBack -= arrayLength;
    return queue[queueBack];
}

template<class T>
void arrayQueueWithQueueSize<T>::pop()
{
    if(queueSize == 0)
        throw queueEmpty();
    queueFront = (queueFront + 1) % arrayLength;
    queue[queueFront].~T();
    queueSize--;
}

template<class T>
void arrayQueueWithQueueSize<T>::push(const T& theElement)
{//将theElement压入队列
    if(queueSize == arrayLength)
    {//扩容
        T* newQueue = new T[arrayLength*2];
        int queueBack = queueSize + queueFront;
        if(queueBack >= arrayLength)
            queueBack -= arrayLength;
        int i;
        int j = 1;
        for(i = (queueFront+1)%arrayLength; i != queueBack; i = (i+1)%arrayLength)
            newQueue[j++] = queue[i];
        newQueue[j] = queue[i];
        arrayLength *= 2;
        queueFront = 0;
        delete[] queue;
        queue = newQueue; 
    }
    int queueBack = queueSize + queueFront;
    if(queueBack >= arrayLength)
        queueBack -= arrayLength;
    queue[(queueBack + 1) % arrayLength] = theElement;
    queueSize++;
}

template<class T>
void arrayQueueWithQueueSize<T>::outputQueue()const
{
    if(!queueSize)
    {
        cout << "Queue empty\n";
        return;
    }
    int iter = (queueFront+1)%arrayLength;
    int queueBack = queueSize + queueFront;
    if(queueBack >= arrayLength) queueBack -= arrayLength;
    while(iter != queueBack)
    {
        cout << queue[iter] << " ";
        iter = (iter + 1) % arrayLength;
    }
    cout << queue[iter] << endl; 
}

// int main()
// {
//     arrayQueueWithQueueSize<int> aqwqs;
//     for(int i = 0; i < 100; i++)
//         aqwqs.push(i);
//     // cout << "queueFront: " << aqwqs.getQueueFront() << "\nqueueBack: " << aqwqs.getQueueBack() << endl;
//     // cout << aqwqs.getArrayLength();
//     // aqwqs.outputQueue();
//     arrayQueueWithQueueSize<int> aqwqsCpy = aqwqs;
//     // for(int i = 0; i < 100; i++)
//     // {
//     //     cout << aqwqsCpy.front() << " ";
//     //     aqwqsCpy.pop();
//     // }
//     aqwqsCpy.pop();
//     cout << endl;
//     for(int i = 0; i < 100; i++)
//     {
//         cout << aqwqsCpy.front() << " ";
//         aqwqsCpy.pop();
//     }

// }