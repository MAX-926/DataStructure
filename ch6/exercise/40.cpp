//meld：交替融汇a, b链表的节点元素
//为带有头节点的循环链表编写meld
#include"../case/6-13.h"

template<class T>
void circularListWithHeader<T>::meld(circularListWithHeader<T> &a, circularListWithHeader<T> &b)//O(a.size + b.size)
{
    int lsA = a.size(), lsB = b.size();//O(1)
    if(!(lsA + lsB)) return;//O(1)
    int indexA = 0, indexB = 0;
    bool crossed = true;
    chainNode<T>* currentNode = headerNode, *currentNodeA = a.headerNode->next, *currentNodeB = b.headerNode->next;
    for(; indexA < lsA && indexB < lsB; )//以下操作性能表现O(a.size + b.size)
    {
        if(crossed)
        {
            currentNode->next = currentNodeA;
            currentNode = currentNode->next;
            currentNodeA = currentNodeA->next;
            indexA++;
            crossed = !crossed;
        }
        else
        {
            currentNode->next = currentNodeB;
            currentNode = currentNode->next;
            currentNodeB = currentNodeB->next;
            indexB++;
            crossed = !crossed;
        }
    }
    while(indexA < lsA)
    {
        currentNode->next = currentNodeA;
        currentNode = currentNode->next;
        currentNodeA = currentNodeA->next;
        if(indexA+1 == lsA) lastNode = currentNode;
        indexA++;
    }
    while(indexB < lsB)
    {
        currentNode->next = currentNodeB;
        currentNode = currentNode->next;
        currentNodeB = currentNodeB->next;
        if(indexB+1 == lsB) lastNode = currentNode;
        indexB++;
    }
    listSize = lsA + lsB;
    lastNode->next = headerNode;
    a.headerNode->next = a.headerNode;
    b.headerNode->next = b.headerNode;
    a.listSize = 0;
    b.listSize = 0;
}

template<class T>
void circularListWithHeader<T>::meld(const circularListWithHeader<T> &a, const circularListWithHeader<T> &b)
{
    clear();
    // auto iterA = a.begin(), iterB = b.begin();
    chainNode<T>* currentNodeA = a.headerNode->next, *currentNodeB = b.headerNode->next;
    int indexA = 0, indexB = 0, lsA = a.size(), lsB = b.size();
    if(!(lsA+lsB)) return;
    bool crossed = true;
    for(; indexA < lsA && indexB < lsB; )
    {
        if(crossed)
        {
            push_back(currentNodeA->element);
            indexA++;
            currentNodeA = currentNodeA->next;
            crossed = !crossed;
        }
        else
        {
            push_back(currentNodeB->element);
            indexB++;
            currentNodeB = currentNodeB->next;
            crossed = !crossed;
        }
    }
    while(indexA < lsA)
    {
        push_back(currentNodeA->element);
        indexA++;
        currentNodeA = currentNodeA->next;
    }
    while(indexB < lsB)
    {
        push_back(currentNodeB->element);
        indexB++;
        currentNodeB = currentNodeB->next;
    }
}

template<class T>
void non_memberMeld(const circularListWithHeader<T> &a, const circularListWithHeader<T> &b, circularListWithHeader<T> &c)//O(a.size + b.size)
{
    //利用a， b的元素进行meld
    if(!(a.size() + b.size())) return;//O(1)
    else if(!a.size())//O(b.size)
    {
        auto iterB = b.begin();
        for(int index = 0; index < b.size(); index++)
            c.push_back(*(iterB++));
        return;
    }
    else if(!b.size())//O(a.size)
    {
        auto iterA = a.begin();
        for(int i = 0; i < a.size(); i++)
            c.push_back(*(iterA++));
        return;
    }
    else//O(a.size + b.size)
    {
        auto iterA = a.begin(), iterB = b.begin();
        bool crossed = true;
        int indexA = 0, indexB = 0;
        int lsA = a.size(), lsB = b.size(); 
        for(; indexA < lsA && indexB < lsB; )
        {
            if(crossed)
            {
                c.push_back(*(iterA++));
                indexA++;
                crossed = !crossed;
                continue;
            }
            else
            {
                c.push_back(*(iterB++));
                indexB++;
                crossed = !crossed;
                continue;
            }
        }
        while(indexA < lsA)
        {
            c.push_back(*(iterA++));
            indexA++;
        }
        while(indexB < lsB)
        {
            c.push_back(*(iterB++));
            indexB++;
        }
    }
}


int main()
{
    circularListWithHeader<char> a, b, c;
    for(int i = 0 ; i < 3; i++)
    {
        a.insert(i, 'a');
        // b.insert(i, 'b');
    }
    for(int i = 0 ; i < 3; i++)
    {
        // a.insert(i, 'a');
        b.insert(i, 'b');
    }
    std::cout << "a:" << a << std::endl;
    std::cout << "b:" << b << std::endl;
    std::cout << "c:" << c << std::endl;
    // non_memberMeld(a, b, c);
    c.meld(a, b);
    std::cout << "a:" << a << std::endl;
    std::cout << "b:" << b << std::endl;
    std::cout << "c:" << c << std::endl;
    c.push_back('m');
    c.insert(0, 'm');
    std::cout << "c:" << c.size() << std::endl;

}