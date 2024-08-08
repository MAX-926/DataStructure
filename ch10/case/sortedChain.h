//有序链表，其成员为数对
#ifndef SORTEDCHAIN_H
#define SORTEDCHAIN_H

#include<iostream>
#include"pairNode.h"
#include"dictionary.h"


template<class K, class E>
class sortedChain:public dictionary<K, E>
{//有序数对链表
    public:
        sortedChain():firstNode(nullptr), dSize(0){}
        ~sortedChain()
        {
            while(firstNode != nullptr)
            {
                pairNode<K, E>* nextNode = firstNode->next;
                delete firstNode;
                firstNode = nextNode;
            }
        }
        bool empty()const {return dSize == 0;}
        int size()const { return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
        void output(ostream&)const;
    protected:
        pairNode<K, E>* firstNode;//有序链表对象
        int dSize;//有序链表中元素的个数
};

template<class K, class E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey)const
{//返回字典中对应数对
    pairNode<K, E>* currentNode = firstNode;
    while(currentNode != nullptr && currentNode->element.first != theKey)
        currentNode = currentNode->next;

    if(currentNode != nullptr && currentNode->element.first == theKey)
        return &currentNode->element;
    else
        return nullptr;
}

template<class K, class E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{//将数对插入有序链表
    pairNode<K, E>* p = firstNode,
                    *tp = nullptr;
    while(p != nullptr && p->element.first < thePair.first)
    {
        tp = p;
        p = p->next;
    }
    if(p != nullptr && p->element.first == thePair.first)
    {
    //说明存在关键字为thePair.first的数对
        p->element.second = thePair.second;
        return;
    }
    pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);
    if(tp == nullptr)
        firstNode = newNode;
    else
        tp->next = newNode;
    dSize++;
    return;
}

template<class K, class E>
void sortedChain<K, E>::erase(const K& theKey)
{//从有序链表中删除关键字theKey对应的数对
    pairNode<K, E>* p = firstNode, *tp = nullptr;
    while(p != nullptr && p->element.first < theKey)
    {
        tp = p;
        p = p->next;
    }
    if(p != nullptr && p->element.first == theKey)
    {
        if(tp == nullptr) firstNode = p->next;//有序链表只有一个元素时
        else tp->next = p->next;
        delete p;
        dSize--;
        return;
    }
}

template<class K, class E>
void sortedChain<K, E>::output(ostream& out)const
{
    pairNode<K, E>* currentNode = firstNode;
    while(currentNode != nullptr)
    {
        out << endl;
        out << currentNode->element.first << " : " << currentNode->element.second << endl; 
        currentNode = currentNode->next;
    }
}

template<class K, class E>
ostream& operator<<(ostream& out, const sortedChain<K, E>& hc)
{
    hc.output(out);
    return out;
}
#endif // SORTEDCHAIN_H