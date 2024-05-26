
#include"../case/6-2.h"

template<class T>
class chainListWithOperatorLocate:public chain<T>
{
    public:
        chainListWithOperatorLocate(int initialCapacity = 10):chain<T>(initialCapacity){}
        T& operator[](int theIndex);
};

template<class T>
T& chainListWithOperatorLocate<T>::operator[](int theIndex)
{
    this->checkIndex(theIndex);
    chainNode<T>* current = (this->firstNode);
    for(int i = 0; i < theIndex; i++)
        current = current->next;
    return current->element;
}

int main()
{
    chainListWithOperatorLocate<int> x;
    for(int i = 0; i < 5; i++)
        x.insert(i,i+1);
    cout << x << endl;
    // try
    // {
    x[0] = 0.5;
    int y = x[0];
    cout << x << endl;
    // }catch(IllegalParameter ip){ip.outputMessage();}
}