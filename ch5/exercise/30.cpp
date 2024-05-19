#include"../case/5-3.h"

template<class T>
class arrayListWithSplit:public arrayList<T>
{
    public:
        arrayListWithSplit(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void split(arrayListWithSplit<T> &a, arrayListWithSplit<T> &b) const;
};

template<class T>
void arrayListWithSplit<T>::split(arrayListWithSplit<T> &a, arrayListWithSplit<T> &b)const
{
    int  j = 0, k = 0;
    // bool tag = ((this->listSize) % 2 == 0);
    for(int i = 0; i < (this->listSize); i++)
    {
        if(i % 2 == 0)
        {
            a.insert(j++, (this->element)[i]);
            // std::cout << "a[" << j-1 << "] = " << this->element[i] << std::endl;
        }
        else
        {
            b.insert(k++, (this->element)[i]);
            // std::cout << "b[" << k-1 << "] = " << this->element[i] << std::endl;
        }
    }
    for(; j > a.listSize && k > b.listSize; )
    {
        if(j < a.listSize)
        {
        a.element[j++].~T();
        }
        b.element[k++].~T();
    }
    // (j < a.size()) && (k < b.size()) ? a.element[j++].~T() : b.element[k++].~T();
    a.listSize = (this->listSize) - (this->listSize)/2;
    b.listSize = (this->listSize) / 2;
    a.arrayLength = a.listSize;
    b.arrayLength = b.listSize;
}

int main()
{
    arrayListWithSplit<int> a, b, c;
    for(int i = 0; i < 8; i++)
        c.insert(i, i+1);
    std::cout << c << std::endl;
    c.split(a, b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}