#include"../case/5-3.h"
#include<iterator>
using namespace std;

template<class T>
class circularArrayList: public linearList<T>
{
    public:
    // constructor, copy-constructor and destructor
        circularArrayList(int initialCapacity = 10);
        circularArrayList(const circularArrayList<T> &theList);
        ~circularArrayList(){delete []element;}
        bool empty()const{return first == -1;}
        int size()const
        {
            if(first == -1) return 0;
            else return (arrayLength + last - first)%arrayLength + 1;// 为什么last-first+1不行？因为last可能小于first
        }
        T& get(int theIndex)const;
        int indexOf(const T &theElement)const;
        void erase(int theIndex);
        void insert(int theIndex, const T &theElement);
        void output(std::ostream &out)const;
        // additional method
        int capacity()const{return arrayLength;}
    protected:
        void checkIndex(int theIndex)const;
        // throw illegalIndex if theIndex invalid
        T* element;
        int arrayLength;
        int first;//是经过映射后的索引
        int last;//是经过映射后的索引
};

template<class T>
circularArrayList<T>::circularArrayList(int initialCapacity)
{//constructor
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "InitialCapacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameter(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    first = -1; //list is enpty
}

template<class T>
circularArrayList<T>::circularArrayList(const circularArrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    element = new T[arrayLength];
    first = theList.first;
    // theList is empty
    if(first == -1) return;
    // theList is non-empty
    last = theList.last;
    int current = first;
    while(current != last)
    {
        element[current] = theList.element[current];
        current = (current + 1)%arrayLength;
    }
    element[current] = theList.element[current];
    // std::copy(theList.element, theList.element+arrayLength, element);
}

template<class T>
void circularArrayList<T>::checkIndex(int theIndex)const
{
    int listSize = size();
    //Verify whether theIndex is between 0 and size()-1
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " size = " << listSize;
        throw IllegalParameter(s.str());
    }
}


template<class T>
T& circularArrayList<T>::get(int theIndex)const
{   //return element whose index is theIndex.
    //throw illegalIndex exception if no such element.
    checkIndex(theIndex);
    return element[(theIndex + first)%arrayLength];
}

template<class T>
 int circularArrayList<T>::indexOf(const T &theElement)const
 {//Return index of first occurrence of theElement
  // return -1 if theElement not in list

    // int current = first;
    // while(current <= last)
    //     if(element[(current+first)%arrayLength] == theElement) break;
    // if(current > last) return -1;
    // else return current;
    int listSize = size();
    for(int i = 0; i < listSize; i++)
        if(element[(i+first)%arrayLength] == theElement)
            return i;
    return -1;
 }

template<class T>
void circularArrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    if(size() == 1)
    {
        element[first].~T();
        first = -1;
        return;
    }
    //determine which side has fewer elements
    //and shift the smaller number of elements
    int listSize = size();
    if(theIndex <= (listSize - 1)/2)
    {//shift left side (theIndex-1 ... 0)
        for(int i = theIndex - 1; i>=0; i--)
            element[(i + first + 1)%arrayLength] = element[(i + first)%arrayLength];
        element[first].~T();
        first = (first+1)%arrayLength;
    }
    else
    {
        for(int i = theIndex + 1; i < listSize; i++)
            element[(i+first-1)%arrayLength] = element[(i+first)%arrayLength];
        element[last].~T();
        last = (last-1+arrayLength)%arrayLength;
    }
}

template<class T>
void circularArrayList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   int listSize = size();
   if (theIndex < 0 || theIndex > listSize)
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw IllegalParameter(s.str());
   }

   // valid index, handle empty list as special case
   if (first == -1)
   {// insert into empty list
      first = last = 0;
      element[0] = theElement;
      return;
   }

   // insert into a nonempty list, make sure we have space
   if (listSize == arrayLength)
   {// no space, double capacity
      T* newArray = new T [2 * arrayLength];

      // copy elements into new array beginning at position  0
      int j = 0;   // position in newArray to copy to
      for (int i = first;
               i != last; i = (i + 1) % arrayLength)//(i+1)%arrayLength表述i++
         newArray[j++] = element[i];
      newArray[j] = element[last];  // copy last element

      // switch to newArray and set first and last
      delete [] element;
      element = newArray;
      arrayLength *= 2;
      first = 0;
      last = j;
   }

   // create space for new element
   if (theIndex <= listSize / 2)
   {// shift elements 0 through theIndex - 1
      for (int i = 0; i < theIndex; i++)
         element[(arrayLength + first + i - 1) % arrayLength]
             = element[(first + i) % arrayLength];
      first = (arrayLength + first - 1) % arrayLength;
   }

   else
   {// shift elements listSize - 1  ... theIndex
      for (int i = listSize - 1; i >= theIndex; i--)
         element[(first + i + 1) % arrayLength]
              = element[(first + i) % arrayLength];
      last = (last + 1) % arrayLength;
   }
       
   // insert new element
   element[(first + theIndex) % arrayLength] = theElement;
}

template<class T>
void circularArrayList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
   if (first == -1)
      return;   // list is empty
   
   // non-empty list
   int current = first;
   while (current != last)
   {
      std::cout << element[current]  << "  ";
      current = (current + 1) % arrayLength;
   }
   std::cout << element[current]  << "  ";
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const circularArrayList<T>& x)
   {x.output(out); return out;}


int main()
{
    circularArrayList<int> x(10);
    for(int i = 0; i < 5; i++)
        x.insert(i, i+1);
    std::cout << x.size();
}

// template<class T>
// circularArrayList<T>::circularArrayList(int initialCapacity):arrayLength(initialCapacity), listSize(0), first(initialCapacity/2), last(first)
// {
//     if(initialCapacity < 0)
//     {
//         std::ostringstream s;
//         s << "initialCapacity = " << initialCapacity << " initialCapacity must be >= 0";
//         throw IllegalParameter(s.str());
//     }
//     // if(theFirst < 0 || theFirst >= arrayLength)
//     // {
//     //     std::ostringstream s;
//     //     s << "first = " << theFirst << " arrayLength = " << arrayLength;
//     //     throw IllegalParameter(s.str());
//     // }
//     // last = (first + 1)%arrayLength;
//     element = new T[initialCapacity];
// }

// template<class T>
// std::ostream& operator<<(std::ostream& out, const circularArrayList<T> &x)
// {
//     x.output(out);
//     return out;
// }

// template<class T>
// void circularArrayList<T>::checkIndex(int theIndex)const
// {
//     if(theIndex < 0 || (first > last ? (theIndex > last && theIndex < first) : (theIndex < first || theIndex > last)))
//     {
//         std::ostringstream s;
//         s << "theIndex  = " << theIndex << " listSize = " << listSize;
//         throw IllegalParameter(s.str());
//     }
//     return;
// }

// template<class T>
// T& circularArrayList<T>::get(int theIndex)const
// {
//     checkIndex(theIndex);
//     return element[(first + theIndex)%arrayLength];
// }

// template<class T>
// int circularArrayList<T>::indexOf(const T &theElement)const
// {
//     int i;
//     for(i = 0; i < listSize && element[(first + i)%listSize)] != theElement; i++);
//     if(i == listSize) return -1;
//     else return i;
// }

// template<class T>
// void circularArrayList<T>::erase(int theIndex)
// {

// }

// template<class T>
// void circularArrayList<T>::insert(int theIndex, const T &theElement)
// {
//     checkIndex(theIndex);
//     if(listSize == arrayLength)
//     {
//         /*inflate*/

//     }
// }

// template<class T>
// void circularArrayList<T>::output(std::ostream &out)const
// {
//     if(first > last)
//     {
//         std::copy(element + first, element + arrayLength, std::ostream_iterator<T>(cout, " "));
//         std::copy(element, element + last + 1, std::ostream_iterator<T>(cout, " "));
//     }
//     else
//     {
//         std::copy(element + first, element + last + 1, std::ostream_iterator<T>(cout, " "));
//     }
// }