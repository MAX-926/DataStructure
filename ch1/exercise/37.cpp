//使用STL算法is_sorted做练习6.is_sorted的语法是：
//is_sorted(start, end)
//is_sorted()函数判断给定区间内的数据是否按照升序排列
//对于字符串string，检查收元素是否升序(基于ascii值)

#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    string a[] = {"Arina" ,"Bruce", "Max"};
    int len = sizeof(a)/sizeof(a[0]);
    cout << is_sorted(a, a+len);
}