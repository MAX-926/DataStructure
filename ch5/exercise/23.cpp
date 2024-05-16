#include"../case/5-3.h"

template<class T>
class arrayListWithLeftShift:public arrayList<T>
{
    public:
        arrayListWithLeftShift(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void leftShift(int position);
};

template<class T>
void arrayListWithLeftShift<T>::leftShift(int position)
{
    if(position <= 0) return;// could throw exception when i < 0 or do a right shift by i
    else if(position >= (this->listSize))
    {
        delete [](this->element);
        this->arrayLength = 0;
        this->listSize = 0;
    }
    else
    {
        T *tmp = (this->element);
        (this->element) += position;
        for( ; tmp < this->element; tmp++)
            tmp->~T();
        (this->listSize) -= position;
        (this->arrayLength) -= position;
    }
}

int main()
{
    arrayListWithLeftShift<int> x(5);
    for(int i = 0; i < 5; i++)
        x.insert(i, i);
    std::cout << x << std::endl;
    x.leftShift(5);
    std::cout << x << std::endl;
}