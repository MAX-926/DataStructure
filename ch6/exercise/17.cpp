#include"../case/extendedChain.cpp"

template<class T>
extendedChain<T>* meld(const extendedChain<T> &a, const extendedChain<T> &b)
{
    extendedChain<T>* cp = new extendedChain<T>;
    // int firstPartLength = 2*min(a.size(), b.size());
    auto ita = a.begin(), itb = b.begin();
    for(int i = 0; ; i++)
    {
        if(ita == a.end() || itb == b.end()) break;
        // while(ita != a.end() && itb != b.end())
        // {
            if(i%2 == 0)
                cp->push_back(*(ita++));
            else
                cp->push_back(*(itb++));
        // }
    }
    while(ita != a.end()) cp->push_back(*(ita++));
    while(itb != b.end()) cp->push_back(*(itb++));
    return cp;
}

// int main()
// {
//     extendedChain<int> a, b;
//     for(int i = 0; i < 6; i++)
//     {
//         a.insert(i ,0);
//         // b.insert(i, 0);
//     }
//     for(int i = 0; i < 6; i++)
//     {
//         // a.insert(i ,12);
//         b.insert(i, 1);
//     } 
//     cout << a << endl << b << endl;
//     cout << *meld(a, b);
// }