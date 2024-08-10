#ifndef SORTEDCHAINWITHTWOHEAD_H
#define SORTEDCHAINWITHTWOHEAD_H
//包含头节点和尾节点的有序链表

#include"../case/dictionary.h"
#include"../case/pairNode.h"
#include<iostream>
#include<limits.h>
using namespace std;

template<class K, class E>
pairNode<K, E> tailNode(pair<const K, E>(INT_MAX, INT_MAX), nullptr);//全局对象

template<class K, class E>
class sortedChainWithTwoHead:public dictionary<K, E>
{
    public:
        sortedChainWithTwoHead()
        {
            tail = &tailNode<K, E>;
            head = new pairNode<K, E>(pair<const K, E>(INT_MAX, INT_MAX), tail);
            dSize = 0;
        }
        virtual ~sortedChainWithTwoHead()
        {
            while(head->next != tail)
            {
                pairNode<K, E>* nextNode = head->next->next;
                delete head->next;
                head->next = nextNode;
            }
        }
        bool empty()const { return dSize == 0;}
        int size()const { return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
        void output(ostream&)const;
    protected:
        pairNode<K, E>* head;//头节点
        pairNode<K, E>* tail;//尾节点
        int dSize;//字典的数对膈俞
};

template<class K, class E>
void sortedChainWithTwoHead<K, E>::output(ostream& out)const
{
    out << endl;
    pairNode<K, E>* currentNode = head->next;
    while(currentNode != tail)
    {
        out << currentNode->element.first << " : " << currentNode->element.second << endl;
        currentNode = currentNode->next;
    }
}

template<class K, class E>
ostream& operator<<(ostream& out, const sortedChainWithTwoHead<K, E>& scwth)
{
    scwth.output(out);
    return out;
}

template<class K ,class E>
pair<const K, E>* sortedChainWithTwoHead<K, E>::find(const K& theKey)const
{//在一个有序链表中查找
    pairNode<K, E>* currentNode = head;
    do
    {
        currentNode = currentNode->next;
        if(currentNode->element.first == theKey)
            return &(currentNode->element);
    }
    while(currentNode != tail);
    return nullptr;
}

template<class K, class E>
void sortedChainWithTwoHead<K, E>::insert(const pair<const K, E>& thePair)
{//将数对插入有序链表
    pairNode<K, E>* p = head,
                    *tp = nullptr;
    do
    {
        tp = p;
        p = p->next;
    }while(p != tail && p->element.first < thePair.first);
    if(p->element.first == thePair.first)
    {
        p->element.second = thePair.second;
        return;
    }
    else
    {
        tp->next = new pairNode<K, E>(thePair, p);
        dSize++;
        return;
    }
}

template<class K, class E>
void sortedChainWithTwoHead<K, E>::erase(const K& theKey)
{//将数对从有序链表中删除
    pairNode<K, E>* p = head,
                    *tp = nullptr;
    do
    {
        tp = p;
        p = p->next;
    }while(p != tail && p->element.first != theKey);
    if(p == tail)
        return;
    tp->next = p->next;
    dSize--;
    delete p;
    return;
}

template<class K, class E>
class hashChains:public dictionary<K, E>
{
    public:
        hashChains(int theDivisor = 11)
        {
            divisor = theDivisor;
            dSize = 0;
            table = new sortedChainWithTwoHead<K, E>[divisor];
        }
        virtual ~hashChains()
        {
            delete[] table;
        }
        bool empty()const { return dSize == 0;}
        int size()const {return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
        void output(ostream&)const;
    protected:
        sortedChainWithTwoHead<K, E>* table;
        int dSize;
        int divisor;
        hash<K> hash;
};

template<class K, class E>
pair<const K, E>* hashChains<K, E>::find(const K& thekey)const
{//根据键值寻找指定数对
    return table[hash(thekey) % divisor].find(thekey);    
}

template<class K, class E>
void hashChains<K, E>::insert(const pair<const K, E>& thePair)
{//将数对thePair插入散列
    int b = hash(thePair.first) % divisor;
    int homeSize = table[b].size();
    table[b].insert(thePair);
    if(homeSize != table[b].size())
        dSize++;
}

template<class K, class E>
void hashChains<K, E>::erase(const K& theKey)
{//将数对thePair插入散列
    int b = hash(theKey) % divisor;
    int homeSize = table[b].size();
    table[b].erase(theKey);
    if(homeSize != table[b].size())
        dSize--;
}

template<class K, class E>
void hashChains<K, E>::output(ostream& out)const
{
    for(int i = 0; i < divisor; i++)
    {
        if(table[i].empty())
            out << "\nthis bucket is null\n";
        else
        {
            out << "\nbelow is chain:\n";
            out << table[i];
        }
    }
}

template<class K, class E>
ostream& operator<<(ostream& out, const hashChains<K, E>& hc)
{
    hc.output(out);
    return out;
}


#endif //SORTEDCHAINWITHTWOHEAD_H