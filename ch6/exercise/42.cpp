#include"../case/6-13.h"

template<class T>
void split(circularListWithHeader<T> &a, circularListWithHeader<T> &b, const circularListWithHeader<T> &c)//O(aSize + bSize + cSize)
{//a中包含索引为奇数的元素，b包含其余元素
    a.clear();//O(aSize)
    b.clear();//O(bSize)
    int index = 0, lsC = c.size();
    auto iterC = c.begin();
    while(index < lsC)//O(lsC), 即O(cSize)
    {
        if(index % 2 != 0)
        {
            a.push_back(*(iterC++));
            index++;
        }
        else
        {
            b.push_back(*(iterC++));
            index++;
        }
    }
}

template<class T>
void circularListWithHeader<T>::split(circularListWithHeader<T> &a, circularListWithHeader<T> &b)//O(aSize + bSize + thisSize)
{//利用*this构建a，b
    a.clear();//O(aSize)
    b.clear();//O(bSize)
    int index = 0, lsC = listSize;
    chainNode<T>* headA = a.headerNode, *headB = b.headerNode, *head = headerNode, *currentNode = headerNode->next;
    while(index < lsC)//O(lsC)
    {
        if(index % 2 != 0)
        {
            a.headerNode->next = currentNode;
            a.headerNode = a.headerNode->next;
            currentNode = currentNode->next;
            a.listSize++;
            --listSize;
            index++;
        }
        else
        {
            b.headerNode->next = currentNode;
            b.headerNode = b.headerNode->next;
            currentNode = currentNode->next;
            b.listSize++;
            --listSize;
            index++;
        }
    }
    a.lastNode = a.headerNode;
    a.lastNode->next = headA;
    a.headerNode = headA;

    b.lastNode = b.headerNode;
    b.lastNode->next = headB;
    b.headerNode = headB;

    headerNode = head;
    headerNode->next = headerNode;
}

int main()
{
    circularListWithHeader<int> a, b, c;
    for(int i = 0; i < 20; i++)
        c.insert(i, i);
    std::cout << "a:" << a << std::endl;
    std::cout << "b:" << b << std::endl;
    std::cout << "c:" << c << std::endl;
    // split(a, b, c);
    c.split(a, b);
    std::cout << "a:" << a << std::endl;
    std::cout << "b:" << b << std::endl;
    std::cout << "c:" << c << std::endl;
    // a.insert(0, 1);
    // b.insert(0, 2);
    // a.push_back(26);
    // b.push_back(26);
    // std::cout << "a:" << a << std::endl;
    // std::cout << "b:" << b << std::endl;
    // std::cout << "c:" << c << std::endl;

}