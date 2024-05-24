#include<iostream>
#include<sstream>
using namespace std;


class IllegalParameter
{
    public:
        IllegalParameter(string s = "IllegalParameter"){this->s = s;}
        void outputMessage(){cout << s;}
    private:
        string s;
};

template<class T>
class circularArrayList
{
    public:
        circularArrayList(int initialCapacity = 10);
        circularArrayList(const circularArrayList<T> &theList);
        ~circularArrayList(){delete[] element;}
        //ADT methods
        bool empty()const{return first == -1;}
        int size()const
        {
            if(first == -1) 
                return 0;
            else return (arrayLength+last-first)%arrayLength + 1; 
        }
        T& get(int theIndex)const;
        int indexOf(const T &theElement)const;
        void insert(int theIndex, const T& theElement);
        void erase(int theIndex);
        int capacity()const{return arrayLength;}
        void output(ostream& out)const;
    protected:
        void checkIndex(int theIndex)const;
        T* element;
        int first;
        int last;
        int arrayLength;
};

template<class T>
circularArrayList<T>::circularArrayList(int initialCapacity)
{
    if(initialCapacity <1)
    {
        ostringstream s;
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
    if(theList.size() == 0)
    {
        arrayLength = theList.arrayLength;
        element = new T[theList.arrayLength];
        first = theList.first;
        last = theList.last;
        return;
    }
    else
    {
        first = theList.first;
        last = theList.last;
        arrayLength = theList.arrayLength;
        if(element) delete []element;
        element = new T[arrayLength];
        int current = first;
        while (current != last)
        {
            element[current] = theList.element[current];
            current = (current+1)%arrayLength;
        }
        element[current] = theList.element[current];
    }
}


template<class T>
ostream& operator<<(ostream& out, const circularArrayList<T> &theList)
{
    theList.output(out);
    return out;
}

template<class T>
void circularArrayList<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= size())
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << size();
        throw IllegalParameter(s.str());
    }
}

template<class T>
void circularArrayList<T>::output(ostream& out)const
{
    int listSize = size();
    for(int i = 0; i < listSize; i++)
        out << element[(first+i)%arrayLength] << " ";
}

template<class T>
T& circularArrayList<T>::get(int theIndex)const
{
    checkIndex(theIndex);
    return element[(theIndex+first)%arrayLength];
}

template<class T>
int circularArrayList<T>::indexOf(const T &theElement)const
{
    if(size() == 0) return -1;
    int current = first, i = 0;
    for(; current != last && element[current] != theElement; current = (current + 1)%arrayLength, i++);
    if(current == last) return -1;
    return i;
}
template<class T>
void circularArrayList<T>::insert(int theIndex, const T &theElement)
{
    int listSize = size();
    if(theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "theIndex = " << theIndex << " size = " << size();
        throw IllegalParameter(s.str());
    }
    if(size() == arrayLength)
    {
        int current = first;
        T* newArray = new T[arrayLength*2];
        int i;
        for(; i < listSize; i++)
        {
            newArray[i] = element[current];
            current = (current+1)%arrayLength;
        }
        delete []element;
        element = newArray;
        arrayLength *= 2;
        first = 0;
        last = i; 
    }
    if(first == -1)
    {
        first = last = 0;
        element[first] = theElement;
        return;
    }
    if(theIndex < size()/2)
    {
        for(int i = 0; i < theIndex; i++)
            element[(arrayLength+i-1+first)%arrayLength] = element[(i+first)%arrayLength];
        first = (arrayLength+first-1)%arrayLength;
    }
    else
    {
        for(int i = size()-1; i >= theIndex; i--)
            element[(first+i+1)%arrayLength] = element[(first+i)%arrayLength];
        last = (last+1)%arrayLength;
    }
    element[(theIndex+first)%arrayLength] = theElement;
}

template<class T>
void circularArrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    if(theIndex < size()/2)
    {
        for(int i = theIndex-1; i >= 0; i--)
            element[(i+first+1)%arrayLength] = element[(first+i)%arrayLength];
        element[first].~T();
        first = (first+1)%arrayLength;
    }
    else
    {
        for(int i = theIndex+1; i < size(); i++)
            element[(arrayLength+first+i-1)%arrayLength] = element[(first+i)%arrayLength];
        element[last].~T();
        last = (arrayLength + last - 1)%arrayLength;
    }
}

int main()
{
    circularArrayList<int> x;
    for(int i = 0; i < 5; i++)
        x.insert(i, i+1);
    cout << x.get(0) << endl;
    x.insert(0, 26);
    cout << x;
}