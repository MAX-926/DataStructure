#ifndef QUEUE_H
#define QUEUE_H

template<class T>//队列中的元素类型T
class queue
{
    public:
        virtual ~queue(){}
        virtual bool empty()const = 0;
                                    //返回true，当且仅当队列为空
        virtual int size()const = 0;
                                    //返回队列元素个数
        virtual T& front() = 0;
                                //返回队首元素的引用
        virtual T& back() = 0;
                                //返回队尾元素的引用
        virtual void pop() = 0;
                                //删除队首元素
        virtual void push(const T& theElement) = 0;
                                                    //将元素x加入队尾
};

#endif //QUEUE_H