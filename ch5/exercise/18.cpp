#include"../case/5-3.h"
template<class T>
class arrayListWithLastIndexOf:public arrayList<T>
{
    public:
        arrayListWithLastIndexOf(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        int lastIndexOf(const T &x) const;
};

template<class T>
int arrayListWithLastIndexOf<T>::lastIndexOf(const T &x) const
{
    int count = (this->listSize) - 1;
    T* iter;
    for(iter = (this->element) + (this->listSize) - 1; *iter != x && iter != (this->element) - 1; iter--, count--);
    if(iter != (this->element) - 1) return count;
    else return -1;
}

int main()
{
    arrayListWithLastIndexOf<int> x(10);
    // for(int i = 0; i < 10; i++)
        // x.insert(i, 26);
    x.insert(0, 8);
    x.insert(1, 3);
    x.insert(2, 7);
    x.insert(3, 4);
    x.insert(4, 6);
    x.insert(5, 7);
    x.insert(6, 5);
    x.insert(7, 2);
    x.insert(8, 3);
    x.insert(9, 5);
    std::cout << x.lastIndexOf(3);
}