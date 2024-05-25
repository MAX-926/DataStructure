#include"./6-11.h"
#include"6-1.h"
#include<sstream>
using namespace std;

template<class T>
class extendedChain:public extendedLinearList<T>
{
    public:
        extendedChain(int initialCapacity = 10);
        extendedChain(const extendedChain<T> &c);
        ~extendedChain();
        //ADT methods:
        bool empty()const{return listSize == 0;}
        int size()const{return listSize;}
        T& get(int theIndex)const;
        int indexOf(const T& element)const;
        void insert(int theIndex, const T& element);
        void erase(int theIndex);
        void push_back(const T &element);
        void clear();
        void output(std::ostream& out)const;
        //iterator:
        class iterator//使用iterator做extenedChain的get操作，如果逐个元素考察，可以将复杂度从O(listSize^2)降到O(listSize)
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
        struct chainNode<T>* lastNode;
        int listSize;
};

template<class T>
std::ostream& operator<<(std::ostream &out, const extendedChain<T> &theExtendedChain)
{
    theExtendedChain.output(out);
    return out;
}

template<class T>
void extendedChain<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
extendedChain<T>::extendedChain(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "initialCapacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameter(s.str());
    }
    firstNode = 0;
    lastNode = 0;
    listSize = 0;
}

template<class T>
extendedChain<T>::extendedChain(const extendedChain<T> &theExtendedChain)
{
    if(theExtendedChain.listSize == 0)
    {
        firstNode = lastNode = 0;
        listSize = 0;
        return;
    }
    listSize = theExtendedChain.listSize;
    chainNode<T>* sourchNode = theExtendedChain.firstNode;
    firstNode = new chainNode<T>(sourchNode->element);
    chainNode<T>* targetNode = firstNode;
    sourchNode = sourchNode->next;
    while(sourchNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourchNode->element);
        sourchNode = sourchNode->next;
        targetNode = targetNode->next;
    }
    lastNode = targetNode;
    targetNode->next = NULL;
}

template<class T>
extendedChain<T>::~extendedChain()
{
    while(firstNode)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
T& extendedChain<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    chainNode<T>* current = firstNode;
    for(int i = 0; i < theIndex; i++)
        current = current->next;
    return current->element;
}

template<class T>
int extendedChain<T>::indexOf(const T &element)const
{
    if(listSize == 0) return -1;
    chainNode<T>* current = firstNode;
    int index = 0;
    while(current && current->element != element)
    {
        current = current->next;
        ++index;
    }
    if(!current) return -1;
    return index;
}

template<class T>
void extendedChain<T>::insert(int theIndex, const T &element)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(theIndex == 0)
    {
        firstNode = new chainNode<T>(element, firstNode);
        ++listSize;
        if(listSize == 1) lastNode = firstNode;
        return;
    }
    chainNode<T>* current = firstNode;
    for(int i = 0; i < theIndex-1; i++)
        current = current->next;
    current->next = new chainNode<T>(element, current->next);
    if(theIndex == listSize) lastNode = current->next;
    ++listSize;
}

template<class T>
void extendedChain<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    if(theIndex == 0)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
        if(!firstNode) lastNode = NULL;
        --listSize;
        return;
    }
    chainNode<T>* current = firstNode;
    for(int i = 0; i < theIndex-1; i++)
        current = current->next;
    chainNode<T>* nextNode = current->next->next;
    if(!nextNode) lastNode = current;
    delete current->next;
    current->next = nextNode;
    --listSize;
}

template<class T>
void extendedChain<T>::push_back(const T &element)
{
    chainNode<T>* newNode = new chainNode<T>(element, NULL);
    if(firstNode == NULL)
    {
        // firstNode = new chainNode<T>(element, NULL);
        firstNode = newNode;
        ++listSize;
        lastNode = firstNode;
        return;
    }
    // lastNode->next = new chainNode<T>(element, NULL);
    lastNode->next = newNode;
    ++listSize;
    lastNode = lastNode->next;
}

template<class T>
void extendedChain<T>::output(ostream& out)const
{
    chainNode<T>* current = firstNode;
    while(current)
    {
        out << current->element << " ";
        current = current->next;
    }
    out << "";
}

template<class T>
void extendedChain<T>::clear()
{
    while(firstNode)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    listSize = 0;
    lastNode = firstNode;
}

int main()
{
    extendedChain<int> xc;
    for(int i = 0; i < 5; i++)
        xc.insert(i, i+1);
    cout << xc << endl;
    xc.push_back(26);
    xc.erase(5);
    xc.push_back(28);
    cout << xc;
}