#include"../case/5-3.h"

template<class T>
class arrayListWithRemoveRange:public arrayList<T>
{
    public:
        arrayListWithRemoveRange(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void removeRange(int startIndex, int endIndex);
};

template<class T>
void arrayListWithRemoveRange<T>::removeRange(int startIndex, int endIndex)
{
    this->checkIndex(startIndex);
    this->checkIndex(endIndex);
    if(startIndex > endIndex) throw IllegalParameter("startIndex must be smaller than endIndex");
    int newLength = endIndex - startIndex + 1;
    newLength  = this->arrayLength - newLength;
    T* tmp = new T[newLength];//O(newLength)
    std::copy(this->element, (this->element) + startIndex, tmp);
    std::copy((this->element) + endIndex + 1, (this->element) + (this->listSize), tmp + startIndex);//total O(listSize - newLength)
    delete [](this->element);
    (this->arrayLength) = newLength;
    (this->listSize) = (this->listSize) - (endIndex - startIndex + 1);
    (this->element) = tmp;
}

int main()
{
    arrayListWithRemoveRange<int> x;
    for(int i = 0; i < 10; i++)
        x.insert(i, i+1);
    std::cout << x << std::endl;
    try
    {
    x.removeRange(6, 5);
    }catch(IllegalParameter ip)
    {
        ip.outputMessage();
    }
    std::cout << x << std::endl;
}