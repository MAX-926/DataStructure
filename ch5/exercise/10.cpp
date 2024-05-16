#include"../case/5-3.h"

template<class T>
class arrayListWithOperatorLessThan:public arrayList<T>
{
    public:
        arrayListWithOperatorLessThan(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        bool operator<(const arrayListWithOperatorLessThan<T> &x) const;
};

template<class T>
bool arrayListWithOperatorLessThan<T>::operator<(const arrayListWithOperatorLessThan<T> &x)const
{
    if(x.listSize == 0)return false;
    if((this->listSize) == 0) return true;
    int i;
    int numOfEle = (this->listSize) >= x.listSize ? x.listSize : (this->listSize);
    for(i = 0; i < numOfEle && x.element[i] > (this->element)[i]; i++);
    if(i == numOfEle) return true;
    else return false;
}

int main()
{
    arrayListWithOperatorLessThan<int> x, y;
    for(int i = 0; i < 5; i++)
    {
        x.insert(i, i-1);
        // y.insert(i, i);
    }
    std::cout << (x < y);
}