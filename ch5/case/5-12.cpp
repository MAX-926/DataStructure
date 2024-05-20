#include"5-12.h"
#include<sstream>
#include<iterator>
using namespace std;

template<class T>
void vectorList<T>::checkIndex(int theIndex)const
{
    if(theIndex < 0 || theIndex >= element->size())
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " size = " << element->size();
        throw IllegalParameter(s.str());
    }
}

template<class T>
vectorList<T>::vectorList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s << "initialCapacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameter(s.str());
    }
    element = new vector<T>;
    element->reserve(initialCapacity);
}

template<class T>
vectorList<T>::vectorList(const vectorList<T> &theList)
{
    //調用vector的拷貝構造函數
    element = new vector<T>(*theList.element);
    // element->reserve(theList.element->size());
    // for(int i = 0;  i < element.size(); i++)
    //     element[i] = theList.element[i];
}

template<class T>
int vectorList<T>::indexOf(const T &theElement)const
{
    int i;
    for(i = 0; i < element->size() && (*element)[i] != theElement; i++);
    if(i == element->size()) return -1;
    return i;
}

template<class T>
void vectorList<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex < 0 || theIndex > element->size())
    {
        std::ostringstream s;
        s << "theIndex = " << theIndex << " size = " << element->size();
        throw IllegalParameter(s.str());
    }
    element->insert(element->begin()+theIndex, theElement);
}

template<class T>
void vectorList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    element->erase(element->begin()+theIndex);
}

template<class T>
void vectorList<T>::output(std::ostream& out)const
{
    //vector在插入數據后會在數組最後添一個元素，其值爲零
    //所以用end()函數獲取最後插入的數據需要將迭代器的值減一！！！
    std::copy(element->begin(), element->end(), std::ostream_iterator<T>(cout, " "));
}