#ifndef DOUBLE_CIRCULAR_LIST_WITH_HEADER_H
#define DOUBLE_CIRCULAR_LIST_WITH_HEADER_H

#include"../case/bidirectionalChainNode.h"
#include"../case/6-11.h"
#include<iostream>
#include<sstream>

template<class T>
class doubleCircularListWithHeader:public extendedLinearList<T>
{
    public:
        doubleCircularListWithHeader();
        doubleCircularListWithHeader(const doubleCircularListWithHeader<T> &theDCLWH);
        ~doubleCircularListWithHeader();
        //ADT methods:
        bool empty()const{return listSize == 0;}
        int size()const{return listSize;}
        T& get(int theIndex)const;
        int indexOf(const T& theElement)const;
        void insert(int theIndex, const T& theElement);
        void erase(int theIndex);
        void push_back(const T& theElement);
        void clear();
        void output(std::ostream& out)const;
        class iterator
        {
            public:
                iterator(bdChainNode<T>* theNode = nullptr){node = theNode;}
                //ADT methods:
                //1.forward:
                iterator& operator++()
                {
                    node = node->next;
                    return *this;
                }
                iterator operator++(int)
                {
                    iterator old = *this;
                    node = node->next;
                    return old;
                }
                //2.backward:
                iterator& operator--()
                {
                    node = node->previous;
                    return *this;
                }
                iterator operator--(int)
                {
                    iterator old = *this;
                    node = node->previous;
                    return old;
                }
                //3.解引用:
                T& operator*()const
                {
                    return node->element;
                }
                T* operator->()const
                {
                    return &(node->element);
                }
                //4.equalization verify:
                bool operator==(const iterator& theIter)const
                {
                    return node == theIter.node;
                }
                bool operator!=(const iterator& theIter)const
                {
                    return node != theIter.node;
                }
            protected:
                bdChainNode<T>* node;
        };//
        iterator begin()const{return iterator(header->next);}
        iterator end()const{return iterator(header->previous);}
        //56.cpp reverse():
        void reverse();
        //57.cpp listLinker():
        void listLinker(doubleCircularListWithHeader<T> &theDCLWH);
        //58.cpp meld():
        void meld(doubleCircularListWithHeader<T> &a, doubleCircularListWithHeader<T> &b);
        //59.cpp merge():
        void merge(doubleCircularListWithHeader<T> &a, doubleCircularListWithHeader<T> &b);
        //60.cpp split():
        void split(doubleCircularListWithHeader<T> &a, doubleCircularListWithHeader<T> &b);
    protected:
        void checkIndex(int theIndex)const;
        bdChainNode<T>* header;
        // bdChainNode<T>* lastNode;
        int listSize;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const doubleCircularListWithHeader<T> &theDCLWH)
{
    theDCLWH.output(out);
    return out;
}

template<class T>
void doubleCircularListWithHeader<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
doubleCircularListWithHeader<T>::doubleCircularListWithHeader()
{
    header = new bdChainNode<T>();
    header->next = header;
    header->previous = header;
    listSize = 0;
}

template<class T>
doubleCircularListWithHeader<T>::doubleCircularListWithHeader(const doubleCircularListWithHeader<T> &theDCLWH)
{
    header = new bdChainNode<T>(theDCLWH.header->element);
    bdChainNode<T>* theCurrentNode = theDCLWH.header->next, *currentNode = header;
    while(theCurrentNode != theDCLWH.header)
    {
        currentNode->next = new bdChainNode<T>(theCurrentNode->element);
        currentNode->next->previous = currentNode;
        currentNode = currentNode->next;
        theCurrentNode = theCurrentNode->next;
    }
    currentNode->next = header;
    header->previous = currentNode;
    listSize = theDCLWH.listSize;
}

template<class T>
doubleCircularListWithHeader<T>::~doubleCircularListWithHeader()
{
    while(header->next->next != header)
    {
        bdChainNode<T>* deleteNode = header->next;
        header->next = header->next->next;
        // std::cout << "delete Node: " << deleteNode->element << std::endl;
        delete deleteNode;
    }
    // std::cout << "delete Node: " << header->next->element << std::endl;
    delete header->next;
}

template<class T>
T& doubleCircularListWithHeader<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    bdChainNode<T>* currentNode = header->next;
    for(int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template<class T>
int doubleCircularListWithHeader<T>::indexOf(const T& theElement)const
{
    bdChainNode<T>* currentNode = header->next;
    header->element = theElement;
    int index = 0;
    for(; currentNode->element != theElement; currentNode = currentNode->next, index++);
    if(currentNode == header) return -1;
    else return index;
}

template<class T>
void doubleCircularListWithHeader<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(theIndex == 0)
    {
        header->next = new bdChainNode<T>(theElement, header->next, header);
        header->next->next->previous = header->next;
        //! header->previous = header->next;
        ++listSize;
        return;
    }
    else
    {
        bdChainNode<T>* currentNode = header->next;
        for(int i = 0; i < theIndex-1; i++)
            currentNode = currentNode->next;
        // bdChainNode<T>* nextNode = currentNode->next;
        currentNode->next = new bdChainNode<T>(theElement, currentNode->next, currentNode);
        currentNode->next->next->previous = currentNode->next;
        ++listSize;
        return;
    }
}

template<class T>
void doubleCircularListWithHeader<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    bdChainNode<T>* currentNode = header->next;
    if(theIndex == 0)
    {
        bdChainNode<T>* deleteNode = header->next;
        header->next = header->next->next;
        header->next->previous = header;
        delete deleteNode;
        --listSize;
        return;
    }
    for(int i = 0; i < theIndex -1; currentNode = currentNode->next, i++);
    bdChainNode<T>* deleteNode = currentNode->next;
    currentNode->next = currentNode->next->next;
    currentNode->next->previous = currentNode;
    // if(theIndex == listSize)
    // {
    //     // currentNode->next = header;
    //     header->previous = currentNode->next;
    // }
    --listSize;
    return;
}

template<class T>
void doubleCircularListWithHeader<T>::push_back(const T& theElement)
{
    bdChainNode<T>* nextNode = header->previous;
    header->previous = new bdChainNode<T>(theElement, header, nextNode);
    nextNode->next = header->previous;
    ++listSize;
    return;
}

template<class T>
void doubleCircularListWithHeader<T>::clear()
{
    while(header->next != header)
    {
        bdChainNode<T>* deleteNode = header->next;
        header->next = deleteNode->next;
        // std::cout << "delete Node: " << deleteNode->element << std::endl;
        delete deleteNode;
    }
    header->previous = header;
    listSize = 0;
    return;
}

template<class T>
void doubleCircularListWithHeader<T>::output(std::ostream& out)const
{
    if(!listSize){out << ""; return;}
    bdChainNode<T>* currentNode = header->next;
    while(currentNode != header)
    {
        out << currentNode->element << " ";
        currentNode = currentNode->next;
    }
}

#endif //DOUBLE_CIRCULAR_LIST_WITH_HEADER

// int main()
// {
//     doubleCircularListWithHeader<int> a;
//     for(int i = 0; i < 10; i++)
//     {
//         a.insert(i, i);
//     }
//     a.clear();
//     std::cout << a << std::endl;
// }