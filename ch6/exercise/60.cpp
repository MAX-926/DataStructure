#include"55.cpp"
#include"../../Tool.h"

template<class T>
void doubleCircularListWithHeader<T>::split(doubleCircularListWithHeader<T> &a, doubleCircularListWithHeader<T> &b)
{
    //a中包含索引为奇数：
    a.clear();
    b.clear();
    if(!listSize) return;
    bdChainNode<T>* headA = a.header, *headB = b.header, *head = header;
    header = header->next;
    bool crossed = true;
    while(header->next != head)
    {
        if(crossed)
        {
            b.header->next = header;
            header->previous = b.header;
            crossed = !crossed;
            b.header = b.header->next;
            header = header->next;
            b.listSize++;
        }
        else
        {
            a.header->next = header;
            header->previous = a.header;
            crossed = !crossed;
            a.header = a.header->next;
            header = header->next;
            a.listSize++;
        }
    }
    if(crossed)
    {
        b.header->next = header;
        header->previous = b.header;
        b.header = b.header->next;
        header = header->next;
        b.listSize++;
    }
    else
    {
        a.header->next = header;
        header->previous = a.header;
        a.header = a.header->next;
        header = header->next;
        a.listSize++;
    }
    a.header->next = headA;
    headA->previous = a.header;
    a.header = headA;

    b.header->next = headB;
    headB->previous = b.header;
    b.header = headB;

    header = head;
    header->next = header;
    header->previous = header;
    listSize = 0;
}

template<class T>
void split(doubleCircularListWithHeader<T> &a, doubleCircularListWithHeader<T> &b, const doubleCircularListWithHeader<T> &c)
{
    a.clear();
    b.clear();
    if(!c.size()) return;
    bool crossed = !crossed;
    auto iter = c.begin(), END = c.end();
    while(iter != END)
    {
        if(crossed)
        {
            b.push_back(*(iter++));
            crossed = !crossed;
        }
        else
        {
            a.push_back(*(iter++));
            crossed = !crossed;
        }
    }
    if(crossed)
    {
        b.push_back(*(iter));
    }
    else
    {
        a.push_back(*(iter));
    }
}

int main()
{
    doubleCircularListWithHeader<int> a, b, c;
    for(int i = 0; i < 5; i++)
        c.insert(i, i);
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    // c.split(a, b);
    split(a, b, c);
    std::cout << "a: " << a << std::endl << "b: " << b << std::endl << "c: " << c << std::endl;
    __HeaderList_fluencyTest<doubleCircularListWithHeader<int>>(a);
    __HeaderList_fluencyTest<doubleCircularListWithHeader<int>>(b);
    __HeaderList_fluencyTest<doubleCircularListWithHeader<int>>(c);
}