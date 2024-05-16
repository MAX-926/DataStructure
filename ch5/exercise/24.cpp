#include"../case/5-3.h"

template<class T>
class arrayListWithCircularShift:public arrayList<T>
{
    public:
        arrayListWithCircularShift(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void circularShift(int i);
};

template<class T>
void arrayListWithCircularShift<T>::circularShift(int i)
{
    if(i < 0) return;
    T *tmp = new T[this->listSize];
    for(int index = 0; index < (this->listSize); index++)
        tmp[(index+i) % 5] = (this->element)[index];
    delete [](this->element);
    (this->element) = tmp;
}

int main()
{
    arrayListWithCircularShift<int> x(5);
    for(int i = 0; i < 5; i++)
        x.insert(i, i);
    std::cout << x << std::endl;
    x.circularShift(101);
    std::cout << x << std::endl;
}