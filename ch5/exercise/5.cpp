// //不需要拉取源码，使用继承进行增量开发！！！！！！！

// //类arrayList的定义
// #include"../../MyTool.h"
// #include"../case/5-1.h"
// #include"../case/5-2.cpp"
// #include<sstream>
// #include<algorithm>
// #include<iterator>
// // #include<iostream>
// template<class T>
// class arrayList:public linearList<T>
// {
//     public:
//         arrayList(int initCapacity = 10, double expanision = 2.0);
//         // arrayList(int initialCapacity = 10);
//         arrayList(const arrayList<T> &b);
//         ~arrayList(){delete []element;}
//         //ADT方法:
//         bool empty() const{return (listSize == 0);}
//         int size() const{return listSize;}
//         T& get(int theIndex) const;
//         int indexOf(const T &theElement) const;
//         void erase(int theIndex);
//         void insert(int theIndex, const T &theElement);
//         void output(std::ostream &out) const;
//         int capacity() const {return arrayLength;}
//         void trimToSize();
//     protected:
//         void checkIndex(int theIndex) const;// 若索引theIndex无效，则抛出异常
//         T* element;// 存储线性表元素的一维数组
//         int arrayLength;// 线性表容量
//         int listSize;// 线性表元素个数
//         double expanision;//element长度的膨胀因子
// };

// template<class T>
// arrayList<T>::arrayList(int initialCapacity, double theExpanision)
// {
//     if(initialCapacity < 1)
//     {
//         std::ostringstream s;
//         s << "initialCapacity = " << initialCapacity << " Must be > 0";
//         throw IllegalParameter(s.str());
//     }
//     else if(theExpanision <= 1)
//     {
//         std::ostringstream s;
//         s << "expanision = " << theExpanision << " Must be > 1";
//         throw IllegalParameter(s.str());
//     }
//     element = new T[initialCapacity];
//     expanision = theExpanision;
//     listSize = 0;
//     arrayLength = initialCapacity;
// }

// // template<class T>
// // arrayList<T>::arrayList(int initialCapacity)
// // {
// //     if(initialCapacity < 1)
// //     {
// //         std::ostringstream s;
// //         s << "initialCapacity = " << initialCapacity << " Must be > 0";
// //         throw IllegalParameter(s.str());
// //     }
// //     element = new T[initialCapacity];
// //     listSize = 0;
// //     arrayLength = initialCapacity;
// //     expanision = 2;
// // }

// template<class T>
// arrayList<T>::arrayList(const arrayList<T> &theList)
// {
//     expanision = theList.expanision;
//     listSize = theList.listSize;
//     arrayLength = theList.arrayLength;
//     element = new T[arrayLength];
//     std::copy(theList.element, theList.element + listSize, element);
// }

// template<class T>
// void arrayList<T>::checkIndex(int theIndex)const
// {
//     // if(theIndex < 0 || theIndex >= listSize) throw IllegalParameter("theIndex is invalid!");
//     if(theIndex < 0 || theIndex >= listSize)
//     {
//         std::ostringstream s;
//         s << "theIndex = " << theIndex << " size = " << listSize;
//         throw IllegalParameter(s.str());
//     }
// }

// template<class T>
// T& arrayList<T>::get(int theIndex) const
// {
//     //返回索引为theIndex的元素
//     //若此元素不存在则抛出异常
//     checkIndex(theIndex);
//     return element[theIndex];
// }

// //查找start-end范围内是否存在元素theElement
// //存在则返回theElement的索引
// template<class T>
// int find(T* start, T* end, const T &theElement)
// {
//     T* s;
//     for(s = start; s < end && *s != theElement; s++);
//     if(s == end) return -1;
//     else return s - start;
// }

// template<class T>
// int arrayList<T>::indexOf(const T &theElement) const
// {
//     //M1:
//     // for(int i = 0; i < listSize && element[i] != theElement; i++);
//     // if(i == listSize) return -1;
//     // else return i;

//     //M2：
//     int theIndex;
//     theIndex = (int)(find(element, element + listSize, theElement));
//     return theIndex;
// }

// template<class T>
// void arrayList<T>::erase(int theIndex)
// {
//     checkIndex(theIndex);
//     //M1:
//     // for(int i = theIndex; i < listSize-2; i++)
//     //     element[i] = element[i+1];
//     //M2:
//     std::copy(element+theIndex+1, element+listSize, element+theIndex);
//     element[--listSize].~T();//调用析构函数，防止内存泄漏 
// }

// template<class T>
// void arrayList<T>::insert(int theIndex, const T &theElement)
// {
//     // checkIndex(theIndex);
//     if(theIndex < 0 || theIndex >listSize)
//     {
//         std::ostringstream s;
//         s << "theIndex = " << theIndex << " size = " << listSize;
//         throw(IllegalParameter(s.str()));
//     }
//     if(listSize == arrayLength)
//     {
//         changeLength1D(element, arrayLength, expanision*arrayLength);
//         arrayLength *= expanision;
//     }
//     std::copy_backward(element+theIndex, element+listSize, element+listSize+1);
//     element[theIndex] = theElement;
//     listSize++;
// }

// template<class T>
// void arrayList<T>::output(std::ostream &out) const
// {
//     // for(int i = 0; i < listSize; i++)
//     //     std::cout << element[i] << " ";
//     // std::cout << endl;
//     std::copy(element, element+listSize, std::ostream_iterator<T>(std::cout, " "));
// }

// template<class T>
// std::ostream& operator<<(std::ostream &out, const arrayList<T> &x)
// {
//     x.output(out); return out;
// }

// template<class T>
// void arrayList<T>::trimToSize()
// {
//     int theSize = std::max(listSize, 1);//O(1)
//     T* tmp  = new T[theSize];//O(theSize),不是O(1)是因为如果类型T是用户自定义类型，则需要为每一个T类型的对象调用构造函数
//     std::copy(element, element+theSize, tmp);//O(theSize)
//     arrayLength = theSize;//O(1)
//     delete []element;//O(1)
//     element = tmp;//O(1)
// }//total O(theSize)

// int main()
// {
//     arrayList<int> x(1);
//     x.insert(0, 26);
//     x.insert(1, 2);
//     x.insert(2, 3);
//     // std::cout << x.capacity();
//     x.trimToSize();
//     std::cout << x.capacity();
// }

#include"../case/5-3.h"

template<class T>
class arrayListWithTrimToSize: public arrayList<T>
{
    public:
    //constructor and destructor
        arrayListWithTrimToSize(int initialCapacity = 10):arrayList<T>(initialCapacity){}
        void trimToSize();
};

template<class T>
void arrayListWithTrimToSize<T>::trimToSize()
{
    if(this->arrayLength == this->listSize) return;

    if(this->listSize == 0)
    {
        delete [](this->element);
        this->element = new T[1];
        this->arrayLength = 1;
        return;
    }

    changeLength1D(this->element, this->arrayLength, this->listSize);
    this->arrayLength = this->listSize;
    // int theSize = std::max(listSize, 1);
    // T* tmp = new T[theSize];
    // std::copy(element, element+listSize, tmp);
    // delete []element;
    // element = tmp;
    // arrayLength = theSize;
}

// int main()
// {
//     arrayListWithTrimToSize<int> x(5);
//     x.insert(0, 1);
//     x.insert(1, 2);
//     x.insert(2, 3);
//     std::cout << x.capacity();
//     x.trimToSize();
//     std::cout << x.capacity();
// }