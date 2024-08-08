//链式散列表
#include"10-1.h"
#include<iostream>
#include"sortedChain.h"
using namespace std;

template<class K, class E>
class hashChains:dictionary<K, E>
{
    public:
        hashChains(int theDivisor = 11);
        ~hashChains(){delete[] table;}
        //ADT Methods：
        bool empty()const{return dSize == 0;}
        int size()const{return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
        void output(ostream&)const;
    protected:
        sortedChain<K, E>* table;//链式散列表
        int dSize;//散列表数对个数
        int divisor;//哈希除法函数的除数
        hash<K> hash;//将关键字转换为整数
};

template<class K, class E>
ostream& operator<<(ostream& out, const hashChains<K, E>& hc)
{
    hc.output(out);
    return out;
}

template<class K, class E>
hashChains<K, E>::hashChains(int theDivisor)
{
    divisor = theDivisor;
    //对divisor做合法性检查
    table = new sortedChain<K, E>[divisor];
    dSize = 0;
}

template<class K, class E>
pair<const K, E>* hashChains<K, E>::find(const K& theKey)const
{//根据关键字theKey，返回散列表的空间
    int i = hash(theKey) % divisor;//现将关键字映射为数字
    pair<const K, E>* thePair = table[i].find(theKey);//线性查询
    if(thePair == nullptr) return nullptr;
    else return thePair;
}

template<class K, class E>
void hashChains<K, E>::insert(const pair<const K, E>& thePair)
{//将thePair插入对应位置
    int i = hash(thePair.first) % divisor;//对应的桶号
    pair<const K, E>*  pairPointer = table[i].find(thePair.first);
    if(pairPointer == nullptr)
    {//代表当前数对还没有加入散列中
        table[i].insert(thePair);
        return;
    }
    else
    {
        pairPointer->second = thePair.second;//更新已有关键字数对的value
        return;
    }
}

template<class K, class E>
void hashChains<K, E>::erase(const K& theKey)
{//删除关键字对应数对，若数对存在，否则返回
    int b = hash(theKey) % divisor;
    pair<const K, E>* thePair = table[b].find(theKey);
    if(thePair == nullptr)
    {//代表sortedChain中没有theKey对应的数对
        return;
    }
    else
        table[b].erase(theKey);
}

template<class K, class E>
void hashChains<K, E>::output(ostream& out)const
{
    for(int i = 0; i < divisor; i++)
    {
        if(table[i].empty())
            cout << "NULL\n";
        else
            cout << table[i];
    }
}

int main()
{
    hashChains<char, int> hc;
    char ch = 'a';
    int num = 1;
    for(int i = 0; i < 10; i++)
    {
        hc.insert(pair<const char, int>(ch++, num++));
    }
    cout << hc;
}