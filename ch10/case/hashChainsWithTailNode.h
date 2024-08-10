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
            // tailNode = new pairNode<K, E>(pair<const K, E>(INT_MAX, INT_MAX), nullptr);//如果不行就新建一個結構
            //调用构造函数构建sortedChainWithTailNode数组
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
        pairNode<K, E>* tailNode;
};

template<class K, class E>
pair<const K, E>* hashChainsWithTailNode<K, E>::find(const K& theKey)const
{
    return table[hash(theKey) % divisor].find(theKey);
}

template<class K, class E>
void hashChainsWithTailNode<K, E>::insert(const pair<const K, E>& thePair)
{
    int homeSize = table[hash(thePair.first) % divisor].size();
    table[hash(thePair.first) % divisor].insert(thePair);
    if(homeSize - table[hash(thePair.first) % divisor].size())
        dSize++;
}

template<class K, class E>
void hashChainsWithTailNode<K, E>::erase(const K&theKey)
{
    int homeSize = table[hash(theKey) % divisor].size();
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

/*

he chain is 
NULL

1 : 5
12 : 60

2 : 10
24 : 160
35 : 230
NULL

15 : 69
NULL

6 : 30

40 : 80

8 : 40
19 : 65
NULL

10 : 50

Its size is 11
Element associated with 1 is 5
Element associated with 6 is 30
Element associated with 12 is 60
Deleted 1, 2, 6, 12
The chain is
NULL
NULL

24 : 160
35 : 230
NULL

15 : 69
NULL
NULL

40 : 80

8 : 40
19 : 65
NULL

10 : 50

Its size is 7

The chain is 
this bucket is null
below is chain:
1 : 5
12 : 60
below is chain:
2 : 10
24 : 160
35 : 230
this bucket is null
below is chain:
15 : 69
this bucket is null
below is chain:
6 : 30
below is chain:
40 : 80
below is chain:
8 : 40
19 : 65
this bucket is null
below is chain:
10 : 50
Its size is 11
Element associated with 1 is 5
Element associated with 6 is 30
Element associated with 12 is 60
Deleted 1, 2, 6, 12
The chain is
this bucket is null
this bucket is null
below is chain:
24 : 160
35 : 230
this bucket is null
below is chain:
15 : 69
this bucket is null
this bucket is null
below is chain:
40 : 80
below is chain:
8 : 40
19 : 65
this bucket is null
below is chain:
10 : 50
Its size is 7
*/