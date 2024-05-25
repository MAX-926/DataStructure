#include"../case/6-2.h"

template<class T>
class chainListWithRemoveRange:public chain<T>
{
    public:
        chainListWithRemoveRange(int initialCapacity = 10):chain<T>(10){}
        void removeRange(int fromIndex, int toIndex);
};

template<class T>
void chainListWithRemoveRange<T>::removeRange(int fromIndex, int toIndex)//O(toIndex+1 + (toIndex-fromIndex+1))
{
    if((fromIndex < 0 || toIndex < 0) || (fromIndex >= (this->listSize) || toIndex >= (this->listSize)))
    {
        ostringstream s;
        s << "invalid index! please check whether toIndex and fromIndex is in the range of [0:" << (this->listSize)-1 << "]";
        throw IllegalParameter(s.str());
    }
    if(fromIndex > toIndex)
    {
        ostringstream s;
        s << "fromIndex = " << fromIndex << " toIndex = " << toIndex << " ,fromIndex must be <= toIndex";
        throw IllegalParameter(s.str());
    }
    chainNode<T>* edge1 = (this->firstNode), *edge2;
    for(int i = 0; i < fromIndex-1; i++)
        edge1 = edge1->next;
    edge2 = edge1->next;
    for(int i = 0; i <= toIndex-fromIndex; i++)
        edge2 = edge2->next;
    //deletion
    chainNode<T>* currentDeleteNode = edge1->next;
    while(currentDeleteNode != edge2)
    {
        chainNode<T>* nextNode = currentDeleteNode->next;
        delete currentDeleteNode;
        currentDeleteNode = nextNode;
    }
    edge1->next = edge2;
    this->listSize -= toIndex-fromIndex+1;
    if(!edge2) edge1->next = NULL;
    return;
}

int main()
{
    chainListWithRemoveRange<int> x;
    for(int i = 0; i < 10; i++)
        x.insert(i, i+1);
    cout << x << endl;
    try
    {
    x.removeRange(1, 1);
    }catch(IllegalParameter ip){ip.outputMessage();}
    cout << x << endl;
}