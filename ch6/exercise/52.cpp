#include"49.h"

template<class T>
void meld(const doubleCircularList<T> &a, const doubleCircularList<T> &b, doubleCircularList<T> &c)
{
    int indexA = 0, indexB = 0;
    int lsA = a.size(), lsB = b.size();
    auto iterA = a.begin(), iterB = b.begin(); 
    if(!lsA)
    {
        c.clear();
        for(; indexB < lsB; indexB++)
            c.push_back(*(iterB++));
        return;
    }
    else if(!lsB)
    {
        c.clear();
        for(; indexA < lsA; indexA++)
            c.push_back(*(iterA++));
        return;
    }
    else
    {
        c.clear();
        bool crossed = true;
        while(indexA < lsA && indexB < lsB)
        {
            if(crossed)
            {
                c.push_back(*(iterA++));
                indexA++;
                crossed = !crossed;
            }
            else
            {
                c.push_back(*(iterB++));
                indexB++;
                crossed = !crossed;
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

template<class T>
void doubleCircularList<T>::meld(doubleCircularList<T> &a, doubleCircularList<T> &b)
{
    int lsA = a.size(), lsB = b.size();
    if(!lsA)
    {
        if(!lsB) return;
        else
        {
            clear();
            firstNode = b.firstNode;
            lastNode = b.lastNode;
            listSize = b.listSize;

            b.firstNode = NULL;
            b.lastNode = NULL;
            b.listSize = 0;

            return;
        }
    }
    if(!lsB)
    {
        if(!lsA) return;
        else
        {
            clear();
            firstNode = a.firstNode;
            lastNode = a.lastNode;
            listSize = a.listSize;

            a.firstNode = NULL;
            a.lastNode = NULL;
            a.listSize = 0;

            return;
        }
    }
    else
    {
        clear();
        int indexA = 0, indexB = 0;
        firstNode = a.firstNode;
        a.firstNode = a.firstNode->next;
        indexA++;
        // bdChainNode<T> *currentNodeA = a.firstNode, *currentNodeB = b.firstNode, *currentNode = firstNode;
        bdChainNode<T> *currentNode = firstNode;
        bool crossed = false;
        while(indexA < lsA && indexB < lsB)
        {
            if(crossed)
            {
                currentNode->next = a.firstNode;
                a.firstNode->previous = currentNode;
                a.firstNode = a.firstNode->next;
                indexA++;
                currentNode = currentNode->next;
                crossed = !crossed;
            }
            else
            {
                currentNode->next = b.firstNode;
                b.firstNode->previous = currentNode;
                b.firstNode = b.firstNode->next;
                indexB++;
                currentNode = currentNode->next;
                crossed = !crossed;
            }
        }
        while(indexA < lsA)
        {
            currentNode->next = a.firstNode;
            a.firstNode->previous = currentNode;
            a.firstNode = a.firstNode->next;
            currentNode = currentNode->next;
            indexA++;
        }
        while(indexB < lsB)
        {
            currentNode->next = b.firstNode;
            b.firstNode->previous = currentNode;
            b.firstNode = b.firstNode->next;
            currentNode = currentNode->next;
            indexB++;
        }
        lastNode = currentNode;
        currentNode->next = firstNode;
        firstNode->previous = lastNode;
        listSize = lsA + lsB;

        a.firstNode = NULL;
        b.firstNode = NULL;
        a.lastNode = NULL;
        b.lastNode = NULL;
        a.listSize = 0;
        b.listSize = 0;
    }   
}

int main()
{
    doubleCircularList<char> a, b, c;
    for(int i = 0; i < 1; i++)
    {
        a.insert(i, 'a');
        // b.insert(i, 'b');
    }
    for(int i = 0; i < 1; i++)
    {
        // a.insert(i, 'a');
        b.insert(i, 'b');
    }
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    // meld(a, b, c);
    c.meld(a, b);
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    c.push_back('c');
    c.insert(0, 'c');
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    auto iterC = c.end();
    for(int i = 0; i < 2*c.size(); i++)
        std::cout << *(iterC--) << " ";
}