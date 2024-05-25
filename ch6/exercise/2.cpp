#include"../case/6-2.h"

template<class T>
class chainListWithSetSize:public chain<T>
{
    public:
        chainListWithSetSize(int initialCapacity = 10):chain<T>(initialCapacity){}
        void setSize(int theSize);
};

template<class  T>
void chainListWithSetSize<T>::setSize(int theSize)
{
    if(this->listSize == 0){return;}
    if(theSize < 0)
    {
        ostringstream s;
        s << "theSize = " << theSize << " Must be >= 0";
        throw IllegalParameter(s.str());
    }
    if(theSize == 0)
    {
        while(this->firstNode)
        {
            chainNode<T>* x = (this->firstNode)->next;
            delete (this->firstNode);
            (this->firstNode) = x;
        }
        return;
    }
    if(theSize >= this->listSize)
    {
        cout << "theSize = " << theSize << " is bigger than listSize = " << this->listSize << endl;
        return;
    }
    else
    {
        chainNode<T>* currentNode = this->firstNode;
        for(int currentIndex = 0; currentIndex < theSize-1; currentIndex++)
            currentNode = currentNode->next;
        chainNode<T>* deleteList = currentNode->next;
        currentNode->next = NULL;
        this->listSize = theSize;
        while(deleteList)
        {
            chainNode<T>* tmp = deleteList->next;
            delete deleteList;
            deleteList = tmp;
        }
    }
}


int main()
{
    chainListWithSetSize<int> x;
    for(int i = 0; i < 5; i++)
        x.insert(i ,i+1);
    cout << x << endl;
    x.setSize(0);
    cout << x << endl;
}