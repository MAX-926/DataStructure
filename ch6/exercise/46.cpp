//meld
#include"43.cpp"

template<class T>
void meld(const doublyLinkedList<T> &a, const doublyLinkedList<T> &b, doublyLinkedList<T> &c)
{
    auto iterA = a.begin(), iterB = b.begin();
    int indexA = 0, indexB = 0, lsA = a.size(), lsB = b.size();
    bool crossed = true;
    while(indexA < lsA && indexB < lsB)
    {
        if(crossed)
        {
            c.push_back(*(iterA++));
            crossed = !crossed;
            ++indexA;
        }
        else
        {
            c.push_back(*(iterB++));
            crossed = !crossed;
            ++indexB;
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
void doublyLinkedList<T>::meld(doublyLinkedList<T> &a, doublyLinkedList<T> &b)
{
    clear();
    // bdChainNode<T>* currentNodeA = a.firstNode, *currentNodeB = b.firstNode;
    // bdChainNode<T> *head;
    bool crossed = true;
    int lsA = a.listSize, lsB = b.listSize;
    // while(indexA < lsA && indexB < lsB)
    if(lsA)
    {    
            firstNode = a.firstNode;
            a.firstNode = a.firstNode->next;
            firstNode->next = NULL;
            firstNode->previous = NULL;
            lastNode = firstNode;
            ++listSize;
            crossed = !crossed;
    }
    else if(lsB)
    {
        firstNode = b.firstNode;
        lastNode = b.lastNode;
        listSize = b.listSize;

        b.firstNode = NULL;
        b.lastNode = NULL;
        b.listSize = 0;
        return;
    }
    else return;
    bdChainNode<T>* currentNode = firstNode;
    while(a.firstNode != NULL && b.firstNode != NULL)
    {
        if(crossed)
        {
            currentNode->next = a.firstNode;
            a.firstNode->previous = currentNode;
            a.firstNode = a.firstNode->next;
            currentNode = currentNode->next;
            crossed = !crossed;
        }
        else
        {
            currentNode->next = b.firstNode;
            b.firstNode->previous = currentNode;
            b.firstNode = b.firstNode->next;
            currentNode = currentNode->next;
            crossed = !crossed;
        }
    }
    while(a.firstNode != NULL)
    {
        currentNode->next = a.firstNode;
        a.firstNode->previous = currentNode;
        currentNode = currentNode->next;
        if(a.firstNode->next == NULL)
        {
            lastNode = a.firstNode;
        }
        a.firstNode = a.firstNode->next;
    }
    while(b.firstNode != NULL)
    {
        currentNode->next = b.firstNode;
        b.firstNode->previous = currentNode;
        currentNode = currentNode->next;
        if(b.firstNode->next == NULL)
        {
            lastNode = b.firstNode;
        }    
        b.firstNode = b.firstNode->next;
    }
    listSize = a.listSize + b.listSize;
    a.lastNode = NULL;
    b.lastNode = NULL;
    a.listSize = 0;
    b.listSize = 0;
}

// int main()
// {
//     doublyLinkedList<char> a, b, c;
//     for(int i = 0; i < 10; i++)
//     {
//         a.insert(i, 'a');
//         b.insert(i, 'b');
//     }
//     std::cout << "a:" << a << std::endl;
//     std::cout << "b:" << b << std::endl;
//     std::cout << "c:" << c << std::endl;
//     // meld(a, b, c);
//     c.meld(a, b);
//     std::cout << "a:" << a << std::endl;
//     std::cout << "b:" << b << std::endl;
//     std::cout << "c:" << c << std::endl;
//     // c.push_back('c');
//     // std::cout << "a:" << a << std::endl;
//     // std::cout << "b:" << b << std::endl;
//     // std::cout << "c:" << c << std::endl;
//     // c.insert(0, 'c');
//     // std::cout << "a:" << a << std::endl;
//     // std::cout << "b:" << b << std::endl;
//     // std::cout << "c:" << c << std::endl;
//     // c.erase(0);
//     // std::cout << "a:" << a << std::endl;
//     // std::cout << "b:" << b << std::endl;
//     // std::cout << "c:" << c << std::endl;
//     // c.erase(c.size()-1);
//     // std::cout << "a:" << a << std::endl;
//     // std::cout << "b:" << b << std::endl;
//     // std::cout << "c:" << c << std::endl;
//     // c.erase(9);
//     // std::cout << "a:" << a << std::endl;
//     // std::cout << "b:" << b << std::endl;
//     // std::cout << "c:" << c << std::endl;
//     // c.erase(0);
//     // std::cout << "a:" << a << std::endl;
//     // std::cout << "b:" << b << std::endl;
//     // std::cout << "c:" << c << std::endl;
// }

int main()
{
    doublyLinkedList<int> x, y;
    for(int i = 0; i < 3; i++)
    {
        x.insert(i, i+1);
        y.insert(i, i+1);
    }
    doublyLinkedList<int> z = x;
    // x.listLinker(y);
    // x.push_back(26);
    std::cout << "x:" << x << std::endl << "y:" << y << std::endl << "z:" << z << std::endl;
    z.meld(x, y);
    // auto iter = x.begin();
    auto iter = z.end();
    // while(iter != x.end())
    while(iter != z.begin())
    {
    //     // std::cout << *(iter++) << " ";
        std::cout << *(iter--) << " ";
    }
    std::cout << *iter << std::endl;
    // std::cout << *iter << std::endl;
    // std::cout << x.size();
    // std::cout << std::endl;
    // std::cout << "&x-&y:" << &x-&y << std::endl;
    // x.insert(0, 26);
    // std::cout << x << std::endl;
    // x.erase(3);
    // x.push_back(26);
    // // x.insert(0, 26);
    // x.clear();
    // x.insert(0, 1);
    // x.push_back(26);
    // std::cout << x << std::endl;
}