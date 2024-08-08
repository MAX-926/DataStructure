#ifndef DICTIONARY_H
#define DICTIONARY_H

#include<iostream>
using namespace std;

template<class K, class E>
class dictionary
{
    public:
    //ADT Methods:
        virtual ~dictionary(){}
    //返回true，当且仅当字典为空
        virtual bool empty()const = 0;
    //返回字典的数对个数
        virtual int size()const = 0;
    //返回关键字k对应的数对
        virtual pair<const K, E>* find(const K&)const = 0;
    //插入新数对
        virtual void insert(const pair<const K, E>&) = 0;
    //删除匹配的数对
        virtual void erase(const K&) = 0;
};

#endif //DICTIONARY_H