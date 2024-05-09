//使用STL算法iota做练习5.iota的语法是:iota(start, end, value)
#include<iostream>
#include<numeric>
using namespace std;
//iato产生一个顺序序列(递增)，以给定的value为开头，逐步+1，以填满start->end
int main()
{
    int s[] = {1, 2, 3, 4, 5, 6, 7};
    int *ip = NULL;
    ip = new int[7];
    int len = sizeof(s)/sizeof(s[0]);
    iota(ip, ip+7, 100);
    for(int i = 0; i < len; i++)
        cout << ip[i] << " ";
    delete []ip;
}