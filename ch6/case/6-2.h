#ifndef CH6_6_2_H
#define CH6_6_2_H
#include"../../ch5/case/5-1.h"
#include"./6-1.h"
#include<sstream>
using namespace std;

template<class T>
class chain:public linearList<T>
{
    public:
        chain(int initialCapacity = 10);
        chain(const chain<T> &c);
        ~chain();
        //ADT methods:
        bool empty()const{return listSize == 0;}
        int size()const{return listSize;}
        T& get(int theIndex)const;
        int indexOf(const T& element)const;
        void insert(int theIndex, const T& element);
        void erase(int theIndex);
        void output(std::ostream& out)const;
        //iterator:
        class iterator//使用iterator做chain的get操作，如果逐个元素考察，可以将复杂度从O(listSize^2)降到O(listSize)
        {
            public:
                iterator(chainNode<T>* theNode = NULL){node = theNode;}
                //解引用操作符
                T& operator*()const{return node->element;}
                T* operator->()const{return &node->element;}
                //迭代器加法操作
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
                //相等检验
                bool operator==(const iterator &theIter)const
                {
                    return node == theIter.node;
                }
                bool operator!=(const iterator &theIter)const{ return node != theIter.node;}
            protected:
                struct chainNode<T>* node;
        };
        iterator begin()const{return iterator(firstNode);}
        iterator end()const{return iterator(NULL);}
        // void show()const;
        // void output()const;
    protected:
        void checkIndex(int theIndex)const;
        struct chainNode<T>*  firstNode;
        int listSize;
};

// template<class T>
// void chain<T>::show()const
// {
//     chainNode<T>* current = firstNode;
//     while(!current)
//     {
//         cout << current->element << " ";
//         current = current->next;
//     }
// }
// template<class T>
// ostream operator<<(ostream& out, const chain<T> &x)
// {
//     x.output(out);
//     return out;
// }

template<class T>
void chain<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
std::ostream& operator<<(std::ostream &out, const chain<T> &theChain)
{
    theChain.output(out);
    return out;
}

template<class T>
chain<T>::chain(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << " initialCapacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameter(s.str());
    }
    listSize = 0;
    firstNode = NULL;
}

template<class T>
chain<T>::chain(const chain<T> &theChain)
{
    listSize = theChain.listSize;
    if(listSize == 0){firstNode = NULL;return;}

    chainNode<T>* current = firstNode, *c_current = theChain.firstNode;
    firstNode = new chainNode<T>(c_current->element, NULL);
    c_current = c_current->next;
    while(c_current != NULL)
    {
        current->next = new chainNode<T>(c_current->element);
        current = current->next;
        c_current = c_current->next;
        // current->next = NULL;
    }
    current->next = NULL;
}

template<class T>
chain<T>::~chain()
{
    while(firstNode != NULL)
    {
        chainNode<T>* tmp = firstNode->next;
        delete firstNode;
        firstNode = tmp;
    }
}

template<class T>
T& chain<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    chainNode<T>* current = firstNode;
    int i = 0;
    while(i != theIndex)
    {
        current = current->next;
        i++;
    }
    return current->element;
}

template<class T>
int chain<T>::indexOf(const T &theElement)const
{
    chainNode<T>* current = firstNode;
    int i = 0;
    // while(current->element != theElement && i < listSize)
    while(current->element != theElement && current != NULL)
    {
        i++;
        current = current->next;
    }
    // if(i == listSize) return -1;
    if(current == NULL) return -1;
    return i;
}



// template<class T>
// void chain<T>::insert(int theIndex, const T& theElement)
// {// Insert theElement so that its index is theIndex.
//    if (theIndex < 0 || theIndex > listSize)
//    {// invalid index
//       ostringstream s;
//       s << "index = " << theIndex << " size = " << listSize;
//       throw IllegalParameter(s.str());
//    }

//    if (theIndex == 0)
//       // insert at front
//       firstNode = new chainNode<T>(theElement, firstNode);
//    else
//    {  // find predecessor of new element
//       chainNode<T>* p = firstNode;
//       for (int i = 0; i < theIndex - 1; i++)
//          p = p->next;
   
//       // insert after p
//       p->next = new chainNode<T>(theElement, p->next);
//    }
//    listSize++;
// }

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {       
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(theIndex == 0)
    {
        firstNode = new chainNode<T>(theElement, firstNode);
        ++listSize;
        return;
    }
    else
    {
        chainNode<T>* current = firstNode, *front = current->next;
        int i = 0;
        while(i != theIndex-1)
        {
            current = current->next;
            front = front->next;
            i++;
        }
        current->next = new chainNode<T>(theElement, front);
        listSize++;
    }
}


template<class T>
void chain<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    chainNode<T>* deleteNode;
    if(theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T>* current = firstNode;
        for(int i = 0; i < theIndex-1; i++)
            current = current->next;
        deleteNode = current->next;
        current->next = current->next->next;
    }
    delete deleteNode;
    listSize--;
}

// template<class T>
// void chain<T>::erase(int theIndex)
// {
//     checkIndex(theIndex);
//     chainNode<T>* current = firstNode, *front = current->next;
//     int i = 0;
//     if(theIndex == 0)
//     {
//         firstNode = current->next;
//         delete current;
//         listSize--;
//     }
//     else
//     {
//         while(i != theIndex-1)
//         {
//             current = current->next;
//             front = front->next;
//             i++;
//         }
//         delete current->next;
//         current->next = front;
//         listSize--;
//         return;
//     }
// }

template<class T>
void chain<T>::output(ostream& out)const
{
    chainNode<T>* current = firstNode;
    while(current)
    {
        out << current->element << " ";
        current = current->next;
    }
}

#endif //CH6_6_2_H