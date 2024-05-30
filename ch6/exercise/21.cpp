#include"../case/extendedChain.cpp"

template<class T>
void split(extendedChain<T> &c, extendedChain<T> &a, extendedChain<T> &b)
{
    if(a.size()) a.clear();
    if(b.size()) b.clear();
    auto iterC = c.begin();
    for(int i = 0; i < c.size(); i++)
    {
        if(i % 2 == 0)
        {
            b.push_back(*(iterC++));
        }
        else
        {
            a.push_back(*(iterC++));
        }
    }
}

int main()
{
    extendedChain<int> a, b, c;
    for(int i = 0; i < 0; i++)
    {
        c.insert(i, i);
    }
    cout << "c:" << c << endl;
    split(c, a, b);
    cout << "a:" << a << endl << "b:" << b << endl << "c:" << c << endl;
}