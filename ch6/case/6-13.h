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
        //NEW ADT METHODS:
        void push_back(const T &theElement);
        void clear();
        void reverse();
        void meld(const circularListWithHeader<T> &a, const circularListWithHeader<T> &b);
        void meld(circularListWithHeader<T> &a, circularListWithHeader<T> &b);
        //iterator
        class iterator
        {
            public:
                iterator(chainNode<T>* node = NULL){theNode = node;}
                //forward op
                iterator& operator++(){theNode = theNode->next; return *this;}
                iterator operator++(int){iterator old(theNode); theNode = theNode->next; return old;}
                //equalization verify
                bool operator==(const iterator &iter)const{return iter.theNode == theNode;}
                bool operator!=(const iterator &iter)const{return iter.theNode != theNode;}
                //解引用
                T& operator*()const{return theNode->element;}
                T* operator->()const{return &(theNode->element);}
            protected:
                struct chainNode<T>* theNode;
        };
        iterator begin()const{return iterator(headerNode->next);}
        iterator end()const{return iterator(lastNode);}
    protected:
        void checkIndex(int theIndex)const;
        chainNode<T>* headerNode;
        chainNode<T>*  lastNode;
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
    // if(theIndex == 0)//Be carefull!!
    // {
    //     chainNode<T>* nextNode = headerNode->next;
    //     headerNode->next = new chainNode<T>(theElement, nextNode);
    //     ++listSize;
    //     return;
    // }
    // chainNode<T>* currentNode = headerNode->next;
    chainNode<T>* currentNode = headerNode;
    for(int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    chainNode<T>* nextNode = currentNode->next;
    currentNode->next = new chainNode<T>(theElement, nextNode);
    if(theIndex == listSize)
        lastNode = currentNode->next;
    ++listSize;
    return;
}

template<class T>
void circularListWithHeader<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    if(theIndex == 0)
    {
        chainNode<T>* deleteNode = headerNode->next;
        headerNode->next = deleteNode->next;
        delete deleteNode;
        --listSize;
        return;
    }
    chainNode<T>* currentNode = headerNode->next;
    for(int i = 0; i < theIndex-1; i++)
        currentNode = currentNode->next;
    chainNode<T>* deleteNode = currentNode->next;
    currentNode->next = currentNode->next->next;
    delete deleteNode;
    if(theIndex == listSize-1)
        lastNode = currentNode;
    --listSize;
    return;
}

template<class T>
circularListWithHeader<T>::circularListWithHeader()
{
    //創建空節點
    headerNode = new chainNode<T>(0);
    lastNode = 0;
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

template<class T>
void circularListWithHeader<T>::push_back(const T &theElement)//O(1)
{
    if(!listSize)//如果当前线性表为空：
    {
        headerNode->next = new chainNode<T>(theElement);
        headerNode->next->next = headerNode;
        lastNode = headerNode->next;
        ++listSize;
        return;
    }
    else
    {
        lastNode->next = new chainNode<T>(theElement);
        lastNode = lastNode->next;
        lastNode->next = headerNode;
        ++listSize;
        return;
    }
}

template<class T>
void circularListWithHeader<T>::clear()//O(listSize)
{
    if(!listSize) return;
    else
    {
        while(headerNode->next && headerNode->next != headerNode)
        {
            chainNode<T>* deleteNode = headerNode->next;
            headerNode->next = headerNode->next->next;
            delete deleteNode;
        }
        listSize = 0;
        lastNode = 0;
    }
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