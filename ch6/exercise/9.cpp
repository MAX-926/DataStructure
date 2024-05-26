#include"../case/6-2.h"
using namespace std;
template<class T>
class chainListWithOperatorLess:public chain<T>
{
    public:
        chainListWithOperatorLess(int initialCapacity = 10):chain<T>(initialCapacity){}
        bool operator<(const chainListWithOperatorLess<T> &theChain)const;
};

template<class T>
bool chainListWithOperatorLess<T>::operator<(const chainListWithOperatorLess<T> &theChain)const
{
    if(this->listSize != theChain.listSize) return false;
    if(this->listSize == 0 || theChain.listSize == 0) return false;
    chainNode<T>* currentNode1 = this->firstNode, *currentNode2 = theChain.firstNode;
    while((currentNode1) && (currentNode1->element < currentNode2->element))
    {
        currentNode1 = currentNode1->next;
        currentNode2 = currentNode2->next;
    }
    if(currentNode1 == NULL) return true;
    return false;
}

int main()
{
    chainListWithOperatorLess<char> x, y;
    char c = 'a';
    for(char i = 0; i < 5; i++)
    {
        x.insert(i, c);
        y.insert(i, c+1);
        c++;
    }
    // y.erase(0);
    cout << x << endl;
    cout << y << endl;
    cout << (x < y) << endl;
}