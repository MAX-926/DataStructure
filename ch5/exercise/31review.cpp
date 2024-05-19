// #include"../case/5-1.h"
// #include<iterator>
// using namespace std;

// template<class T>
// class circularArrayList:public linearList<T>
// {
//     public:
//         //constructor, copy-constructor and destructor
//         circularArrayList(int initialCapacity = 10);
//         circularArrayList(const circularArrayList<T> &theList);
//         ~circularArrayList(){delete []element;}
//         bool empty()const{return first == -1;}
//         int size()const
//         {
//             if(first == -1) return 0;
//             else
//             return (arrayLength + last - first)%arrayLength + 1;
//         }
//         int indexOf(const T &theElement)const;
//         T& get(int theIndex)const;
//         void insert(int theIndex, const T &theElement);
//         void erase(int theIndex);
//         int capacity()const{return arrayLength;}
//         void output(std::ostream& out)const;
//         T* getEle(){return element;}
//     protected:
//         void checkIndex(int theIndex)const;
//         T* element;
//         int first;
//         int last;
//         int arrayLength;
// };

// template<class T>
// void circularArrayList<T>::checkIndex(int theIndex)const
// {
//     int listSize = size();
//     if(theIndex < 0 || theIndex >= listSize)
//     {
//         std::ostringstream s;
//         s << "theIndex = " << theIndex << " listSize = " << listSize;
//         throw IllegalParameter(s.str());
//     }
// }

// template<class T>
// circularArrayList<T>::circularArrayList(int initialCapacity)
// {
//     if(initialCapacity < 1)
//     {
//         std::ostringstream s;
//         s << "initialCapacity = " << initialCapacity << " Must be > 0";
//         throw IllegalParameter(s.str());
//     }
//     arrayLength = initialCapacity;
//     element = new T[arrayLength];
//     first = -1;
// }

// template<class T>
// circularArrayList<T>::circularArrayList(const circularArrayList<T> &theList)
// {
//     arrayLength = theList.arrayLength;
//     first = theList.first;
//     last = theList.last;
//     element = new T[arrayLength];
// }

// template<class T>
// int circularArrayList<T>::indexOf(const T &theElement)const
// {
//     if(first == -1) return -1;
//     int i;
//     for(i = 0; i < size() && element[(i+first)%arrayLength] != theElement; i++);
//     if(i == size()) return -1;
//     return i;
// }

// template<class T>
// T& circularArrayList<T>::get(int theIndex)const
// {
//     checkIndex(theIndex);
//     return element[(theIndex + first)%arrayLength];
// }

// template<class T>
// void circularArrayList<T>::erase(int theIndex)
// {
//     checkIndex(theIndex);
//     if(size() == 1)
//     {
//         element[first].~T();
//         first = -1;
//     }
//     int listSize = size();
//     if(theIndex <= (listSize-1)/2)
//     {//shift left side elements: 0...theindex-1
//         for(int i = theIndex-1; i>= 0; i--)
//             element[(i+1+first)%arrayLength] = element[(i+first)%arrayLength];
//         element[first].~T();
//         first = (first+1)%arrayLength;
//     }
//     else
//     {
//         for(int i = theIndex+1; i < listSize; i++)
//             element[(i-1+first)%arrayLength] = element[(i+first)%arrayLength];
//         element[last].~T();
//         last = (arrayLength+last-1)%arrayLength;
//     }
// }

// template<class T>
// void circularArrayList<T>::insert(int theIndex, const T &theElement)
// {
//     int listSize = size();
//     if(theIndex < 0 || theIndex > listSize)
//     {
//         std::ostringstream s;
//         s << "theIndex = " << theIndex << " listSize = " << listSize;
//         throw IllegalParameter(s.str());
//     }
//     if(first == -1)//keypoint!!!!!
//     {
//         element[0] = theElement;
//         first = last = 0;
//         return;
//     }
//     // check whether there is enough space for a newly insert element
//     if(listSize == arrayLength)
//     {
//         T* tmp = new T[arrayLength*2];
//         int j = 0;
//         // int current = first;
//         for(int current = first; current != last; current = (current+1)%arrayLength)
//             tmp[j++] = element[current];
//         tmp[j] = element[last];
//         delete []element;
//         element = tmp;
//         arrayLength*=2;
//         first = 0;
//         last = j;
//     }
//     //choose a better way to move less elements
//     if(theIndex <= (listSize)/2)
//     {
//         for(int i = 0; i < theIndex; i++)
//             element[(arrayLength+i-1+first)%arrayLength] = element[(i+first)%arrayLength];
//         first = (first-1+arrayLength)%arrayLength;
//     }
//     else
//     {
//         for(int i = listSize-1; i >= theIndex; i--)
//             element[(first+i+1)%arrayLength] = element[(first+i)%arrayLength];
//         last = (last+1)%arrayLength;
//     }
//     element[(theIndex+first)%arrayLength] = theElement;
// }

// // template<class T>
// // void circularArrayList<T>::insert(int theIndex, const T& theElement)
// // {// Insert theElement so that its index is theIndex.
// //    int listSize = size();
// //    if (theIndex < 0 || theIndex > listSize)
// //    {// invalid index
// //       ostringstream s;
// //       s << "index = " << theIndex << " size = " << listSize;
// //       throw IllegalParameter(s.str());
// //    }

// //    // valid index, handle empty list as special case
// //    if (first == -1)
// //    {// insert into empty list
// //       first = last = 0;
// //       element[0] = theElement;
// //       return;
// //    }

// //    // insert into a nonempty list, make sure we have space
// //    if (listSize == arrayLength)
// //    {// no space, double capacity
// //       T* newArray = new T [2 * arrayLength];

// //       // copy elements into new array beginning at position  0
// //       int j = 0;   // position in newArray to copy to
// //       for (int i = first;
// //                i != last; i = (i + 1) % arrayLength)//(i+1)%arrayLength表述i++
// //          newArray[j++] = element[i];
// //       newArray[j] = element[last];  // copy last element

// //       // switch to newArray and set first and last
// //       delete [] element;
// //       element = newArray;
// //       arrayLength *= 2;
// //       first = 0;
// //       last = j;
// //    }

// //    // create space for new element
// //    if (theIndex <= listSize / 2)
// //    {// shift elements 0 through theIndex - 1
// //       for (int i = 0; i < theIndex; i++)
// //          element[(arrayLength + first + i - 1) % arrayLength]
// //              = element[(first + i) % arrayLength];
// //       first = (arrayLength + first - 1) % arrayLength;
// //    }

// //    else
// //    {// shift elements listSize - 1  ... theIndex
// //       for (int i = listSize - 1; i >= theIndex; i--)
// //          element[(first + i + 1) % arrayLength]
// //               = element[(first + i) % arrayLength];
// //       last = (last + 1) % arrayLength;
// //    }
       
// //    // insert new element
// //    element[(first + theIndex) % arrayLength] = theElement;
// // }

// template<class T>
// void circularArrayList<T>::output(std::ostream& out)const
// {
//     if(first == -1) return;
//     int listSize = size();
//     int current = first;
//         // std::copy(element+(first+i)%arrayLength, element+(first+i)%arrayLength, std::ostream_iterator<T>(std::cout, " "));
//     while(current != last)
//     {
//         std::cout << element[current] <<  " ";
//         current = (current+1)%arrayLength;
//     }
//     std::cout << element[current] << " ";
// }

// template<class T>
// std::ostream& operator<<(std::ostream& out, const circularArrayList<T> & theList)
// {
//     theList.output(out);
//     return out;
// }

// int main()
// {
//     circularArrayList<int> x(10);
//     for(int i = 0; i < 5; i++)
//         x.insert(i, i+1);
//     std::cout << x.size() << " ";
// }