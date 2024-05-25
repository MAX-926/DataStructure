#include"../case/6-2.h"

template<class T>
class chainListWithSet:public chain<T>
{
    public:
        chainListWithSet(int initialCapacity = 10):chain<T>(initialCapacity){}
        void set(int theIndex, const T &element);
};

template<class T>
void chainListWithSet<T>::set(int theIndex, const T &element)
{
    this->checkIndex(theIndex);
    chainNode<T>* current = (this->firstNode);
    for(int i = 0; i < theIndex; i++)
        current = current->next;
    current->element = element;
    return;
}

int main()
{
    chainListWithSet<int> x;
    for(int i = 0; i < 5; i++)
        x.insert(i, i+1);
    cout << x << endl;
    x.set(0, 26);
    x.set(0, 36);
    x.set(4, 26);
    cout << x << endl;
}