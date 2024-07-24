#include"9.cpp"
#include"../../ch8/case/8-1.h"
#include<sstream>
using namespace std;
//双端栈
template<class T>
class dequeStack:public stack<T>, private arrayDeque<T>
{
    public:
        //constructor, copy-constructor and destructor
        dequeStack(int initialCapacity = 10);
        dequeStack(const dequeStack<T>&);
        ~dequeStack(){}
        //ADT methods:
        bool empty()const{return arrayDeque<T>::empty();}
        int size()const{return arrayDeque<T>::size();}
        T& top(){return arrayDeque<T>::front();}
        void pop(){arrayDeque<T>::pop_front();}
        void push(const T& theElement){arrayDeque<T>::push_front(theElement);}
};
//为什么要开发dequeStack？
//可能的原因：要分析使用dirived带来的性能损耗，以及同时获得的编码复杂性降低的优势，以及把双端队列作为栈使用时进行性能评价

template<class T>
dequeStack<T>::dequeStack(int initialCapacity):stack<T>(),arrayDeque<T>(initialCapacity){}

template<class T>
dequeStack<T>::dequeStack(const dequeStack<T>& ds):arrayDeque<T>(ds){}//显式调用父类的拷贝构造函数

// int main()
// {
//     dequeStack<int> ds;
//     for(int i = 0; i < 20; i++)
//         ds.push(i);
//     dequeStack<int> dsCpy(ds);
//     for(int i = 0; i < 20; i++)
//     {
//         cout << dsCpy.top() << " ";
//         dsCpy.pop();
//     }
// }