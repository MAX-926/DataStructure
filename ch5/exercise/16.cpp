#include"../case/5-3.h"
template<class T>
class arrayListWithClear:public arrayList<T>
{
    public:
        arrayListWithClear(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void clear();
};

template<class T>
void arrayListWithClear<T>::clear()
{
    delete [](this->element);
    (this->listSize) = 0;
    (this->arrayLength) = 0;
}

int main()
{
    arrayListWithClear<int> x;
    for(int i = 0; i < 5; i++)
        x.insert(i, i+1);
    std::cout << x.capacity() << std::endl;
    x.clear();
    std::cout << x.capacity() << std::endl;
}