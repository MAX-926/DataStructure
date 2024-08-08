//sortedChain
#ifndef SORTEDCHAIN_H
#define SORTEDCHAIN_H

#include<iostream>
#include"pairNode.h"
#include"10-1.h"
using namespace std;


// template<class K, class E>
// struct pairNode
// {
//     //constructor
//     pairNode(const K& theK, const E& theE)
//     {
//         element(theK, theE);
//         next = nullptr;
//     }
//     //overloading constructor
//     pairNode(pair<const K, E>& thePair, pairNode<K, E>* theNext = nullptr)//支持将pair类型的数据作为参数传入构造pairNode对象
//     {
//         element = thePair;
//         next = theNext;
//     }
//     //data
//     pair<const K, E> element;
//     //pointer
//     pairNode<K, E>* next;//pairNode传递信息k给pair以使pair完成初始化工作，pair的键值要求为不可更改的，所以引入const修饰符
// };

//sortedChain class
template<class K, class E>
class sortedChain:public dictionary<K, E>//是字典，不是多重字典
{
    public:
        sortedChain();
        sortedChain(const sortedChain<K, E>&);
        ~sortedChain();
        //ADT Methods:
        bool empty()const {return firstNode == nullptr;}
        int size()const { return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
        //将链表输出
        void output()const;
    protected:
        //头节点
        pairNode<K, E>* firstNode;
        //尾节点
        pairNode<K, E>* lastNode;
        int dSize;
};

template<class K, class E>
sortedChain<K, E>::sortedChain()
{
    firstNode = nullptr;
    lastNode = nullptr;
    dSize = 0;
}

template<class K, class E>
sortedChain<K, E>::sortedChain(const sortedChain<K, E>& theSc)
{
    if(theSc.firstNode == nullptr)
    {
        firstNode = nullptr;
        lastNode = nullptr;
        dSize = 0;
        return;
    }
    dSize = theSc.dSize;
    firstNode = new pairNode<K, E>(theSc.firstNode->element.first, theSc.firstNode->element.second);
    pairNode<K, E>* nodeIter = theSc.firstNode, *thisIter = firstNode;
    nodeIter = nodeIter->next;
    while(nodeIter != nullptr)
    {
        thisIter->next = new pairNode<K, E>(nodeIter->element.first, nodeIter->element.second);
        nodeIter = nodeIter->next;
        thisIter = thisIter->next;
    }
    lastNode = thisIter;
}

template<class K, class E>
sortedChain<K, E>::~sortedChain()
{
    while(firstNode != nullptr)
    {
        pairNode<K, E>* nextPairNode = firstNode->next;
        delete firstNode;
        firstNode = nextPairNode;
    }
}

template<class K, class E>
pair<const K, E>* sortedChain<K, E>::find(const K& theK)const
{//根据键值寻找对应的pair，如果不存在指定的pair则返回nullptr
    pairNode<K, E>* currentNode = firstNode;
    //搜索关键字为theK的数对
    while(currentNode != nullptr && currentNode->element.first != theK)//最坏情况：O(n)
        currentNode = currentNode->next;
    //判断是否匹配
    if(currentNode != nullptr && currentNode->element.first == theK)//有必要再判断first与theK相等吗？？
        //找到匹配数对
        return &currentNode->element;
    //无匹配数对
    return nullptr;
}

template<class K ,class E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{//向sortedChain插入新的数对
    //往字典中插入thePair，覆盖已经存在的匹配的数对
    pairNode<K, E>* p = firstNode, 
                  *tp = nullptr; //tp trails p
    //移动指针tp，使thePair可以插在tp后面
    while(p != nullptr && p->element.first < thePair.first)
    {
        tp = p;
        p = p->next;
    }
    if(p != nullptr && p->element.first == thePair.first)
    {//如果键值已经存在，则更新当前键值对应的值
        p->element.second = thePair.second;
        return;
    }
    //执行到此说明p->element.first > thePair.first
        pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);//p是一个位次恰好在thePair之后的节点
        if(tp == nullptr)
            firstNode = newNode;
        else
            tp->next = newNode;
        dSize++;
        return;
}

template<class K, class E>
void sortedChain<K, E>::erase(const K& theK)
{//将键theK对应的数对删除
    pairNode<K, E>* currentNode = firstNode,
                  * tp = nullptr;
    while(currentNode != nullptr && currentNode->element.first < theK)
    {
        tp = currentNode;
        currentNode = currentNode->next;
    }
    if(currentNode != nullptr && currentNode->element.first == theK)
    {//找到一个匹配的数对
        if(tp == nullptr)
        //说明字典只有一个节点
            firstNode = currentNode->next;
        tp->next = currentNode->next;
        delete currentNode;
        dSize--;
        return;
    }
}

template<class K, class E>
void sortedChain<K, E>::output()const
{
    pairNode<K, E>* currentNode = firstNode;
    while(currentNode != nullptr)
    {
        cout << currentNode->element.second << " ";
        currentNode = currentNode->next;
    }
}

#endif //SORTEDCHAIN_H

// int main()
// {
//     char ch = 'a';
//     int num = 1;
//     sortedChain<char, int> sc;
//     // for(int i = 0; i < 10; i++)
//     // {
//     //     sc.insert(pair<char, int>(ch++, num++));
//     // }

//     // ch = 'a';
//     // for(int i = 0; i < 10; i++)
//     //     cout << sc.find(ch++)->second << " ";
//     sc.insert(pair<char, int>(ch, num));
//     sc.insert(pair<char, int>(ch+5, num+10));
//     sc.insert(pair<char, int>(ch+4, num+22));
//     sc.insert(pair<char, int>(ch+2, num+45));
//     sc.output();
// }