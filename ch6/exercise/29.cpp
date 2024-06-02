#include"../../ch5/case/5-1.h"
#include"../case/6-1.h"
#include<sstream>
#include<iostream>
// virtual reutrnType funName() = 0;
template<class T>
class circularList:public linearList<T>
{
    public:
    //chain methods:
        circularList();//O(1)
        ~circularList();//O(listSize)
        bool empty() const {return  firstNode == NULL;}//O(1)
        int size() const {return listSize;}//O(1)
        T& get(int theIndex)const;//wrost O(theIndex) best O(1)
        int indexOf(const T &theELement)const;//best O(1) worst O(listSize)
        void insert(int theIndex, const T &theElement);//best O(1) normal O(theIndex)
        void erase(int theIndex);//best O(1) normal O(theIndex)
    //extendedChain methods:
        void clear();//O(listSize)
        void push_back(const T &theElement);//O(1)
        void output(std::ostream &out)const;//O(listSize)
    protected:
        void checkIndex(int theIndex)const;//O(1)
        chainNode<T>* firstNode;
        chainNode<T>* lastNode;
        int listSize;
};

template<class T>
std::ostream& operator<<(std::ostream &out, const circularList<T> &CL)
{
    CL.output(out);
    return out;
}

template<class T>
circularList<T>::circularList()
{
    firstNode = 0;
    lastNode = 0;
    listSize = 0;
}

template<class T>
circularList<T>::~circularList()
{
    if(listSize == 0) return;
    while(listSize != 1)
    {
        chainNode<T>* nextNode = firstNode->next;
        // std::cout << "destroy Node:" << firstNode->element << std::endl;
        delete firstNode;
        firstNode = nextNode;
        listSize--;
    }
    // std::cout << "destroy Node:" << firstNode->element << std::endl;
    delete firstNode;
    --listSize;
    firstNode = 0;
    lastNode = 0;
}

template<class T>
void circularList<T>::checkIndex(int theIndex)const//O(1)
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
T& circularList<T>::get(int theIndex)const
{
    checkIndex(theIndex);//O(1)
    chainNode<T>* currentNode = firstNode;//O(1)
    for(int i = 0; i < theIndex; i++)//O(index)
        currentNode = currentNode->next;
    return currentNode->element;//O(1)
}

template<class T>
int circularList<T>::indexOf(const T &theElement)const
{
    chainNode<T>* currentNode = firstNode;
    int index = 0;
    while(currentNode != NULL && currentNode->element != theElement)
    {
         currentNode = currentNode->next;
         index++;
    }
    if(currentNode == NULL) return -1;
    else return index;
}

template<class T>
void circularList<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(listSize == 0)
    {
        firstNode = new chainNode<T>(theElement, NULL);// modified
        firstNode->next = firstNode;
        lastNode = firstNode;
        ++listSize;
        return;
    }
    if(theIndex == 0)
    {
        chainNode<T>* nextNode = firstNode;
        firstNode = new chainNode<T>(theElement, nextNode);
        ++listSize;
        lastNode->next = firstNode;
        // if(listSize)
        //     lastNode = firstNode;
        return;
    }
    else
    {
        chainNode<T>* currentNode = firstNode;
        for(int i = 0; i < theIndex-1; i++)//O(theIndex)
            currentNode = currentNode->next;
        if(theIndex == listSize)
        {
            currentNode->next = new chainNode<T>(theElement, firstNode);
            ++listSize;
            lastNode = lastNode->next;
            return;
        }
        else
        {
            chainNode<T>* nextNode = currentNode->next;
            currentNode->next = new chainNode<T>(theElement, nextNode);
            // if(nextNode == NULL) lastNode = currentNode->next;
            ++listSize;
            return;
        }
    }
}

template<class T>
void circularList<T>::erase(int theIndex)
{
    checkIndex(theIndex);//O(1)
    if(theIndex == 0)
    {
        if(listSize == 1)//O(1)
        {
            delete firstNode;
            firstNode = 0;
            lastNode = 0;
            --listSize;
            return;
        }
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
        --listSize;
        lastNode->next = firstNode;
        return;
    }
    chainNode<T>* currentNode = firstNode;
    for(int i = 0; i < theIndex-1; i++)//O(theIndex)
        currentNode = currentNode->next;
    chainNode<T>* nextNode = currentNode->next->next;
    delete currentNode->next;
    currentNode->next = nextNode;
    if(nextNode == firstNode)
    {
        lastNode = currentNode;
        // lastNode->next = firstNode;
    }
    --listSize;
    return;
}

template<class T>
void circularList<T>::clear()
{
    while(listSize != 1)
    {
        chainNode<T>* nextNode = firstNode->next;
        // std::cout << "delete Node:" << firstNode->element << std::endl;
        delete firstNode;
        firstNode = nextNode;
        --listSize;
    }
    delete firstNode;
    --listSize;
    firstNode = 0;
    lastNode = 0;
    return;
}

template<class T>
void circularList<T>::push_back(const T &theElement)//O(1)
{
    if(listSize == 0)
    {
        firstNode = new chainNode<T>(theElement, firstNode);
        lastNode = firstNode;
        ++listSize;
        return;
    }
    else
    {
        lastNode->next = new chainNode<T>(theElement, firstNode);
        ++listSize;
        lastNode = lastNode->next;
        return;
    }
}

template<class T>
void circularList<T>::output(std::ostream& out)const
{
    if(listSize == 0)
    {
        out << "";
        return;
    }
    chainNode<T>* currentNode = firstNode;
    while(currentNode->next != firstNode)
    // while(1)
    {
        out << currentNode->element << " ";
        currentNode = currentNode->next;
    }
    out << currentNode->element;
    return;
}

// int main()
// {
//     circularList<int> x;
//     for(int i = 0; i < 10; i++)
//         x.insert(i, i+1);
//     std::cout << x << std::endl;
//     x.clear();
//     std::cout << x << std::endl;
//     x.insert(0, 26);
//     std::cout << x << std::endl;
// }