//类arrayList的一个迭代器

#include"../../MyTool.h"
#include"5-1.h"
#include"5-2.cpp"
#include<sstream>
#include<algorithm>
#include<numeric>
#include<iterator>
// #include<iostream>
template<class T>
class arrayList:public linearList<T>
{
    public:
        arrayList(int initialCapacity = 10);
        arrayList(const arrayList<T> &b);
        ~arrayList(){delete []element;}
        //ADT方法:
        bool empty() const{return (listSize == 0);}
        int size() const{return listSize;}
        T& get(int theIndex) const;
        int indexOf(const T &theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T &theElement);
        void output(std::ostream &out) const;
        int capacity() const {return arrayLength;}
        class iterator;
        class iterator
        {
            public:
                typedef std::bidirectional_iterator_tag iterator_category;
                typedef T value_type;
                typedef ptrdiff_t difference_type;
                typedef T* pointer;
                typedef T& reference;

                //构造函数
                iterator(T* thePosition = 0){position = thePosition;}

                //解引用操作符
                T& operator*() const {return *position;}
                T* operator->() const {return &*position;}
                //迭代器的值增加
                iterator& operator++(){position++; return *this;}
                iterator operator++(int){iterator it(*this); position++; return it;}
                //迭代器的值减少
                //前减
                iterator& operator--()
                {
                    --position;
                    return *this;
                }
                //后减
                iterator operator--(int)
                {
                    iterator old = *this;
                     --position;
                     return old;
                }
                //测试是否相等
                bool operator!=(const iterator &it) const
                {
                    return it.position != position;
                }
                bool operator==(const iterator &it) const
                {
                    return it.position == position;
                }
            protected:
                T* position;//指向元素的指针

        };
        iterator begin()const{return iterator(element);}
        iterator end()const{return iterator(element+listSize);}

        //取出指针element
        T* getEle(){return element;}
    protected:
        void checkIndex(int theIndex) const;// 若索引theIndex无效，则抛出异常
        T* element;// 存储线性表元素的一维数组
        int arrayLength;// 线性表容量
        int listSize;// 线性表元素个数
};

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

template<class T>
std::ostream& operator<<(std::ostream &out, const arrayList<T> &x)
{
    x.output(out); return out;
}


int main()
{
    arrayList<int> x(5);
    x.insert(0, 1);
    x.insert(1, 2);
    x.insert(2, 3);
    x.insert(3, 4);
    x.insert(4, 5);
    arrayList<int>::iterator it;
    std::reverse(x.begin(), x.end());
    int sum = std::accumulate(x.begin(), x.end(), 0);
    std::cout << sum << std::endl;
    for(it = x.begin();it != x.end(); it++)
        std::cout << *it << " ";
}