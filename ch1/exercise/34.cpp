//使用STL算法fill做练习3。fill的语法是fill(start, end, value)
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(a)/sizeof(a[0]);
    fill(a, a+len, 26);
    for(int i = 0; i < len; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << a[11] << " " << a[12];
}