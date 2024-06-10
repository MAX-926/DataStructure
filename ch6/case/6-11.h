#ifndef CH6_6_11_H
#define CH6_6_11_H
#include"../../ch5/case/5-1.h"

template<class T>
class extendedLinearList:public linearList<T>
{
    public:
        ~extendedLinearList(){}
        virtual void clear() = 0;
        virtual void push_back(const T& theElement) = 0;
};

#endif //CH6_6_11_H