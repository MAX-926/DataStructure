#include"49.h"
#include"50.cpp"

template<class T>
void split(doubleCircularList<T> &a, doubleCircularList<T> &b, const doubleCircularList<T> &c)//O(a.size + b.size + c.size)
{
    a.clear();//O(a.size)
    b.clear();//O(b.size)
    auto iterC = c.begin();
    int indexC = 0;
    int lsC = c.size();
    while(indexC < lsC)//O(c.size)
    {
        if(indexC % 2 != 0)
        {
            a.push_back(*(iterC++));
            indexC++;
        }
        else
        {
            b.push_back(*(iterC++));
            indexC++;
        }
    }
}

template<class T>
void doubleCircularList<T>::split(doubleCircularList<T> &a, doubleCircularList<T> &b)//O(a.szie + b.size + listSize)
{
    a.clear();//O(a.size)
    b.clear();//O(b.size)
    if(listSize < 2)//O(1)
    {
        if(listSize < 1) return;//O(1)
        else//O(1)
        {
            b.firstNode = firstNode;
            b.lastNode = lastNode;
            b.listSize = listSize;

            firstNode = NULL;
            lastNode = NULL;
            listSize = 0;
            
            return;
        }
    }
    else//O(listSize)
    {
        int index = 0;
        //b的首节点处理
        b.firstNode = firstNode;
        b.lastNode = b.firstNode;
        ++b.listSize;
        index++;

        firstNode = firstNode->next;

        b.firstNode->next = b.firstNode;
        b.firstNode->previous = b.firstNode;
        //a的首节点处理
        a.firstNode = firstNode;
        a.lastNode = a.firstNode;

        firstNode = firstNode->next;
        
        ++a.listSize;
        ++index;
        a.firstNode->next = a.firstNode;
        a.firstNode->previous = a.firstNode;

        bdChainNode<T>* currentNodeA = a.firstNode, *currentNodeB = b.firstNode;

        while(index < listSize)//O(thisList last elements)
        {
            if(index % 2 != 0)
            {
                currentNodeA->next = firstNode;
                firstNode->previous = currentNodeA;
                firstNode = firstNode->next;
                currentNodeA = currentNodeA->next;
                ++a.listSize;
                ++index;
            }
            else
            {
                currentNodeB->next = firstNode;
                firstNode->previous = currentNodeB;
                firstNode = firstNode->next;
                currentNodeB = currentNodeB->next;
                ++b.listSize;
                index++;
            }
        }
        a.lastNode = currentNodeA;
        b.lastNode = currentNodeB;
        a.lastNode->next = a.firstNode;
        b.lastNode->next = b.firstNode;
        a.firstNode->previous = a.lastNode;
        b.firstNode->previous = b.lastNode;

        firstNode = NULL;
        lastNode = NULL;
        listSize = 0;
        return;
    }
}

int main()
{
    doubleCircularList<int> a, b, c;
    for(int i = 0; i < 5; i++)
        c.insert(i, i);
    std::cout << "a: " << a << std::endl <<  "b: " << b << std::endl << "c: " << c << std::endl;
    // split(a, b, c);
    c.split(a, b);
    std::cout << "a: " << a << std::endl <<  "b: " << b << std::endl << "c: " << c << std::endl;
    a.reverse();
    b.reverse();
    std::cout << "a: " << a << std::endl <<  "b: " << b << std::endl << "c: " << c << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl << "b.size() = " << b.size() << std::endl;
    auto iterA = a.end(), iterB = b.end();
    for(int i = 0; i < 10; i++)
        std::cout << *(iterA--) << " ";
    std::cout << std::endl;
    for(int i = 0; i < 9; i++)
        std::cout << *(iterB--) << " ";
}