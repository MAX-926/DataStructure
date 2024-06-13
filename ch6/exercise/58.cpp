//meld

#include"55.cpp"
#include"56.cpp"
#include"57.cpp"
#include"../../Tool.h"

template<class T>
void meld(const doubleCircularListWithHeader<T> &a, const doubleCircularListWithHeader<T> &b, doubleCircularListWithHeader<T> &c)
{
    c.clear();
    auto iterA = a.begin(), iterB = b.begin();
    int lsA = a.size(), lsB = b.size();
    int indexA = 0, indexB = 0;
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

template<class T>
void doubleCircularListWithHeader<T>::meld(doubleCircularListWithHeader<T> &a, doubleCircularListWithHeader<T> &b)
{
    clear();
    if(!a.listSize)
    {
        if(!b.listSize) return;
        else
        {
            listLinker(b);
            return;
        }
    }
    else
    {
        if(!b.listSize)
        {
            listLinker(a);
            return;
        }
    }
    int indexA = 0, indexB = 0;
    bool crossed = true;
    bdChainNode<T>* headA = a.header, *headB = b.header, *head = header;
    a.header = a.header->next;
    b.header = b.header->next;

    // header->next = a.header;
    // a.header->previous = header;

    // indexA++;
    // a.header = a.header->next;
    // header = header->next;

    while(indexA < a.listSize && indexB < b.listSize)
    {
        if(crossed)
        {
            header->next = a.header;
            a.header->previous = header;
            indexA++;
            a.header = a.header->next;
            header = header->next;
            crossed = !crossed;
        }
        else
        {
            header->next = b.header;
            b.header->previous = header;
            indexB++;
            b.header = b.header->next;
            header = header->next;
            crossed = !crossed;
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
    a.header->previous = a.header;
    b.header->next = b.header;
    b.header->previous = b.header;
    a.listSize = 0;
    b.listSize = 0;
}

// int main()
// {
//     doubleCircularListWithHeader<char> a, b, c;
//     for(int i = 0; i < 10; i++)
//     {
//         a.insert(i, 'a');
//         b.insert(i, 'b');
//     }
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
//     // meld(a, b, c);
//     c.meld(a, b);
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
//     c.reverse();
//     std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
//     __HeaderList_fluencyTest<doubleCircularListWithHeader<char>>(c);
// }