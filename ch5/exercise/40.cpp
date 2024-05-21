//莫将size()和capacity()弄混！！！
#include"../case/5-12.h"
#include<math.h>


template<class T>
class vectorListWithSplit:public vectorList<T>
{
    public:
        vectorListWithSplit(int initialCapacity = 10):vectorList<T>(initialCapacity){}
        void split(vectorListWithSplit<T> &a, vectorListWithSplit<T> &b);
};

//对空表的情况要单独处理：1.空表的输出 2.对空表不需要split操作，split函数应该直接返回
template<class T>
void vectorListWithSplit<T>::split(vectorListWithSplit<T> &a, vectorListWithSplit<T> &b)
{
    if(this->size() == 0){/*// (a.element)->reserve(0);// (b.element)->reserve(0);*/return;}
    int size_a = std::ceil(this->size()/2);
    int size_b = this->size() - size_a;
    int i, j, k;
    i = j = k  = 0;
    for(; i < this->size(); i++)
        i % 2 == 0 ? a.insert(j++, this->get(i)) : b.insert(k++, this->get(i));
}

int main()
{
    vectorListWithSplit<int> a, b, c;
    for(int i = 0; i < 2; i++)
        c.insert(i, i+1);
    c.split(a, b);
    std::cout << c << std::endl << a << std::endl << b << std::endl;
}