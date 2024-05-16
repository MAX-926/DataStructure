#include"../case/5-3.h"

template<class T>
class arrayListWithReserve:public arrayList<T>
{
    public:
        arrayListWithReserve(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void reserve(int theCapacity);
};

template<class T>
void arrayListWithReserve<T>::reserve(int theCapacity)
{
    if(theCapacity <= this->arrayLength){ return;}
    // theCapacity = std::max(theCapacity, this->arrayLength);
    changeLength1D<T>(this->element, this->arrayLength, theCapacity);

    // T* tmp = new T[theCapacity];
    // std::copy(this->element, (this->element) + (this->listSize), tmp);
    // delete [](this->element);
    // (this->element) = tmp;

    this->arrayLength = theCapacity;
}

int main()
{
    // int * ip = new int[10];
    // for(int i = 0; i < 10; i++)
    //     ip[i] = i+1;

    arrayListWithReserve<int> x(5);
    for(int i = 0; i  < 5; i++)
        x.insert(i, i+1);
    std::cout << x.capacity() << std::endl;
    x.reserve(10);
    std::cout << x.capacity();
    // changeLength1D<int>(ip, 10, 5);
    // for(int i = 0; i < 7; i++)
    //     std::cout << ip[i] << " ";
}