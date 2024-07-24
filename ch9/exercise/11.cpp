#include"../case/9-1.h"
#include"9.cpp"

//利用deque实现queue
template<class T>
class dequeQueue:public queue<T>, private arrayDeque<T>
{
    public:
    //constructor, copy-constructor and destructor
        dequeQueue(int initialCapacity = 10);
        dequeQueue(const dequeQueue<T>&);
        ~dequeQueue(){}
        //ADT methods:
        bool empty()const{return arrayDeque<T>::empty();}
        int size()const{return arrayDeque<T>::size();}
        T& front(){return arrayDeque<T>::front();}
        T& back(){return arrayDeque<T>::back();}
        void push(const T& theElement){arrayDeque<T>::push_back(theElement);}
        void pop(){arrayDeque<T>::pop_front();}
};

template<class T>
dequeQueue<T>::dequeQueue(int initialCapacity):queue<T>(), arrayDeque<T>(initialCapacity){}

template<class T>
dequeQueue<T>::dequeQueue(const dequeQueue<T>& dq):arrayDeque<T>(dq), queue<T>(){}

//预期性能评价：arrayDeque中的方法会比dequeQueue的方法执行快，因为dequeQueue的方法是通过嵌套arrayDeque的方法，从而间接调用arrayDeque的方法编写而成。
//dequeQueue的方法自然比直接执行相关函数(arrayDeque的函数)慢

// int main()
// {
//     dequeQueue<int> dq;
//     for(int i = 0; i < 20; i++)
//         dq.push(i);
//     cout << "front: " << dq.front() << " back: " << dq.back() << endl;
//     cout << "size = " << dq.size() << endl;
//     cout << "empty?"  << dq.empty() << endl;
//     // for(int i = 0 ;i < 15; i++)
//     // {
//     //     // cout << dq.front() << " ";
//     //     dq.pop();
//     // }
//     for(int i = 0; i < 20; i++)
//     {
//         cout << dq.front() << " ";
//         dq.pop();
//     }
// }