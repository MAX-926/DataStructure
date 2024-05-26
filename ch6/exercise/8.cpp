#include"../case/6-2.h"
using namespace std;
template<class T>
class chainListWithOperatorEqual:public chain<T>
{
    public:
        chainListWithOperatorEqual(int initialCapacity = 10):chain<T>(initialCapacity){}
        bool operator!=(const chainListWithOperatorEqual<T> &theChain)const;
};

template<class T>
bool chainListWithOperatorEqual<T>::operator!=(const chainListWithOperatorEqual<T> &theChain)const
{
    if(this->listSize != theChain.listSize) return true;
    chainNode<T>* currentNode1 = this->firstNode, *currentNode2 = theChain.firstNode;
    while((currentNode1) && (currentNode1->element == currentNode2->element))
    {
        currentNode1 = currentNode1->next;
        currentNode2 = currentNode2->next;
    }
    if(currentNode1 == NULL) return false;
    return true;
}

int main()
{
    chainListWithOperatorEqual<int> x, y;
    for(int i = 0; i < 5; i++)
    {
        x.insert(i, i);
        y.insert(i, i);
    }
    // y.erase(0);
    cout << x << endl;
    cout << y << endl;
    cout << (x != y) << endl;
}