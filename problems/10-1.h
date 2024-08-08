#ifndef DICTIONARY_H
#define DICTIONARY_H

using namespace std;

template<class K, class E>
class dictionary
{
    public:
        virtual ~dictionary(){}
        //返回false，当且仅当字典为空
        virtual bool empty()const = 0;
        //返回字典中数对的数目
        virtual int size()const = 0;
        //返回匹配数对的指针
        virtual pair<const K, E>* find(const K&)const = 0;
        //往字典中加入一个数对
        virtual void insert(const pair<const K, E>&) = 0;
        //删除匹配的数对
        virtual void erase(const K&) = 0;
};

#endif //DICTIONARY_H