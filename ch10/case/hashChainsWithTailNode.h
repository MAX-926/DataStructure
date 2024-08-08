#ifndef HASHCHAINSWITHTAILNODE_H
#define HASHCHIANSWITHTAILNODE_H
#include"dictionary.h"
#include"pairNode.h"
// #include"sortedChain.h"
#include"sortedChainWithTailNode.h"
#include<iostream>
#include<limits.h>


template<class K, class E>
class hashChainsWithTailNode:public dictionary<K, E>
{
    public:
        //constructor and destructor:
        hashChainsWithTailNode(int theDivisor = 11)
        {
            divisor = theDivisor;
            dSize = 0;
            table = new sortedChainWithTailNode<K ,E>[divisor];
        }
        virtual ~hashChainsWithTailNode() {delete[] table;}
        //ADT Meothods:
        bool empty()const { return dSize == 0;}
        int size()const { return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>& thePair);
        void erase(const K&);
        void output(ostream&)const;
    protected:
        sortedChainWithTailNode<K, E>* table;
        hash<K> hash;
        int divisor;
        int dSize;
};

template<class K, class E>
pair<const K, E>* hashChainsWithTailNode<K, E>::find(const K& theKey)const
{
    return table[hash(theKey) % divisor].find(theKey);
}


template<class K, class E>
void hashChainsWithTailNode<K, E>::insert(const pair<const K, E>& thePair)
{
    int homeSize = table[hash(thePair.first) % divisor],size();
    table[hash(thePair.first) % divisor].insert(thePair);
    if(homeSize - table[hash(thePair.first) % divisor].size())
        dSize++;
}

template<class K, class E>
void hashChainsWithTailNode<K, E>::erase(const K&theKey)
{
    int homeSize = table[hash(thePair.first) % divisor],size();
    table[hash(theKey) % divisor].erase(theKey);
    if(homeSize - table[hash(theKey) % divisor].size())
        dSize--;
}

template<class K, class E>
void hashChainsWithTailNode<K, E>::output(ostream& out)const
{
    out << endl;
    for(int i = 0; i < divisor; i++)
    {
        if(table[i].empty())
            out << "NULL\n";
        else    out << table[i];
    }
}


template<class K, class E>
ostream& operator<<(ostream& out, const hashChainsWithTailNode<K, E>& hcwtn)
{
    hcwtn.output(out);
    return out;
}

#endif //HASHCHAINSWITHTAILNODE