//非成员方法merge 生成一个有序链表
#include"../case/extendedChain.cpp"

template<class T>
extendedChain<T>*  merge(extendedChain<T> &a, extendedChain<T> &b)//O(a.size+b.size),因为函数会调取listA与listB的所有节点
{
    extendedChain<T>* c = new extendedChain<T>;
    auto iterA = a.begin(), iterB = b.begin();
    while(iterA != a.end() && iterB != b.end())//O(min(a.size, b.size)),这里会把其中一条list遍历完
    {
        if(*(iterA) == *(iterB))//o(1)
        {
            c->push_back(*(iterB++));//因为有lastNode所以push_back的代价为O(1)
            continue;
        }
        c->push_back( *(iterA) > *(iterB) ? *(iterB++):*(iterA++) );//O(1)
    }       
    while(iterA != a.end()){ c->push_back(*(iterA++));}//O(a.lastSize)，这里会把未遍历完的list遍历完
    while(iterB != b.end()) {c->push_back(*(iterB++));}//O(b.lastSize)，这里会把未遍历完的list遍历完
    return c;
}

int main()
{
    extendedChain<int> a, b;
    for(int i = 0; i < 10; i++)
    {
        a.insert(i, i);
        // b.insert(i, i+100);
    }
    for(int i = 0; i < 8; i++)
    {
        // a.insert(i, i+1);
        b.insert(i, i);
    }
    cout << "a:" << a << endl << "b:" << b << endl;
    extendedChain<int>* c = merge(a, b);
    cout << "a:" << a << endl << "b:" << b << endl << "c:" << *c << endl;
}