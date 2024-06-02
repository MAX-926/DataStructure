//为循环链表实现meld函数

#include"29.cpp"

template<class T>
class circularListWithMeld:public circularList<T>
{
    public:
        circularListWithMeld():circularList<T>(){}
        void meld(const circularListWithMeld<T> &a, const circularListWithMeld<T> &b);
};

template<class T>
void circularListWithMeld<T>::meld(const circularListWithMeld<T> &a, const circularListWithMeld<T> &b)
{
    if(!a.listSize)
    {
        chainNode<T>* currentNode = b.firstNode;
        while(currentNode->next != firstNode)
        {
            this->push_back(currentNode->element);
            currentNode = currentNode->next;
            this->listSize = a.listSize;
            return;
        }
        

    }
    chainNode<T>* currentNode;
}