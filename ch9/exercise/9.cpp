//双端（deque）队列是一个有序线性表，在表的任何一端可以插入和删除操作
//1)定义双端队列的抽象数据类型，要求包含以下操作：
//1.empty 2.size 3.front 4.back 5.push_front 6.pop_front 7.push_back 8.pop_back
/*

抽象数据类型deque
{
    数据：
        deque:deque是一个有序线性表，在表的两端可以进行插入和删除的操作
    操作：
        empty()：返回true，当且仅当deque为空
        size()：返回双端队列中元素的个数
        front()：返回队首的元素
        back()：返回队尾的元素
        pop_front()：在队首删除元素
        pop_back()：在队尾删除元素
        push_front()：在队首压入元素
        push_back()：在队尾压入元素
}

*/

//2)定义一个C++抽象类deque，使抽象数据类型deque中每一个函数都在该抽象类中有对应的方法

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

//3)用公式（9-3）表示一个双向队列。设计一个具体的C++类arrayDeque，它派生于deque。注意，C++的STL中的类deque是数据结构deque的数组实现。
//deque应该是一个环形队列
#include"../../Tool.h"
#include<sstream>
using namespace std;

template<class T>
class arrayDeque:public deque<T>
{
    public:
    //constructor, copy-constructor and destructor
        arrayDeque(int initialCapacity = 10);//O(1) or O(initialCapacity)
        arrayDeque(const arrayDeque<T>&);//O(ad.size + arrayLength)
        ~arrayDeque(){if(deque) delete[] deque;}//O(1) cout << "~arrayDeque()\n";
    //ADT methods:
        //O(1)
        bool empty()const{return queueFront == queueBack;}
        //O(1)
        int size()const{return (queueBack - queueFront + arrayLength) % arrayLength;}
        //O(1)
        T& front();
        //O(1)
        T& back();
        //O(1)
        T pop_front();
        //O(1)
        T pop_back();
        //O(1) or O(this.size) or O(arrayLength + this.size)
        void push_front(const T& theElement);
        //O(1) or O(this.size) or O(arrayLength + this.size)
        void push_back(const T& theElement);
    //test tools:
        //O(1)
        void outputCapacity()const{cout << "capacity = " << arrayLength << endl;}
        //O(this.size)
        void outputDequeFrontToBack()const;
        //O(this.size)
        void outputDequeBackToFront()const;
        //O(arrayLength)
        void outputDequeArray()const;
    protected:
        T* deque;
        int arrayLength;
        int queueFront;
        int queueBack;
};

template<class T>
arrayDeque<T>::arrayDeque(int initialCapacity)//O(1) or O(initialCapacity)
{
    if(initialCapacity < 1)//O(1)
    {
        ostringstream s;
         s << "initialCapacity = " << initialCapacity << " must be > 0";
         throw illegalParameter(s.str());
    }
    queueFront = 0;
    queueBack = 0;
    arrayLength = initialCapacity;
    deque = new T[arrayLength];//O(arrayLength) or O(1)，取决于类型T是否有构造函数需要调用
}

template<class T>
arrayDeque<T>::arrayDeque(const arrayDeque<T>& ad)//O(ad.size + arrayLength)
{//复制队列元素
    arrayLength = ad.arrayLength;
    queueFront = ad.queueFront;
    queueBack = ad.queueBack;
    deque = new T[arrayLength];//O(1) or O(ad.arrayLength)
    int iter = (ad.queueFront+1) % ad.arrayLength;
    while(iter != ad.queueBack)//O(ad.size)
    {
        deque[iter] = ad.deque[iter];
        iter = (iter + 1) % arrayLength;
    }
    //复制最后一个元素
    deque[iter] = ad.deque[iter];
}

template<class T>
T& arrayDeque<T>::front()//O(1)
{//获取队首元素
    if(queueFront == queueBack)//O(1)
        throw queueEmpty();
    return deque[(queueFront + 1) % arrayLength];//O(1)
}

template<class T>
T& arrayDeque<T>::back()//O(1)
{//获取队尾元素
    if(queueFront == queueBack)//O(1)
        throw queueEmpty();
    return deque[queueBack];//O(1)
}

template<class T>
T arrayDeque<T>::pop_front()//O(1)
{//删除队首元素
    if(queueFront == queueBack)//O(1)
        throw queueEmpty();
    queueFront = (queueFront + 1) % arrayLength;
    T re = deque[queueFront];
    deque[queueFront].~T();
    return re;
}

template<class T>
T arrayDeque<T>::pop_back()//O(1)
{//删除队尾元素
    if(queueFront == queueBack)//O(1)
        throw queueEmpty();
    T re = deque[queueBack];
    deque[queueBack].~T();
    queueBack = (queueBack - 1 + arrayLength) % arrayLength;
    return re;
}

template<class T>
void arrayDeque<T>::push_front(const T& theElement)//O(1) or O(this.size) or O(arrayLength + this.size)
{//向队首加入元素
    if((queueBack+1) % arrayLength == queueFront)//O(this.size) or O(arrayLength + this.size)
    {//队列满。需要扩容
        T* newDeque = new T[arrayLength*2];//O(1) or O(arrayLength)
        //复制元素
        int j = 1;
        int iter = (queueFront + 1) % arrayLength;
        while(iter != queueBack)//O(this.size)
        {
            newDeque[j++] = deque[iter];
            iter = (iter + 1) % arrayLength;
        }
        //复制最后一个元素
        newDeque[j] = deque[iter];
        //初始化queueFront,queueBack,arrayLength
        queueFront = 0;
        queueBack = j;
        arrayLength *= 2;
        delete[] deque;//O(1) or O(this.size)
        deque = newDeque;
    }
    deque[queueFront] = theElement;
    queueFront = (queueFront - 1 + arrayLength) % arrayLength;
}

template<class T>
void arrayDeque<T>::push_back(const T& theElement)//O(1) or O(this.size) or O(arrayLength + this.size)
{//向队尾加入元素
    if((queueBack+1) % arrayLength == queueFront)////O(this.size) or O(arrayLength + this.size)
    {//队列满。需要扩容
        T* newDeque = new T[arrayLength*2];
        //复制元素
        int j = 1;
        int iter = (queueFront+1) % arrayLength;
        while(iter != queueBack)
        {
            newDeque[j++] = deque[iter];
            iter = (iter + 1) % arrayLength;
        }
        //复制最后一个元素
        newDeque[j] = deque[iter];
        //初始化queueFront,queueBack,arrayLength
        queueFront = 0;
        queueBack = j;
        arrayLength *= 2;
        delete[] deque;
        deque = newDeque;
    }
    queueBack = (queueBack + 1) % arrayLength;
    deque[queueBack] = theElement;
}

template<class T>
void arrayDeque<T>::outputDequeFrontToBack()const//O(this.size)
{//从队首打印到队尾
    int iter = (queueFront + 1) % arrayLength;
    while(iter != queueBack)//相等队列为空
    {
        cout << deque[iter] << " ";
        iter = (iter + 1) % arrayLength;
    }
    cout << deque[iter] << endl;
}

template<class T>
void arrayDeque<T>::outputDequeBackToFront()const//O(this.size)
{//从队尾到队首打印元素
    int iter = queueBack;
    while(queueBack != queueFront)
    {
        cout << deque[iter] << " ";
        iter = (iter + 1) % arrayLength;
    }
    cout << endl;
}


template<class T>
void arrayDeque<T>::outputDequeArray()const//O(arrayLength)
{
    for(int i = 0; i < arrayLength; i++)
        cout << deque[i] << " ";
    cout << endl;
}

//3)用适当的测试数据测试代码

// int main()
// {
//     arrayDeque<int> ad;//initialCapacity = 10

//     //测试empty()
//     // ad.push_front(26);
//     // ad.push_back(26);
//     // for(int i = 0; i < 10; i++)//触发扩容
//     //     ad.push_front(26);
//     //     // ad.push_back(26);
//     // ad.outputCapacity();
//     // switch(ad.empty())
//     // {
//     //     case true:
//     //         cout << "ad is empty\n";
//     //         break;
//     //     default:
//     //         cout << "ad is not empty\n";
//     // }

//     //测试size()
//         //未扩容前
//     // for(int i = 0; i < 9; i++)
//         // ad.push_front(i);
//         // ad.push_back(i);
//         // ad.pop_front();
//         // ad.pop_back();
//         //扩容后
//     // for(int i = 0; i < 10; i++)
//         // ad.push_front(i);
//         // ad.push_back(i);
//         // ad.pop_front();
//         // ad.pop_back();
//     // cout << "ad.size = " << ad.size() << endl;

//     //测试front()
//     // for(int i = 0; i < 5; i++)
//     //     // ad.push_back(i);
//     //     ad.push_front(i);
//     // for(int i = 0; i < 10; i++)//触发扩容，检查front是否为预期值
//     // {
//         // ad.push_front(i);
//         // ad.push_back(i);
//         // cout << ad.front() << " ";
//         // cout << ad.back() << " ";
//     // }

//     //测试back()
//     // for(int i = 0; i < 5; i++)
//     //     // ad.push_back(i);
//     //     ad.push_front(i);
//     // for(int i = 0; i < 10; i++)//触发扩容，检查front是否为预期值
//     // {
//     //     // ad.push_front(i);
//     //     ad.push_back(i);
//     //     // cout << ad.front() << " ";
//     //     // cout << ad.back() << " ";
//     // }
//     // for(int i = 0; i < 15; i++)
//     // {
//     //     cout << ad.back() << " ";
//     //     ad.pop_back();
//     // }
//     //4 3 2 1 0 0 1 2 3 4 5 6 7 8 9

//     // 测试pop_back()/push_back()
//     // for(int i = 0; i < 20; i++)
//     //     ad.push_back(i);
//     // ad.outputDequeArray();
//     // ad.outputCapacity();
//     // for(int i = 0; i < 20; i++)
//     // {
//     //     cout << ad.back() << " ";
//     //     ad.pop_back();
//     // }
//     // cout << ad.size()

//     //测试pop_front()/push_front()
//     // for(int i = 0; i < 20; i++)
//     //     ad.push_front(i);
//     // ad.outputDequeArray();
//     // ad.outputCapacity();
//     // for(int i = 0; i < 20; i++)
//     //     ad.push_back(i);
//     // ad.outputDequeArray();
//     // ad.outputCapacity();
//     // for(int i = 0; i < 40; i++)
//     // {
//     //     cout << ad.front() << " ";
//     //     ad.pop_front();
//     // }

// }