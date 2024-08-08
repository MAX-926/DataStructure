#ifndef HASHCHAINS_H
#define HASHCHAINS_H
//鏈式哈希表

#include"dictionary.h"
#include<iostream>
#include"sortedChain.h"
#include"../../Tool.h"

template<class K, class E>
class hashChains:public dictionary<K, E>
{
    public:
    //constructor and destructor
        hashChains(int theDivisor = 11);
        ~hashChains();
    //ADT Methods:
        bool empty()const { return dSize == 0;}
        int size()const { return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
        void output(ostream&)const;
    protected:
        int search(const K&)const;
        sortedChain<K, E>* table;
        int divisor;
        int dSize;
        hash<K> hash;
};

template<class K, class E>
hashChains<K, E>::hashChains(int theDivisor):divisor(theDivisor), dSize(0)
{//初始化table
    table = new sortedChain<K, E>[divisor];
}

template<class K, class E>
hashChains<K, E>::~hashChains()
{
    delete[] table;
}

template<class K, class E>
int hashChains<K, E>::search(const K& theKey)const
{//返回關鍵字theKey的數對所在桶的編號
    return hash(theKey) % divisor;
}

template<class K, class E>
pair<const K, E>* hashChains<K, E>::find(const K& theKey)const
{//在鏈表中尋找數對
    // int b = search(theKey);
    // if(table[b].empty())
    //     return nullptr;
    // else
    // {//在鏈表中搜索數對
    //     return table[b].find(theKey);
    // }
    return table[hash(theKey) % divisor].find(theKey);
}

template<class K, class E>
void hashChains<K, E>::insert(const pair<const K ,E>& thePair)
{
    // int b = search(thePair.first);
    int b = hash(thePair.first) % divisor;
    int homeSize = table[b].size();
    table[b].insert(thePair);
    if(homeSize < table[b].size())
        dSize++;
    // pair<const K, E>* target = table[b].find(thePair.first);
    // if(target != nullptr)
    // {
    //     target->second = thePair.second;
    //     return;
    // }
    // else
    // {
    //     table[b].insert(thePair);
    //     dSize++;
    //     return;
    // }
}

template<class K, class E>
void hashChains<K, E>::erase(const K& theKey)
{
    table[hash(theKey) % divisor].erase(theKey);
    // int b = search(theKey);
    // if(table[b].empty())
    //     throw hashTableFull();
    // int oldSize = table[b].size();
    // table[b].erase(theKey);
    // if(table[b].size() - oldSize != 0)
    //     dSize--;
}

template<class K, class E>
void hashChains<K, E>::output(ostream& out)const
{
    for(int i = 0; i < divisor; i++)
    {
        out << endl;
        if(table[i].empty())
            out << "********NULL********\n";
        else
            out << table[i];
        out << "____________________________________\n";
    }
}

template<class K, class E>
ostream& operator<<(ostream& out, const hashChains<K, E>& hc)
{
    hc.output(out);
    return out;
}

#endif //HASHCHAINS_H