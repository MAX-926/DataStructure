#ifndef EXTENDEDQUEUE_H
#define EXTENDEDQUEUE_H

#include"../case/9-1.h"

template<class T>
class extendedarrayQueue;
template<class T>
class extendedQueue:public queue<T>
{
    public:
        virtual ~extendedQueue(){}
        //NEW methods:
        //5.1）
        //i：输入一个队列
        // virtual void inputQueue() = 0;
        //ii：输出一个队列
        virtual void outputQueue()const = 0;
        //iii:把一个队列分解成两个新队列，一个队列包含原来的第1,3,5...个元素，另一个队列包含其余的元素
        virtual void split(extendedarrayQueue<T>& A, extendedarrayQueue<T>& b) = 0;
        //iv:把两个队列合并成一个新队列。从队列1开始，轮流从两个队列选择元素插入新队列。若某个队列空了，则将另一个队列中的剩余元素插入新队列。合并前后，每一个队列的元素相对顺序不变。
        virtual void merge(extendedarrayQueue<T>& a, extendedarrayQueue<T>& b) = 0;
};
#endif // EXTENDEDQUEUE_H