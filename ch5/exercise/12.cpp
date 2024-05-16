#include"../case/5-3.h"
#include<iterator>

template<class T>
class arrayListWithPopBack:public arrayList<T>
{
    public:
        arrayListWithPopBack(int theInitialCapacity = 10):arrayList<T>(theInitialCapacity), initialCapacity(theInitialCapacity){}
        void pop_back();
    private:
        int initialCapacity;
};

template<class T>
void arrayListWithPopBack<T>::pop_back()
{
    if(this->listSize == 0) return;
    if(this->listSize-1 < this->arrayLength/4)
    {
        int newLength = std::max(this->arrayLength/2, initialCapacity);
        T* tmp = new T[newLength];//O(newLength)
        std::copy(this->element, (this->element)+(this->listSize)-1, tmp);//O(listSize-2)
        delete [](this->element);
        this->element = tmp;
        (this->listSize)--;
        this->arrayLength = newLength;
    }
    else
    {
        (this->listSize)--;
    }
}

int main()
{
    arrayListWithPopBack<int> x(4);
    for(int i = 0; i < 10; i++)
        x.insert(i, i+1);
    // x.pop_back();
    // x.pop_back();
   for(int i = 0; i < 8; i++)
        x.pop_back();
    std::cout << x << std::endl << x.capacity() << std::endl;
    x.pop_back();
    std::cout << x << std::endl << x.capacity();
}