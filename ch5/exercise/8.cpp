#include"../case/5-3.h"

template<class T>
class arrayListWithOperatorEqual:public arrayList<T>
{
    public:
        arrayListWithOperatorEqual():arrayList<T>(10){}
        bool operator==(const arrayListWithOperatorEqual &x) const;
};

template<class T>
bool arrayListWithOperatorEqual<T>::operator==(const arrayListWithOperatorEqual<T> &x)const
{
    bool equal = true;
    for(int i = 0; i < this->listSize && equal; i++)//O(listSize)
        equal = (this->element)[i] == x.element[i];
    return equal;
}

int main()
{
    arrayListWithOperatorEqual<int> x, y;
    // for(int i = 0; i < 5; i++)
    // {
    //     x.insert(i, i+1);
    //     y.insert(i, i+2);
    // }
    // std::cout << x.capacity();
    std::cout << (x==y);
}