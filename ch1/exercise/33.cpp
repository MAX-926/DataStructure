//使用STL算法count做练习2。count的语法是：count(start, end, value)
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int a[] = {1, 2, 3, 4, 5, 4, 2, 5, 6, 2, 3, 56, 3, 6};
    int len = sizeof(a)/sizeof(a[0]);
    sort(a, a+len);
    for(int i = 0; i < len; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << count(a, a+len, 4);
}