#include"../case/6-13.h"

template<class T>
void circularListWithHeader<T>::reverse()//O(listSize^2)
{
    chainNode<T>* currentNode = headerNode->next, *targetNode;
    int targetIndex = listSize-1;
    for(int i = 0; i < listSize/2; i++)//O(listSize/2)
    {
        targetNode = headerNode->next;
        for(int j = 0; j < targetIndex; j++)//O(targetIndex), targetIndex:listSize-1, listSize-2, ..., listSize/2
            targetNode = targetNode->next;
        std::swap(currentNode->element, targetNode->element);
        --targetIndex;
        currentNode = currentNode->next;
    }    
}

template<class T>
void non_memberReverse(circularListWithHeader<T> &x)
{
    x.reverse();
}

int main()
{
    circularListWithHeader<int> x;
    for(int i = 0; i < 2; i++)
        x.insert(i, i+1);
    std::cout << x << std::endl;
    // x.reverse();
    non_memberReverse(x);
    std::cout << x << std::endl;
}