//circularListArray
//state:
//1.T* element
//2.chainNode<T>* first
//3/chainNode<T>* last
//4.arrayLength (capacity)
// formula: index = (first + theIndex) % arrayLength
#include<sstream>
#include"ch5/case/5-1.h"
#include<iostream>
#include<iterator>
using namespace std;

//index = (index0 + theIndex)%arrayLength
template<class T>
class arrayCircularList:public linearList<T>
{
    public:
        arrayCircularList(int initialCapacity = 10);
        arrayCircularList(const arrayCircularList<T> &theACL);
        ~arrayCircularList();
        bool empty()const{return first == -1;}
        int size()const{ return (arrayLength + last - first) % arrayLength + 1;}
        T& get(int theIndex)const;
        int indexOf(const T &theElement)const;
        void insert(int theIndex, const T &theElement);
        void erase(int theIndex);
        void output(ostream& out)const;
        int capacity()const{return arrayLength;}
    protected:
        void checkIndex(int theIndex)const;
        void inflate();
        T* element;
        int first;
        int last;
        int arrayLength;
        // int capacity;
};

template<class T>
void arrayCircularList<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= arrayLength)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << arrayLength;
        throw IllegalParameter(s.str());
    }
}

template<class T>
void arrayCircularList<T>::inflate()
{
    int exp = 2;
    int listSize = size();
    T* newSpace = new T[arrayLength*exp];
    for(int i = 0; i < listSize; i++)
    {
        newSpace[i] = element[(first + i) % arrayLength];
    }
    delete []element;
    element = newSpace;
    first = 0;
    last = listSize-1;
    arrayLength *= exp;
}

template<class T>
arrayCircularList<T>::arrayCircularList(int initialCapacity)
{
    element = new T[initialCapacity];
    first = -1;
    arrayLength = initialCapacity;
}

template<class T>
arrayCircularList<T>::arrayCircularList(const arrayCircularList<T> &theACL)
{
    int listSize = size();
    element = new T[theACL.arrayLength];
    copy(theACL.element, theACL.element + arrayLength, element);
    first = theACL.first;
    last = theACL.last;
    arrayLength = theACL.arrayLength;
}

template<class T>
arrayCircularList<T>::~arrayCircularList()
{
    if(element)
        delete []element;
}

template<class T>
T& arrayCircularList<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    return element[(first + theIndex)%arrayLength];
}

template<class T>
int arrayCircularList<T>::indexOf(const T &theElement)const
{
    int ls = size();
    int i;
    for(i = 0; i < ls && element[(first + i)%arrayLength] != theElement; i++);
    if(i == ls) return -1;
    else return i;
}

template<class T>
void arrayCircularList<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex < 0 || theIndex > arrayLength)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << arrayLength;
        throw IllegalParameter(s.str());
    }
    int listSize = size();
    if(arrayLength == listSize)
        inflate();
    if(empty())
    {
        first = 0;
        last = 0;
        element[first] = theElement;
        return;
    }

    //左移
    if(theIndex < listSize/2)
    {
        for(int i = 0; i <= theIndex-1; i++)
        {
            element[(arrayLength + i - 1 + first) % arrayLength] = element[(first + i) % arrayLength];
        }
        first = (arrayLength + first - 1) % arrayLength;
    }
    else
    {
        for(int i = listSize-1; i >= theIndex; i--)
        {
            element[(i+first+1)%arrayLength] = element[(i+first)%arrayLength];
        }
        last = (last+1) % arrayLength;
    }
    element[(first + theIndex) % arrayLength] = theElement;
}

template<class T>
void arrayCircularList<T>::erase(int theIndex)
{
    int listSize = size();
    if(theIndex < listSize / 2)
    {
        for(int i = theIndex; i >= 0; i--)
            element[(first+i)%arrayLength] = element[(arrayLength+i-1+first)%arrayLength];
        element[first].~T();
        first = (first + 1)%arrayLength;
    }
    else
    {
        for(int i = theIndex; i < listSize-1; i++)
            element[(i+first)%arrayLength] = element[(i+1+first)%arrayLength];
        element[last].~T();
        last = (arrayLength + last - 1)%arrayLength;
    }
    if(listSize == 1)
    {
        first = -1;
    }
}

template<class T>
void arrayCircularList<T>::output(ostream& out)const
{
    int ls = size();
    for(int i = 0; i < ls; i++)
        out << element[(i+first)%arrayLength] << " ";
}

template<class T>
ostream& operator<<(ostream& out, const arrayCircularList<T> &theACL)
{
    theACL.output(out);
    return out;
}

int main()
{
    arrayCircularList<int> x;
    for(int i = 0; i < 10; i++)
        x.insert(i, i+1);
    x.insert(10, 26);
    std::cout << "x:" << x.indexOf(0) << std::endl;
}