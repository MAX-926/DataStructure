//适用STL算法mismatch做练习7。mismatch的语法是:
//mismatch(start1, end1, start2)

#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[] = {2, 3, 4, 5, 6, 7};
    int len = sizeof(a)/sizeof(a[0]);
    pair<int*, int*> p1;
    p1 = mismatch(a, a+len, b);
    if(p1.first == a[5]) cout << "mismatch";
}