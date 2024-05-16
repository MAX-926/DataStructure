#include"../case/5-3.h"

template<class T>
class arrayListWithOperatorUnequal:public arrayList<T>
{
    public:
        arrayListWithOperatorUnequal():arrayList<T>(10){}
        bool operator!=(const arrayListWithOperatorUnequal &x) const;
};

template<class T>
bool arrayListWithOperatorUnequal<T>::operator!=(const arrayListWithOperatorUnequal<T> &x)const
{
    bool Unequal = true;
    for(int i = 0; i < this->listSize && Unequal; i++)//O(liseSize)
        Unequal = (this->element)[i] != x.element[i];
    return Unequal;
 }
int main()
{
    arrayListWithOperatorUnequal<int> x, y;
   for(int i = 0; i < 5; i++)
    {
        x.insert(i, i+1);
        y.insert(i, i+1);
    }
    std::cout << x.capacity();
    std::cout << (x!=y);
}