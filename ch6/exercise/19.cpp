//非成员方法merge 生成一个有序链表
#include"../case/extendedChain.cpp"

template<class T>
extendedChain<T>*  merge(extendedChain<T> &a, extendedChain<T> &b)
{
    extendedChain<T>* c = new extendedChain<T>;
    auto iterA = a.begin(), iterB = b.begin();
    while(iterA != a.end() && iterB != b.end())
    {
        if(*(iterA) == *(iterB))
        {
            c->push_back(*(iterB++));
            continue;
        }
        c->push_back( *(iterA) > *(iterB) ? *(iterB++):*(iterA++) );
    }       
    while(iterA != a.end()){ c->push_back(*(iterA++));}
    while(iterB != b.end()) {c->push_back(*(iterB++));}
    return c;
}

int main()
{
    extendedChain<int> a, b;
    for(int i = 0; i < 8; i++)
    {
        a.insert(i, i+10);
        // b.insert(i, i+100);
    }
    for(int i = 0; i < 5; i++)
    {
        // a.insert(i, i+1);
        b.insert(i, i+100);
    }
    cout << "a:" << a << endl << "b:" << b << endl;
    extendedChain<int>* c = merge(a, b);
    cout << "a:" << a << endl << "b:" << b << endl << "c:" << *c << endl;
}