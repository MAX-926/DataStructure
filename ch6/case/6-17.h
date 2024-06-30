#include"6-16.h"
#include"6-2.h"

void binSort(chain<studentRecord> &theChain, int range)
{
    //按分数排序
    //对箱子初始化
    chain<studentRecord>* bin;
    bin = new chain<studentRecord>[range + 1];

    //把学生记录从链表取出，然后分配到箱子里
    int numberOfElements = theChain.size();
    for(int i = 1; i <= numberOfElements; i++)
    {
        studentRecord x = theChain.get(0);
        theChain.erase(0);
        bin[x.score].insert(0, x);
    }

    //从箱子中收集元素
    for(int i = range; i >= 0; i--)
    {
        while(!bin[i].empty())
        {
            studentRecord x = bin[i].get(0);
            bin[i].erase(0);
            theChain.insert(0, x);
        }
    }
    delete []bin;
}

