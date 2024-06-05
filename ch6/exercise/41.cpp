//merge
//为circularListWithHeader编写merge
#include"../case/6-13.h"

template<class T>
void merge(const circularListWithHeader<T> &a, const circularListWithHeader<T> &b, circularListWithHeader<T> &c)
{
    c.clear();
    int indexA = 0, indexB = 0;
    int lsA = a.size(), lsB = b.size();
    bool crossed = true;
    auto iterA = a.begin(), iterB = b.begin();
    for(; indexA < lsA && indexB < lsB; )
    {
        if(*iterA < *iterB)
        {
            c.push_back(*(iterA++));
            indexA++;
        }
        else if(*iterA > *iterB)
        {
            c.push_back(*(iterB++));
            indexB++;
        }
        else
        {
            if(crossed)
            {
                c.push_back(*(iterA++));
                crossed = !crossed;
                indexA++;
            }
            else
            {
                c.push_back(*(iterB++));
                crossed = !crossed;
                indexB++;
            }
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

template<class T>
void circularListWithHeader<T>::merge(circularListWithHeader<T> &a, circularListWithHeader<T> &b)
//在这个算法中， 抛弃节点时不要将节点作为headerNode，这样会导致后续索引headerNode->next时出现错误：因为在获取nextNode前就修改了previous的next
//不应该依赖一个会发生修改的节点去索引下一个值！！！
{
    clear();
    int lsA = a.listSize, lsB = b.listSize;
    int indexA = 0, indexB = 0;
    bool crossed = true;
    chainNode<T>* head = headerNode, *headA = a.headerNode, *headB = b.headerNode;

    a.headerNode = a.headerNode->next;
    b.headerNode = b.headerNode->next;
    
    // chainNode<T>* currentNodeA = a.headerNode->next, *currentNodeB = b.headerNode->next;
    for(; indexA < lsA && indexB < lsB; )
    {
        // ! if(a.headerNode->next->element < b.headerNode->next->element)//使用迭代器优化对链条数据的访问
        if(a.headerNode->element < b.headerNode->element)//使用迭代器优化对链条数据的访问
        {
            headerNode->next = a.headerNode;
            //!  headerNode->next = a.headerNode->next;
            
            a.headerNode = a.headerNode->next;
            headerNode = headerNode->next;
            indexA++;
        }
        // ! else if(a.headerNode->next->element > b.headerNode->next->element)
        else if(a.headerNode->element > b.headerNode->element)
        {
            headerNode->next = b.headerNode;
            // ! headerNode->next = b.headerNode->next;

            b.headerNode = b.headerNode->next;
            headerNode = headerNode->next;
            indexB++;
        }
        else
        {
            if(crossed)
            {
                headerNode->next = a.headerNode;
                // ! headerNode->next = a.headerNode->next;

                a.headerNode = a.headerNode->next;
                headerNode = headerNode->next;
                crossed  = !crossed;
                indexA++;                
            }
            else
            {
                headerNode->next = b.headerNode;
                // ! headerNode->next = b.headerNode->next;
                
                b.headerNode = b.headerNode->next;
                headerNode = headerNode->next;
                crossed  = !crossed;
                indexB++;    
            }
        }
    }
    while(indexA < lsA)
    {
        headerNode->next = a.headerNode;
        //! headerNode->next = a.headerNode->next;

        a.headerNode = a.headerNode->next;
        headerNode = headerNode->next;
        indexA++;
        if(indexA == lsA)
        {
            lastNode = headerNode;
            lastNode->next = head;
            // break;
        }
    }
    while(indexB < lsB)
    {
        headerNode->next = b.headerNode;
        //! headerNode->next = b.headerNode->next;

        b.headerNode = b.headerNode->next;
        headerNode = headerNode->next;
        indexB++;
        if(indexB == lsB)
        {
            lastNode = headerNode;
            lastNode->next = head;
            // break;
        }
    }
    listSize = lsA + lsB;
    headerNode = head;
    a.headerNode = headA;
    b.headerNode = headB;
    a.listSize = 0;
    b.listSize = 0;
    a.headerNode->next = a.headerNode;
    b.headerNode->next = b.headerNode;
}

int main()
{
    circularListWithHeader<int> a, b, c;
    for(int i = 0; i < 1; i++)
    {
        a.insert(i, 15);
        b.insert(i, 0);
    }
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
    // merge(a, b, c);
    c.merge(a, b);
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
    // c.insert(0, 26);
    // c.erase(0);
    // c.erase(9);
    // c.push_back(26);
    // std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
}
