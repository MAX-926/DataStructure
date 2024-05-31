#include"../../ch5/case/5-1.h"

template<class T>
class extendedLinearList:public linearList<T>
{
    public:
        ~extendedLinearList(){}
        virtual void clear() = 0;
        virtual void push_back(const T& theElement) = 0;
};