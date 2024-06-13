#include"55.cpp"
#include"57.cpp"
#include"../../Tool.h"

template<class T>
void merge(const doubleCircularListWithHeader<T> &a, const doubleCircularListWithHeader<T> &b, doubleCircularListWithHeader<T> &c)
{
    auto iterA = a.begin(), iterB = b.begin();
    int indexA = 0, indexB = 0;
    int lsA = a.size(), lsB = b.size();
    bool crossed = true;
    for(; indexA < lsA && indexB < lsB; )
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
void doubleCircularListWithHeader<T>::merge(doubleCircularListWithHeader<T> &a, doubleCircularListWithHeader<T> &b)
{
    clear();
    if(!a.listSize)
    {
        if(!b.listSize) return;
        else{listLinker(b); return;}
    }
    else
    {
        if(!b.listSize){listLinker(a); return;}
    }
    bool crossed = true;
    bdChainNode<T>* headA = a.header, *headB = b.header, *head = header;
    int indexA = 0, indexB = 0;

    a.header = a.header->next;
    b.header = b.header->next;

    // if(a.header->element < b.header->element)
    // {
    //     header->next = a.header;
    //     a.header->previous = header;
    //     indexA++;
    //     a.header = a.header->next;
    //     header = header->next;
    // }
    // else if(a.header->element > b.header->element)
    // {
    //     header->next = b.header;
    //     b.header->previous = header;
    //     indexB++;
    //     b.header = b.header->next;
    //     header = header->next;
    // }
    // else //a.header->element == b.header->element
    // {
    //     header->next = a.header;
    //     a.header->previous = header;
    //     indexA++;
    //     crossed = !crossed;
    //     a.header = a.header->next;
    //     header = header->next;
    // }
    while(indexA < a.listSize && indexB < b.listSize)
    {
        if(a.header->element < b.header->element)
        {
            header->next = a.header;
            a.header->previous = header;
            indexA++;
            a.header = a.header->next;
            header = header->next;
        }
        else if(a.header->element > b.header->element)
        {
            header->next = b.header;
            b.header->previous = header;
            indexB++;
            b.header = b.header->next;
            header = header->next;
        }
        else //a.header->element == b.header->element
        {
            if(crossed)
            {
                header->next = a.header;
                a.header->previous = header;
                indexA++;
                crossed = !crossed;
                a.header = a.header->next;
                header = header->next;
            }
            else
            {
                header->next = b.header;
                b.header->previous = header;
                indexB++;
                crossed = !crossed;
                b.header = b.header->next;
                header = header->next;
            }
        }
    }
    while(indexA < a.listSize)
    {
        header->next = a.header;
        a.header->previous = header;
        indexA++;
        a.header = a.header->next;
        header = header->next;
    }
    while(indexB < b.listSize)
    {
        header->next = b.header;
        b.header->previous = header;
        indexB++;
        b.header = b.header->next;
        header = header->next;
    }

    header->next = head;
    head->previous = header;
    listSize = a.listSize + b.listSize;
    header = head;

    a.header = headA;
    b.header = headB;
    a.header->next = a.header;
    b.header->next = b.header;
    a.header->previous = a.header;
    b.header->previous = b.header;
    a.listSize = 0;
    b.listSize = 0;
}

// int main()
// {
//     doubleCircularListWithHeader<int> a, b, c;
//     for(int i = 0; i < 0; i++)
//     {
//         a.insert(i, i);
//     }
//     for(int i = 0; i < 0; i++)
//     {
//         b.insert(i, i+4);
//     }
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
//     c.merge(a, b);
//     // merge(a, b, c);
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
//     __HeaderList_fluencyTest<doubleCircularListWithHeader<int>>(c);
// }