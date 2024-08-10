#ifndef SORTEDCHAINWITHTAILNODE_H
#define SORTEDCHAINWITHTAILNODE_H

#include"dictionary.h"
#include"pairNode.h"
#include<limits.h>

template<class K, class E>
pairNode<K, E> tail(pair<const K, E>(INT_MAX, INT_MAX), nullptr);

//携帶尾節點的有序鏈表
template<class K ,class E>
class sortedChainWithTailNode:public dictionary<K, E>
{
    public:
    //construcor and destructor
        // sortedChainWithTailNode(pairNode<K, E>* theTailNode = TNode):dSize(0)
        sortedChainWithTailNode():dSize(0)
        {
            // tailNode = new pairNode<K, E>(pair<const K, E>(INT_MAX, INT_MAX), nullptr);//如果不行就新建一個結構
            tailNode = &tail<K, E>;
            firstNode = tailNode;
        }
        virtual ~sortedChainWithTailNode();
        bool empty()const { return dSize == 0;}
        int size()const { return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
        void output(ostream&)const;
    protected:
        pairNode<K, E>* firstNode;
        pairNode<K, E>* tailNode;
        int dSize;
};

template<class K, class E>
sortedChainWithTailNode<K, E>::~sortedChainWithTailNode()
{
    while(firstNode != &tail<K, E>)
    {
        pairNode<K, E>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class K, class E>
pair<const K, E>* sortedChainWithTailNode<K, E>::find(const K& theKey)const
{//返回關鍵字對應數對
    //遍歷鏈表
    // pairNode<K, E>* p = firstNode;
    // while(p != nullptr && p->element.first != theKey)
    //     p = p->next;
    // if(p == nullptr)
    //     return nullptr;
    // else
    //     return &(p->element);
    pairNode<K, E>* p = firstNode;
    while(p->element.first != theKey)
        p = p->next;
    if(p == nullptr)
        return nullptr;
    else
        return &(p->element);
}

template<class K, class E>
void sortedChainWithTailNode<K, E>::insert(const pair<const K ,E>& thePair)
{//綫性探查是否存在thePair關聯的pairNode
    pairNode<K, E>* p = firstNode,
                    *tp = nullptr;
    while(p->element.first < thePair.first)
    {
        tp = p;
        p = p->next;
    }
    if(p->element.first == thePair.first)
    {
        p->element.second = thePair.second;
        return;
    }
    pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);
    if(tp == nullptr)
        firstNode = newNode;
    else
        tp->next = newNode;
    dSize++;
}

template<class K, class E>
void sortedChainWithTailNode<K, E>::erase(const K& theKey)
{
    pairNode<K, E>* p = firstNode,
                    *tp = nullptr;
    while(p != nullptr && p->element.first != theKey)
    {
        tp = p;
        p = p->next;
    }
    if(p == nullptr)
        return;
    else
    {
        if(tp == nullptr)
            firstNode = firstNode->next;
        else
            tp->next = p->next;
        delete p;
        dSize--;
    }
}

template<class K, class E>
void sortedChainWithTailNode<K, E>::output(ostream& out)const
{
    pairNode<K, E>* currentNode = firstNode;
    out << endl;
    while(currentNode != tailNode)
    {
        out << currentNode->element.first << " : " << currentNode->element.second << endl;
        currentNode = currentNode->next;
    }
}

template<class K, class E>
ostream& operator<<(ostream& out, const sortedChainWithTailNode<K, E>& scwtn)
{
    scwtn.output(out);
    return out;
}

#endif //SORTEDCHAINWITHTAILNODE_H