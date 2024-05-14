#include"5-3.h"

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "initialCapacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameter(s.str());
    }
    element = new T[initialCapacity];
    listSize = 0;
    arrayLength = initialCapacity;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    listSize = theList.listSize;
    arrayLength = theList.arrayLength;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex)const
{
    // if(theIndex < 0 || theIndex >= listSize) throw IllegalParameter("theIndex is invalid!");
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " size = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{
    //返回索引为theIndex的元素
    //若此元素不存在则抛出异常
    checkIndex(theIndex);
    return element[theIndex];
}

//查找start-end范围内是否存在元素theElement
//存在则返回theElement的索引
template<class T>
int find(T* start, T* end, const T &theElement)
{
    T* s;
    for(s = start; s < end && *s != theElement; s++);
    if(s == end) return -1;
    else return s - start;
}

template<class T>
int arrayList<T>::indexOf(const T &theElement) const
{
    //M1:
    // for(int i = 0; i < listSize && element[i] != theElement; i++);
    // if(i == listSize) return -1;
    // else return i;

    //M2：
    int theIndex;
    theIndex = (int)(find(element, element + listSize, theElement));
    return theIndex;
}

template<class T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    //M1:
    // for(int i = theIndex; i < listSize-2; i++)
    //     element[i] = element[i+1];
    //M2:
    std::copy(element+theIndex+1, element+listSize, element+theIndex);
    element[--listSize].~T();//调用析构函数，防止内存泄漏 
}

template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement)
{
    // checkIndex(theIndex);
    if(theIndex < 0 || theIndex >listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " size = " << listSize;
        throw(IllegalParameter(s.str()));
    }
    if(listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, 2*arrayLength);
        arrayLength *= 2;
    }
    std::copy_backward(element+theIndex, element+listSize, element+listSize+1);
    element[theIndex] = theElement;
    listSize++;
}

template<class T>
void arrayList<T>::output(std::ostream &out) const
{
    // for(int i = 0; i < listSize; i++)
    //     std::cout << element[i] << " ";
    // std::cout << endl;
    std::copy(element, element+listSize, std::ostream_iterator<T>(std::cout, " "));
}

// template<class T>
// std::ostream& operator<<(std::ostream &out, const arrayList<T> &x)
// {
//     x.output(out); return out;
// }
