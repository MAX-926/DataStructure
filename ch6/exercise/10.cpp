#include"../case/6-2.h"

template<class T>
class chainListWithSwap:public chain<T>
{
    public:
        chainListWithSwap(int initialCapacity = 10):chain<T>(initialCapacity){}
        void swap(chainListWithSwap<T> &theChain);
};
// void chainListWithSwap<T>::swap(chainListWithsSwap<T> &theChain)
template<class T>
void chainListWithSwap<T>::swap(chainListWithSwap<T> &theChain)
{
    chainNode<T>* tmpNode = (this->firstNode);
    this->firstNode = theChain.firstNode;
    theChain.firstNode = tmpNode;
}

int main()
{
    chainListWithSwap<int> x, y;
    for(int i = 0; i < 6; i++)
    {
        x.insert(i ,i);
        y.insert(i, i+1);
    }
    cout << x << endl << y << endl;
    x.swap(y);
    cout << x << endl << y << endl;
}