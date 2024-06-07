//使用双向链表，完成merge方法
#include"43.cpp"
//19. non-member-merge
template<class T>
void merge(const doublyLinkedList<T> &a, const doublyLinkedList<T> &b, doublyLinkedList<T> &c)//O(cSize + aSize + bSize)
{
    c.clear();//O(cSize)
    auto iterA = a.begin(), iterB = b.begin();
    int indexA = 0, lsA = a.size(), indexB = 0, lsB = b.size();
    bool crossed  = true;
    while(indexA < lsA && indexB < lsB)
    {
        if(*(iterA) < *(iterB))
        {
            c.push_back(*(iterA++));
            indexA++;
        }
        else if(*(iterA) > *(iterB))
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
void doublyLinkedList<T>::merge(doublyLinkedList<T> &a, doublyLinkedList<T> &b)
{
    if(!(a.firstNode && b.firstNode)) return;
    clear();
    bool crossed = true;
    bdChainNode<T>* headA = a.firstNode, *headB = b.firstNode;
    while(a.firstNode != NULL && b.firstNode != NULL)
    {
        if(a.firstNode->element < b.firstNode->element)
        {
            if(!listSize)
            {
                firstNode = a.firstNode;
                lastNode = firstNode;
                a.firstNode = a.firstNode->next;
                firstNode->next = NULL;
                listSize++;
                continue;
            }
            firstNode->next = a.firstNode;
            a.firstNode->previous = firstNode;
            a.firstNode = a.firstNode->next;
            firstNode = firstNode->next;
        }
        else if(a.firstNode->element > b.firstNode->element)
        {
            if(!listSize)
            {
                firstNode = b.firstNode;
                lastNode = firstNode;
                b.firstNode = b.firstNode->next;
                firstNode->next = NULL;
                listSize++;
                continue;
            }
            firstNode->next = b.firstNode;
            b.firstNode->previous = firstNode;
            b.firstNode = b.firstNode->next;
            firstNode = firstNode->next;
        }
        else// a.firstNode == b.firstNode
        {
            if(crossed)
            {
                if(!listSize)
                {
                    firstNode = a.firstNode;
                    lastNode = firstNode;
                    a.firstNode = a.firstNode->next;
                    firstNode->next = NULL;
                    crossed = !crossed;
                    listSize++;
                    continue;
                }
                firstNode->next = a.firstNode;
                a.firstNode->previous = firstNode;
                a.firstNode = a.firstNode->next;
                firstNode = firstNode->next;
                crossed = !crossed;
            }
            else
            {
                firstNode->next = b.firstNode;
                b.firstNode->previous = firstNode;
                b.firstNode = b.firstNode->next;
                firstNode = firstNode->next;
                crossed = !crossed;
                // if(!listSize)
                // {
                //     firstNode = b.firstNode;
                //     lastNode = firstNode;
                //     b.firstNode = b.firstNode->next;
                //     firstNode->next = NULL;
                //     crossed = !crossed;
                //     continue;
                // }
            }
        }
    }
    while(a.firstNode != NULL)
    {
        firstNode->next = a.firstNode;
        a.firstNode->previous = firstNode;
        a.firstNode = a.firstNode->next;
        firstNode = firstNode->next;
    }
    while(b.firstNode != NULL)
    {
        firstNode->next = b.firstNode;
        b.firstNode->previous = firstNode;
        b.firstNode = b.firstNode->next;
        firstNode = firstNode->next;
    }
    lastNode = firstNode;
    firstNode = headA->element >= headB->element ? headB : headA;
    listSize = a.listSize + b.listSize;
    a.listSize = 0;
    b.listSize = 0;
}

// int main()
// {
//     doublyLinkedList<int> a, b, c;
//     for(int i = 0; i < 10; i++)
//     {
//         a.insert(i, i+1);
//         b.insert(i, i);
//     }
//     std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
//     // merge(a, b, c);
//     c.merge(a, b);
//     std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
//     c.insert(0, 26);
//     c.insert(c.size()-1, 26);
//     c.push_back(28);
//     std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
// }