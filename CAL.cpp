#include"ch5/case/5-1.h"
#include<iostream>
#include<sstream>

using namespace std;

template<class T>
class cir_arrayList:public linearList<T>
{
    public:
        // constructor & copy-constructor and destructor:
        cir_arrayList(int initialCapacity = 10);
        cir_arrayList(const cir_arrayList<T> &theCAL);
        ~cir_arrayList(){if(element) delete element;}
        //ADT methods:
        bool empty()const{return first == -1;}
        int size()const
        {
            if(first == -1) 
                return 0;
            else 
                return ((last - first + arrayLength) % arrayLength + 1);
        }
        T& get(int theIndex)const;
        int indexOf(const T &theElement)const;
        void insert(int theIndex, const T& theElement);
        void erase(int theIndex);
        void output(ostream& out)const;
    protected:
        void checkIndex(int theIndex)const;
        void inflate();
        T* element;
        int first;
        int last;
        int arrayLength;
};

template<class T>
void cir_arrayList<T>::inflate()
{
    int listSize = size();
    int exp = 2;
    T* newSpace = new T[2*arrayLength];
    int i;
    for(i = 0; i < listSize; i++)
        newSpace[i] = element[(i+first)%arrayLength];
    first = 0;
    last = i;
    arrayLength *= exp;
    delete []element;
    element = newSpace;
}

template<class T>
void cir_arrayList<T>::checkIndex(int theIndex)const
{
    int listSize = size();
    if(theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << size();
        throw IllegalParameter(s.str());
    }
}

template<class T>
cir_arrayList<T>::cir_arrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "initialCapacity = " << initialCapacity << " must be > 0";
        throw IllegalParameter(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[initialCapacity];
    first = -1;
    last = first;
}

template<class T>
cir_arrayList<T>::cir_arrayList(const cir_arrayList<T> &theCAL)
{
    first = theCAL.first;
    last = theCAL.last;
    arrayLength = theCAL.arrayLength;
    element = new T[arrayLength];
    for(int i = 0; i < arrayLength; i++)
        element[i] = theCAL.element[i];
    return;
}

template<class T>
T& cir_arrayList<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    return element[(theIndex+first)%arrayLength];
}

template<class T>
int cir_arrayList<T>::indexOf(const T& theElement)const
{
    int index = 0;
    int i;
    for(i = first; i != last && element[i] != theElement; (i = (i+1) % arrayLength), index++);
    if(i == last)
    {
        if(element[i] != theElement)
            return -1;
        else
            return index;
    }
    else return index;
}

template<class T>
void cir_arrayList<T>::insert(int theIndex, const T &theElement)
{
    int listSize = size();
    if(theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    if(listSize == arrayLength)
        inflate();//扩容，按照一个乘法因子增加数组的容量，对线性表实施一系列操作所需的时间与不改变数组长度相比，至多增加一个常数因子
    if(listSize == 0)
    {
        first = 0;
        last = first;
        element[first] = theElement;
        return;
    }
    //选择一个优的移动数据方案：
    if(theIndex < listSize / 2)
    {
        //移动左边的数据
        for(int i = 0; i < theIndex; i++)
            element[(i+first-1+arrayLength)%arrayLength] = element[(i+first)%arrayLength];
        first = (first-1+arrayLength) % arrayLength;
    }
    else
    {
        //移动右边的元素
        for(int i = listSize - 1; i >= theIndex; i--)
            element[(i+1+first)%arrayLength] = element[(i+first)%arrayLength];
        last = (last + 1) % arrayLength;
    }
    element[(theIndex + first) % arrayLength] = theElement;
}

template<class T>
void cir_arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    int listSize = size();
    if(listSize == 1)
    {
        element[first].~T();
        first = -1;
        last = first;
        return;
    }
    //确定优的数据移动方案:
    if(theIndex < listSize / 2)
    {
        //移动左边的数据：
        for(int i = theIndex; i > 0; i--)
            element[(i+first)%arrayLength] = element[(i-1+first+arrayLength)%arrayLength];
        element[first].~T();
        first = (first+1)%arrayLength;
    }
    else
    {
        for(int i = theIndex; i < listSize-1; i++)
            element[(i+first)%arrayLength] = element[(i+1+first)%arrayLength];
        element[last].~T();
        last = (last - 1 + arrayLength) % arrayLength; 
    }
}

template<class T>
void cir_arrayList<T>::output(ostream& out)const
{
    int listSize = size();
    for(int i = 0; i < listSize; i++)
        out << element[(i+first)%arrayLength] << " ";
}

template<class T>
ostream& operator<<(ostream& out, const cir_arrayList<T> &theCAL)
{
    theCAL.output(out);
    return out;
}

int main()
{
    cir_arrayList<int> a;
    for(int i = 0; i < 10; i++)
        a.insert(i, i);
    std::cout << a << std::endl;
    a.erase(0);
    a.erase(a.size()-1);
    std::cout << a << std::endl;
    std::cout << a.get(0) << std::endl;
}