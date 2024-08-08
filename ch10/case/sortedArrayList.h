#ifndef SORTEDARRAYLIST_H
#define SORTEDARRAYLIST_H

//有序数组
#include"dictionary.h"
#include<sstream>
#include"../../Tool.h"
#include<iostream>

using namespace std;

template<class K, class E>
class sortedArrayList:public dictionary<K, E>
{
    public:
        //constructor, destructor
        sortedArrayList(int initialCapacity = 10);
        ~sortedArrayList(){delete[] sortedList;}
        //ADT Methods:
        bool empty()const { return dSize == 0;}
        int size()const {return dSize;}

        // pair<const K, E>* find(const K&)const;
        pair<const K, E>* find(const K&)const;
        // void insert(const pair<const K, E>&);
        void insert(const pair<const K, E>&);

        void erase(const K&);
        void output(ostream&)const;
    protected:
        // 二分查找辅助函数
        int binarySearch(const K&, int, int)const;
        pair<const K, E>** sortedList;//字典
        int dSize;//字典数对的个数
        int arrayLength; 
};

template<class K, class E>
void sortedArrayList<K, E>::output(ostream& out)const
{
    for(int i = 0; i < dSize; i++)
    {
        out << endl;
        out << sortedList[i]->first << " : " << sortedList[i]->second << endl;
    }
}

template<class K, class E>
ostream& operator<<(ostream& out, const sortedArrayList<K, E>& sal)
{
    sal.output(out);
    return out;
}

template<class K, class E>
sortedArrayList<K, E>::sortedArrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream os;
        os << "initialCapacity = " << initialCapacity << " must be > 0\n";
        throw illegalParameter(os.str());
    }
    arrayLength = initialCapacity;
    sortedList = new pair<const K, E>*[initialCapacity];
    dSize = 0;
}

template<class K, class E>
pair<const K, E>* sortedArrayList<K, E>::find(const K& theKey)const
{//使用二分查找策略
    int index = binarySearch(theKey, 0, dSize - 1);
    if(index == -1)
        return nullptr;
    else return sortedList[index];
}

template<class K, class E>
int sortedArrayList<K, E>::binarySearch(const K& theKey, int left, int right)const
{//未找到返回-1，否则返回数对索引
    int middle = (right + left) / 2;
    if(left >= right && sortedList[right]->first != theKey)
        return -1;
    if(sortedList[middle]->first == theKey)
        return middle;
    else if(sortedList[middle]->first < theKey)
        binarySearch(theKey, middle + 1, right);
    else
        binarySearch(theKey, left, middle - 1);
}

template<class K, class E>
void sortedArrayList<K, E>::insert(const pair<const K, E>& thePair)
{//将数对插入有序数组中
    if(dSize == arrayLength)
    {//扩容
        pair<const K, E>** newSortedList = new pair<const K, E>*[arrayLength*2];
        for(int i = 0; i < dSize; i++)
            newSortedList[i] = sortedList[i];
        delete[] sortedList;
        sortedList = newSortedList;
        arrayLength *= 2;
    }
    if(dSize == 0)
    {
        sortedList[dSize++] = new pair<const K, E>(thePair);
        return;
    }
    //数组中有数对，寻找数对
    int index = binarySearch(thePair.first, 0, dSize - 1);
    if(index != -1)
    {//有序数组中存在关键字为theKey的数对
        sortedList[index]->second = thePair.second;
        return;
    }
    //需要插入新数对
    for(index = 0; index < dSize && sortedList[index]->first < thePair.first; index++);
    for(int iter = dSize - 1; iter >= index; iter--)
        sortedList[iter+1] = sortedList[iter];
    sortedList[index] = new pair<const K, E>(thePair);    
    dSize++;
    return;
}

template<class K, class E>
void sortedArrayList<K, E>::erase(const K& theKey)
{//删除有序数组中关键字为theKey的数对
    int iter = 0;
    int index = binarySearch(theKey, 0, dSize - 1);
    if(index == -1) return;//有序数组中没有关键字为theKey的数对
    else
    {//找到数对
        delete sortedList[index];//删除索引为index的数对
        int i;
        for(i = index + 1; i < dSize; i++)
            sortedList[i-1] = sortedList[i];
        sortedList[i] = nullptr; 
        dSize--;
    }
}

#endif //SORTEDARRAYLIST_H

/*
    if(dSize == 0)
    {
        sortedList[dSize++] = new pair<const K, E>(thePair.first ,thePair.second);
        dSize++;
        return;
    }
    int iter = 0;
    for(; iter < dSize && sortedList[iter]->first < thePair.first; iter++);
    if(iter == dSize)
    if(sortedList[iter]->first == thePair.first)
    {
        sortedList[iter]->second = thePair.second;
        return;
    }
    //需要在iter-1的位置插入数对
    //检查是否有足够的空间
    if(dSize == arrayLength)
    {//扩容
        pair<const K, E>** newSortedList = new pair<const K, E>*[arrayLength*2];
        //移动数据
        for(int i = 0; i < iter; i++)
            newSortedList[i] = sortedList[i];
        for(int i = iter + 1; i <= dSize; i++)
            newSortedList[i] = sortedList[i-1];
        delete[] sortedList;
        sortedList = newSortedList;
        arrayLength *= 2;
        sortedList[iter] = new pair<const K, E>(thePair);
        dSize++;
        return;
    }
    //不需要扩容则移动数据
    for(int i = dSize - 1; i >= iter; i--)
        sortedList[i+1] = sortedList[i];
    sortedList[iter] = new pair<const K, E>(thePair);
    dSize++;
    return;
*/