//子集生成办法

#include<iostream>
#include<string.h>
#include<iterator>
#include<algorithm>
#include<vector>
using namespace std;

template<class T>
void Func(vector<T> &s, int i, int n)
{
    if(i == n)
    {
        copy(s.begin(), s.end(), ostream_iterator<T>(cout, " "));
        cout << endl;
    }
    else
    {
        s[i] = 0;
        Func(s, i+1, n);
        s[i] = 1;
        Func(s, i+1, n);
    }
}

int main()
{
    string s("abc");
    vector<bool> tb(s.size(), 0);
    Func(tb, 0, s.size());
}