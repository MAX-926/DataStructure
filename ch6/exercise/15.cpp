#include"../case/6-2.h"

template<class T>
class chainListWithReverse:public chain<T>
{
    public:
        chainListWithReverse(int initialCapacity = 10):chain<T>(initialCapacity){}
        void reverse();
};

template<class T>
void chainListWithReverse<T>::reverse()
{
    if(this->listSize == 0) return;
    chainNode<T>* current = this->firstNode;
    chainNode<T>* target = NULL;
    for(int i = 0; i < (this->listSize)/2; i++)
    {
        T tmp = current->element;
        target = current;
        for(int j = i; j < (this->listSize)-1-i; j++)
            target = target->next;
        current->element = target->element;
        target->element = tmp;
        current = current->next;
    }
}

int main()
{
    chainListWithReverse<int> x;
    for(int i = 0; i < 20; i++)
        x.insert(i, i+1);
    cout << x << endl;
    x.reverse();
    cout << x << endl;
}