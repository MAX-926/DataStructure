#include"49.h"
// #include"50.cpp"

template<class T>
void merge(const doubleCircularList<T> &a, const doubleCircularList<T> &b, doubleCircularList<T> &c)
{
    c.clear();
    auto iterA = a.begin(), iterB = b.begin();
    int indexA = 0, indexB = 0;
    int lsA = a.size(), lsB = b.size();
    bool crossed = true;
    while(indexA < lsA && indexB < lsB)//O(lsA + lsB)
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
void doubleCircularList<T>::merge(doubleCircularList<T> &a, doubleCircularList<T> &b)//O(initial_listSize + lsA + lsB)
{
    int lsA = a.size(), lsB = b.size();
    if(!lsA && !lsB) return;//O(1)
    else if(!lsA)//O(initial_listSize)
    {
        clear();//O(listSize)
        firstNode = b.firstNode;
        lastNode = b.lastNode;
        listSize = b.listSize;

        b.firstNode = NULL;
        b.lastNode = NULL;
        b.listSize = 0;
        return;
    }
    else if(!lsB)//O(initial_listSize)
    {
        firstNode = a.firstNode;
        lastNode = a.lastNode;
        listSize = a.listSize;

        a.firstNode = NULL;
        a.lastNode = NULL;
        a.listSize = 0;

        return;
    }
    else//O(initial_listSize + lsA + lsB)
    {
        clear();//O(listSize)
        int indexA = 0, indexB = 0;
        bool crossed = true;
        if(a.firstNode->element > b.firstNode->element)//O(1)
        {
            firstNode = b.firstNode;
            b.firstNode = b.firstNode->next;
            indexB++;
        }
        else if(a.firstNode->element < b.firstNode->element)//O(1)
        {
            firstNode = a.firstNode;
            a.firstNode = a.firstNode->next;
            indexA++;
        }
        else//O(1)
        {
            firstNode = a.firstNode;
            a.firstNode = a.firstNode->next;
            indexA++;
            crossed = !crossed;
        }
        bdChainNode<T>* head = firstNode;
        while(indexA < lsA && indexB < lsB)//total underline: O(lsA + lsB)
        {
            if(a.firstNode->element < b.firstNode->element)//O(1)
            {
                firstNode->next = a.firstNode;
                a.firstNode = a.firstNode->next;
                firstNode->next->previous = firstNode;
                firstNode = firstNode->next;
                indexA++;
            }
            else if(a.firstNode->element > b.firstNode->element)//O(1)
            {
                firstNode->next = b.firstNode;
                b.firstNode = b.firstNode->next;
                firstNode->next->previous = firstNode;
                firstNode = firstNode->next;
                indexB++;
            }
            else//a.firstNode->element == b.firstNode->element, O(1)
            {
                if(crossed)//O(1)
                {
                    firstNode->next = a.firstNode;
                    a.firstNode = a.firstNode->next;
                    firstNode->next->previous = firstNode;
                    firstNode = firstNode->next;
                    indexA++;
                    crossed = !crossed;
                }
                else//O(1)
                {               
                    firstNode->next = b.firstNode;
                    b.firstNode = b.firstNode->next;
                    firstNode->next->previous = firstNode;
                    firstNode = firstNode->next;
                    indexB++;
                    crossed = !crossed;
                }
            }
        }
        while(indexA < lsA)//O(last A elements)
        {
            firstNode->next = a.firstNode;
            a.firstNode = a.firstNode->next;
            firstNode->next->previous = firstNode;
            firstNode = firstNode->next;
            indexA++;
            if(indexA == lsA)
            {
                lastNode = firstNode;
            }
        }
        while(indexB < lsB)//O(last B elements)
        {
            firstNode->next = b.firstNode;
            b.firstNode = b.firstNode->next;
            firstNode->next->previous = firstNode;
            firstNode = firstNode->next;            
            indexB++;
            if(indexB == lsB)
            {
                lastNode = firstNode;
            }
        }
        firstNode = head;
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
    // doubleCircularList<int> a, b, c;
    // for(int i = 0; i < 10; i++)
    // {
    //     a.insert(i, i+1);
    //     b.insert(i, i+1);
    // }
    // std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    // merge(a, b, c);
    // std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    // c.reverse();
    // std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    doubleCircularList<int> a ,b, c;
    for(int i = 0; i < 3; i++)
    {
        // a.insert(i, i+1);
        b.insert(i, i+8);
        c.insert(i, 2);
    }
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    // c.merge(a, b);
    merge(a, b, c);
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    c.push_back(26);
    c.insert(0, 25);
    auto iterC = c.end();
    for(int i = 0; i < 10; i++)
    {
        std::cout << *(iterC--) << " ";
    }
}