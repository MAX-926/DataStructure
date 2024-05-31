#ifndef CH6_6_13_H
#define CH6_6_13_H

#include"6-1.h"
#include"../../ch5/case/5-1.h"
#include<sstream>
//使用循环链表可以使链表的代码简洁且执行高效
template<class T>
class circularListWithHeader:linearList<T>
{
    public:
        circularListWithHeader();
        ~circularListWithHeader();
        bool empty()const{return headerNode->next == headerNode;}
        int size()const{return listSize;}
        T& get(int theIndex)const;
        int indexOf(const T &theElement)const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(std::ostream& out)const;
    protected:
        void checkIndex(int theIndex)const;
        chainNode<T>* headerNode;
        int listSize;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const circularListWithHeader<T> &clwh)
{
    clwh.output(out);
    return out;
}

template<class T>
circularListWithHeader<T>::~circularListWithHeader()
{
    // chainNode<T>* nextNode = headerNode->next;
    // while(nextNode != NULL)
    // {
    //     chainNode<T>* next = nextNode->next;
    //     delete nextNode;
    //     nextNode = next;
    // }
    // headerNode->next = headerNode;

    while(headerNode->next != headerNode && headerNode->next != NULL)
    {
        chainNode<T>* nextNode = headerNode->next;
        headerNode->next = nextNode->next;
        delete nextNode;
    }
    headerNode->next = headerNode;
}

template<class T>
void circularListWithHeader<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
T& circularListWithHeader<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    chainNode<T>* currentNode = headerNode->next;
    for(int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template<class T>
void circularListWithHeader<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    chainNode<T>* currentNode = headerNode->next;
    for(int i = 0; i < theIndex-1; i++)
        currentNode = currentNode->next;
    chainNode<T>* nextNode = currentNode->next;
    currentNode->next = new chainNode<T>(theElement, nextNode);
    ++listSize;
    return;
}

template<class T>
void circularListWithHeader<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    chainNode<T>* currentNode = headerNode->next;
    for(int i = 0; i < theIndex-1; i++)
        currentNode = currentNode->next;
    chainNode<T>* deleteNode = currentNode->next;
    currentNode->next = currentNode->next->next;
    delete deleteNode;
    --listSize;
    return;
}

template<class T>
circularListWithHeader<T>::circularListWithHeader()
{
    //創建空節點
    headerNode = new chainNode<T>(0);
    headerNode->next = headerNode;//circularList为空表的条件
    listSize = 0;
}

template<class T>
int circularListWithHeader<T>::indexOf(const T &theElement)const
{
    //返回元素首次出现的索引， 若元素不存在则返回-1
    headerNode->element = theElement;
    //在链表中搜索元素theElement
    chainNode<T>* currentNode = headerNode->next;
    int index = 0;
    while(theElement != currentNode->element)
    {
        currentNode = currentNode->next;
        index++;
    }
    if(currentNode == headerNode) return -1;
    else return index;
}

template<class T>
void circularListWithHeader<T>::output(std::ostream& out)const
{
    if(listSize == 0)
    {
        out << "";
        return;
    }
    chainNode<T>* currentNode = headerNode->next;
    while(currentNode != headerNode)
    {
        out << currentNode->element << " ";
        currentNode = currentNode->next;
    }
    return;
}

// template<class T>
// int circularListWithHeader<T>::indexOf(const T &theElement)const
// {
//     headerNode->element = theElement;
//     chainNode<T>* currentNode = headerNode->next;
//     int index = 0;
//     while(currentNode->element != theElement)
//     {
//         currentNode = currentNode->next;
//         index++;
//     }
//     if(currentNode == headerNode) return -1;
//     else return index;
// }
#endif //CH6_6_13_H