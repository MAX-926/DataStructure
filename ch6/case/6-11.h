#include"../../ch5/case/5-1.h"

template<class T>
class extendLinearList:public linearList<T>
{
    public:
        ~extendLinearList(){}
        virtual void clear() = 0;
        virtual void push_back(const T& theElement) = 0;
};

