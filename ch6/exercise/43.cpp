//design class doublyLinkedList
#include<iostream>
#include<sstream>
#include"../case/6-11.h"
#include"../case/bidirectionalChainNode.h"

template<class T>
class doublyLinkedList:public extendedLinearList<T>
{
    public:
        doublyLinkedList():extendedLinearList<T>(), firstNode(0), lastNode(0), listSize(0){}
        doublyLinkedList(const doublyLinkedList<T> &theDLL);
        ~doublyLinkedList();
        bool empty()const{return listSize == 0;}
        int size()const{return listSize;}
        T& get(int theIndex)const;
        int indexOf(const T& theElements)const;
        void insert(int theIndex, const T& theElement);
        void erase(int theIndex);
        void push_back(const T& theElement);
        void clear();
        void output(std::ostream& out)const;
        //KEY_POINT:iterator:
        class iterator
        {
            public:
                iterator(bdChainNode<T>* theNode):node(theNode){}
                iterator(const iterator &theIter):node(theIter.node){}
                ~iterator(){}
                //解引用
                T& operator*()const{return node->element;}
                T* operator->()const{return &node->element;}
                //forwards
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
                //backwards
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
                //equalization verify
                bool operator==(const iterator &theIter)const{ return theIter.node == node; }
                bool operator!=(const iterator &theIter)const{ return theIter.node != node; }
            protected:
                bdChainNode<T>* node;
        };
        iterator begin()const{ return iterator(firstNode); }
        iterator end()const{ return iterator(lastNode); }
        //new ADT methods:
        void listLinker(doublyLinkedList<T> &theDLL);
        //44.cpp reverse():
        void reverse();
        //46.cpp meld():
        void meld(doublyLinkedList<T> &a, doublyLinkedList<T> &b);
        //47.cpp merge():
        void merge(doublyLinkedList<T> &a, doublyLinkedList<T> &b);
    protected:
        void checkIndex(int theIndex)const;
        bdChainNode<T>* firstNode;
        bdChainNode<T>* lastNode;
        int listSize;
};

template<class T>
doublyLinkedList<T>::~doublyLinkedList()
{
    clear();
}

template<class T>
doublyLinkedList<T>::doublyLinkedList(const doublyLinkedList<T> &theDLL)
{
    if(theDLL.listSize == 0)
    {
        firstNode = 0;
        lastNode = 0;
        listSize = 0;
        return;
    }
    else
    {
        // firstNode = new bdChainNode<T>(theDLL.firstNode->element, NULL, NULL);
        // lastNode = firstNode;
        // ++listSize;
        listSize = 0;
        firstNode = NULL;
        lastNode = NULL;
        bdChainNode<T>* currentNode = theDLL.firstNode;
        while(currentNode != NULL)
        {
            push_back(currentNode->element);
            currentNode = currentNode->next;
        }
    }
}

template<class T>
std::ostream& operator<<(std::ostream& out, const doublyLinkedList<T> &theDLL)
{
    theDLL.output(out);
    return out;
}

template<class T>
void doublyLinkedList<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
T& doublyLinkedList<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    bdChainNode<T>* currentNode = firstNode;
    for(int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template<class T>
int doublyLinkedList<T>::indexOf(const T& theElement)const
{
    if(!listSize) return -1;
    bdChainNode<T>* currentNode = firstNode;
    int index = 0;
    for(;index < listSize && currentNode->element != theElement; index++)
        currentNode = currentNode->next;
    if(index == listSize) return -1;
    else return index;
}

template<class T>
void doublyLinkedList<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(theIndex == 0)
    {
        if(!listSize)
        {
            firstNode = new bdChainNode<T>(theElement, NULL, NULL);
            lastNode = firstNode;
            listSize++;
            return;
        }
        else
        {
            firstNode = new bdChainNode<T>(theElement, firstNode, NULL);
            firstNode->next->previous = firstNode;
            ++listSize;
            return;
        }
    }
    if(theIndex == listSize)
    {
        lastNode->next = new bdChainNode<T>(theElement, NULL, lastNode);
        ++listSize;
        lastNode = lastNode->next;
        return;
    }
    else
    {
        bdChainNode<T>* currentNode = firstNode;
        for(int i = 0; i < theIndex-1; i++)
            currentNode = currentNode->next;
        bdChainNode<T>* nextNode = currentNode->next;
        currentNode->next = new bdChainNode<T>(theElement, nextNode, currentNode);
        currentNode->next->next->previous = currentNode->next;
        listSize++;
        return;
    }
}

template<class T>
void doublyLinkedList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    if(theIndex == 0)
    {
        bdChainNode<T>* deleteNode = firstNode;
        firstNode = firstNode->next;
        delete deleteNode;
        --listSize;
        if(!listSize)
        {
            firstNode = NULL;
            lastNode = NULL;
        }
        return;
    }
    if(theIndex == listSize-1)
    {
        bdChainNode<T>* deleteNode = lastNode;
        lastNode = lastNode->previous;
        lastNode->next = NULL;
        delete deleteNode;
        --listSize;
        if(!listSize)
        {
            firstNode = 0;
            lastNode = 0;
        }
        return;
    }
    else
    {
        // bdChainNode<T>* currentNode = firstNode;
        //可以优化：如果需要删除的节点距离前端近，则从前端接近；否则从后端接近：
        if(theIndex <= listSize/2)
        {
            bdChainNode<T>* currentNode = firstNode;
            for(int i = 0; i < theIndex-1; i++)
                currentNode = currentNode->next;
            bdChainNode<T>* deleteNode = currentNode->next;
            currentNode->next = deleteNode->next;
            deleteNode->next->previous = currentNode;
            delete deleteNode;
            --listSize;
            return;
        }
        else
        {
            bdChainNode<T>* currentNode = lastNode;
            //0, 1, 2, 3, 4, 5, 6
            for(int i = 0; i < (listSize - 1) - theIndex - 1; i++)//为什么是减2而不是减1？？ 原因：listSize - 1 - theIndex表达lastNode到theIndex的距离， 再减一表达到达前一个的距离
                currentNode = currentNode->previous;
            bdChainNode<T>* deleteNode = currentNode->previous;
            currentNode->previous = deleteNode->previous;
            deleteNode->previous->next = currentNode;
            delete deleteNode;
            --listSize;
            return;
        }
    }
}

template<class T>
void doublyLinkedList<T>::push_back(const T& theElement)
{
    if(!listSize)
    {
        firstNode = new bdChainNode<T>(theElement, NULL, NULL);
        lastNode = firstNode;
        ++listSize;
        return;
    }
    else
    {
        lastNode->next = new bdChainNode<T>(theElement, NULL, lastNode);
        lastNode = lastNode->next;
        ++listSize;
        return;
    }
}

template<class T>
void doublyLinkedList<T>::clear()
{
    while(firstNode != NULL)
    {
        bdChainNode<T>* nextNode = firstNode->next;
        // std::cout << "delete Node: " << firstNode->element << std::endl; 
        delete firstNode;
        firstNode = nextNode;
    }
    firstNode = 0;
    listSize = 0;
    lastNode = 0;
    return;
}

template<class T>
void doublyLinkedList<T>::output(std::ostream& out)const
{
    if(listSize == 0) 
    {
        out << "";
        return;
    }
    bdChainNode<T>* currentNode = firstNode;
    while(currentNode != NULL)
    {
        out << currentNode->element << " ";
        currentNode = currentNode->next;
    }
    return;
}

template<class T>
void doublyLinkedList<T>::listLinker(doublyLinkedList<T> &theDLL)
{
    if(listSize == 0)
    {
        firstNode = theDLL.firstNode;
        lastNode = theDLL.lastNode;
        listSize = theDLL.listSize;
        theDLL.firstNode = NULL;
        theDLL.lastNode = NULL;
        theDLL.listSize = 0;
    }
    else
    {
        lastNode->next = theDLL.firstNode;
        theDLL.firstNode->previous = lastNode;
        lastNode = theDLL.lastNode;
        listSize += theDLL.listSize;
        theDLL.firstNode = NULL;
        theDLL.lastNode = NULL;
        theDLL.listSize = 0;
    }
}

// int main()
// {
//     doublyLinkedList<int> x;
//     for(int i = 0; i < 3; i++)
//         x.insert(i, i+1);
//     doublyLinkedList<int> y = x;
//     x.listLinker(y);
//     x.push_back(26);
//     std::cout << "x:" << x << std::endl << "y:" << y << std::endl;
//     // auto iter = x.begin();
//     auto iter = x.end();
//     // while(iter != x.end())
//     while(iter != x.begin())
//     {
//     //     // std::cout << *(iter++) << " ";
//         std::cout << *(iter--) << " ";
//     }
//     std::cout << *iter << std::endl;
//     // std::cout << *iter << std::endl;
//     // std::cout << x.size();
//     // std::cout << std::endl;
//     // std::cout << "&x-&y:" << &x-&y << std::endl;
//     // x.insert(0, 26);
//     // std::cout << x << std::endl;
//     // x.erase(3);
//     // x.push_back(26);
//     // // x.insert(0, 26);
//     // x.clear();
//     // x.insert(0, 1);
//     // x.push_back(26);
//     // std::cout << x << std::endl;
// }