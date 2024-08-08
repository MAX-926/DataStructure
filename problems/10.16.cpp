#include<iostream>
#include<utility>
#include"../../Tool.h"
using namespace std;

//散列表使用的函数为除法函数
template<class K, class E>
class hashTable
{
    //constructor, destructor
    hashTable(int theDivisor)
    {
        divisor = theDivisor;
        dSize = 0;
        //分配和初始化散列表数组
        table = new pair<const K, E>*[divisor];
        for(int i = 0; i < divisor; i++)
            table[i] = nullptr;
    }
    ~hashTable();
    //ADT methods:
    //search
    int search(const K& theKey)const;
    //find
    pair<const K, E>* find(const K&)const;
    //insert
    void insert(const pair<const K, E>&);
    //erase
    void erase(const K&);
    //data member
    protected:
        pair<const K, E>** table;//散列表
        hash<K> hash;//把类型K映射到一个非整数
        int dSize;//字典中数对的个数
        int divisor;//散列函数除数
};

// template<class K, class E>
// int hashTable<K, E>::search(const K& theKey)const
// {//搜索一个公开地址散列表，查找关键字为theKey的散列
// //如果匹配的数对存在，返回它的位置，否则，散列表不满，
// //则返回关键字为theKey的数对可以插入的位置
//     int i = (int) hash(theKey) % divisor;
//     int j = i;
//     do{
//         if(table[j] == nullptr || table[j]->first == theKey)//
//             return j;
//         j = (j + 1) % divisor;
//     }while(j != i);//在有回到起点前
//     return j;//等于开头，则说明散列表满，且数对不存在
// }

template<class K, class E>
int hashTable<K, E>::search(const K& theKey)const
{
    int i = hash(theKey);
    int j = i;
    do
    {
        if(table[j] == nullptr || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    }while(j != i);
    return j;
}

template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey)const
{//返回匹配数对的指针
//如果数对不存在，则返回null
    int b = search(theKey);
    if(table[b] == nullptr || table[b]->first != theKey)
        return nullptr;
    return table[b];
}

template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
    int b = search(thePair.first);
    if(table[b] == nullptr)
    {
        table[b] = new pair<const K, E>(thePair);
        dSize++;
    }
    else
        if(table[b]->first == thePair.first)
            table[b]->second = thePair.second;
        else
            throw hashTableFull();
    return;
}

template<class K, class E>
void hashTable<K, E>::erase(const K& theKey)
{//移动那些hash地址不大于当前地址的元素
    int b = search(theKey);
    int currentAddress = b;
    int iter = (b + 1) % divisor;//需要移动的元素在当前删除元素的后面
    if(table[b] == nullptr || table[b]->first != theKey)
        return;
    else
    {
        do
        {
            if(currentAddress >= hash(table[iter]->first))
            {
                table[currentAddress] = table[iter];
                iter = (iter + 1) % divisor;
                currentAddress = (currentAddress + 1) % divisor;
            }
        }
        while(table[iter] != nullptr && iter != b);

    }
}