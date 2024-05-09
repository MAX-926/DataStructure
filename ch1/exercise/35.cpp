//使用STL算法inner_product做练习4。inner_product的语法是:inner_product(start1, end1, start2, initialValue)
#include<iostream>
#include<numeric>
using namespace std;

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {2, 4, 6, 8, 10};
    cout << inner_product(a, a+5, b, 0);
}