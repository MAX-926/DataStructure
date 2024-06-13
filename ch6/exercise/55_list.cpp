#include<list>
#include<iostream>
#include<sstream>
#include"../../ch5/case/5-1.h"
#include"E:/DataStructure/Tool.h"

template<class T>
class STL_list:public linearList<T>
{
    public:
        STL_list();
        STL_list(const STL_list<T> & theList);
        ~STL_list();
        //ADT methods:
        bool empty()const{return list->empty();}
        int size()const{ return list->size();}
        T& get(int theIndex)const;
        int indexOf(const T& theElement)const;
        void insert(int theIndex, const T& theElement);
        void erase(int theIndex);
        void output(std::ostream& out)const;
    protected:
        void checkIndex(int theIndex)const;
        std::list<T>* list;
        int listSize;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const STL_list<T> theSTL_list)
{
    theSTL_list.output(out);
    return out;
}

template<class T>
void STL_list<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
}

template<class T>
STL_list<T>::STL_list()
{
    list = new std::list<T>;
    listSize = 0;
}

template<class T>
STL_list<T>::STL_list(const STL_list<T> &theList)
{
    list = new std::list<T>(*theList.list);
    listSize = theList.list->size();
}

template<class T>
STL_list<T>::~STL_list()
{
    if(list)
    {
        delete list;
    }
}

template<class T>
T& STL_list<T>::get(int theIndex)const
{
    auto iter = list->begin();
    for(int i = 0; i < theIndex; i++)
        iter++;
    return *iter;
}

template<class T>
int STL_list<T>::indexOf(const T& theElement)const
{
    int index = 0;
    auto iter = list->begin();
    for(; *(iter) != theElement && index < listSize; index++, iter++);
    if(index == listSize) return -1;
    else return index;
}

template<class T>
void STL_list<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw IllegalParameter(s.str());
    }
    auto iter = list->begin();
    for(int i = 0; i < theIndex; i++)
        iter++;
    list->insert(iter, theElement);
    listSize++;
    return;
}

template<class T>
void STL_list<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    auto iter = list->begin();
    for(int i = 0; i < theIndex; i++)
        iter++;
    list->erase(iter);
    --listSize;
}

template<class T>
void STL_list<T>::output(std::ostream& out)const
{
    auto iter = list->begin();
    for(int i = 0; i < listSize; i++)
    {
        out << *(iter++) << " ";
    }
}

int main()
{
    STL_list<int> x;
    for(int i = 0; i < 3; i++)
        x.insert(i, i);
    std::cout << x << std::endl;
    x.erase(0);
    std::cout << x << std::endl;
}

// int main()
// {
//     std::list<int> x;
//     x.size();
// }