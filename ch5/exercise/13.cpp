#include"../case/5-3.h"

template<class T>
class arrayListWithSwap:public arrayList<T>
{
    public:
        arrayListWithSwap(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void swap(arrayListWithSwap<T> &x);
};

template<class T>
void arrayListWithSwap<T>::swap(arrayListWithSwap<T> &x)
{
//     T* tmp;
//     int tmpLen;
//     int tmpListSize;
//     tmp = this->element;
//     tmpLen = this->arrayLength;
//     tmpListSize = this->listSize;
//     //swap
//     this->element = x.element;
//     this->arrayLength = x.arrayLength;
//     this->listSize = x.listSize;
//     x.element = tmp;
//     x.arrayLength = tmpLen;
//     x.listSize = tmpListSize;
    std::swap(this->element, x.element);
    std::swap(this->arrayLength, x.arrayLength);
    std::swap(this->listSize, x.listSize);
}

int main()
{
    arrayListWithSwap<int> x, y;
    for(int i  = 0; i < 10; i++)
        x.insert(i, i+1);
    for(int i  = 0; i < 8; i++)
        y.insert(i, 26);    
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    x.swap(y);

    std::cout << x << std::endl << "x.capacity() = " << x.capacity() << " x.listSize = " << x.size() << std::endl;
    std::cout << y << std::endl << "y.capacity() = " << y.capacity() << " y.listSize = " << y.size() << std::endl;
}