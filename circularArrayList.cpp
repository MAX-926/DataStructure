#include"ch5/case/5-1.h"
#include<iterator>
#include<sstream>

template<class T>
class circularArrayList:public linearList<T>
{
    public:
        //constructor, copy-constructor and destructor
        circularArrayList(int initialCapacity = 10);//best:O(1)  worst:O(initialCapacity)
        circularArrayList(const circularArrayList<T> &theList);//O(theList.arrayLength)
        ~circularArrayList(){delete []element;}//O(1)
        bool empty()const{return first == -1;}//O(1)
        int size()const//O(1)
        {
            if(first == -1) return 0;
            else return (arrayLength + last - first)%arrayLength + 1;
        }
        int indexOf(const T& theElement)const;//best:O(1) worst:O(listSize)
        T& get(int theIndex)const;//O(1)
        void insert(int theIndex, const T &theElement);//best:O(1) worst:O(arrayLength)
        void erase(int theIndex);//best:O(1) worst:O(min{theIndex, listSize-theIndex-1})
        void output(std::ostream& out)const;//O(listSize)
        int capacity(){return arrayLength;}//O(1)
    protected:
        void checkIndex(int theIndex)const;//O(1)
        T* element;
        int first;
        int last;
        int arrayLength;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const circularArrayList<T> &theList)
{
    theList.output(out);
    return out;
}

template<class T>
void circularArrayList<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= size())
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " size = " << size();
        throw IllegalParameter(s.str());
    }
}

template<class T>
circularArrayList<T>::circularArrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "initialCapacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameter(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    first = -1;
}

template<class T>
circularArrayList<T>::circularArrayList(const circularArrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    first = theList.first;
    last = theList.last;
    element = new T[arrayLength];
    for(int i = first; i != last; i = (i+1)%arrayLength)
        element[i] = theList[i];
    element[last] = theList.element[last];
}

template<class T>
int circularArrayList<T>::indexOf(const T &theElement)const
{
    // checkIndex(theIndex);
    int i;
    for(i = 0; i < size() && element[(i+first)%arrayLength] != theElement; i++);
    if(i == size()) return -1;
    return i;
}

template<class T>
T& circularArrayList<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    return element[(theIndex+first)%arrayLength];
}

template<class T>
void circularArrayList<T>::insert(int theIndex, const T &theElement)
{
    int listSize = size();
    if(theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " size = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(first == -1)
    {
        element[0] = theElement;
        first = last = 0;
        return;
    }
    if(listSize == arrayLength)
    {
        T* newList = new T[2*arrayLength];//O(1) or O(arrayLength)
        int j = 0;
        for(int i = first; i != last; i = (i+1)%arrayLength)
            newList[j++] = element[i];
        newList[j] = element[last];//O(listSize)
        delete []element;
        element = newList;
        arrayLength*=2;
        first = 0;
        last = j;
    }
    if(theIndex <= listSize/2)//O(min{theIndex, listSize-theIndex})
    {
        //shift left side
        for(int i = 0; i < theIndex; i++)
            element[(arrayLength+first+i-1)%arrayLength] = element[(first+i)%arrayLength];
        first = (arrayLength+first-1)%arrayLength;
    }
    else
    {
        for(int i = listSize-1; i >= theIndex; i--)
            element[(first+i+1)%arrayLength] = element[(first+i)%arrayLength];
        last = (last+1)%arrayLength;
    }
    element[(theIndex + first)%arrayLength] = theElement;
}

template<class T>
void circularArrayList<T>::erase(int theIndex)
{
    int listSize = size();
    checkIndex(theIndex);
    if(first == -1)
    {
        element[0].~T();
        first = -1;
        return;
    }
    if(theIndex <= (listSize-1)/2)//O(min{theIndex, listSize-theIndex-1})
    {
        for(int i = theIndex-1; i >= 0; i--)
            element[(i+1+first)%arrayLength] = element[(i+first)%arrayLength];
        first = (first+1)%arrayLength;        
    }
    else
    {
        for(int i = theIndex+1; i < listSize; i++)
            element[(arrayLength+i-1+first)%arrayLength] = element[(i+first)%arrayLength];
        last = (arrayLength+last-1)%arrayLength;
    }
}

template<class T>
void circularArrayList<T>::output(std::ostream& out)const
{
    int current = first;
    for(; current != last; current = (current+1)%arrayLength)
        std::cout << element[current] << " ";
    std::cout << element[current] << " ";
}


int main()
{
    circularArrayList<int> x;
    for(int i = 0; i < 5; i++)
        x.insert(i, i+1);
    std::cout << x.get(5);
}

//從抽象層解決問題（索引元素）
//遇到減法加上arrayLength