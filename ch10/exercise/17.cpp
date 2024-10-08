/*
b = 17
num = [7, 42, 25, 70, 14, 38, 8, 21, 34, 11]

hashTable = [34, 0, 70, 0, 38, 21, 0, 7, 42, 25, 8, 11, 0, 0, 14, 0, 0]

插入最后一个关键字后，负载因子为：10/17 = 0.59

在一次失败搜索中，最多和平均查找次数为：
失败查找时，对当前位置需要的检验次数为：[2， 1， 2， 1， 3， 2， 1， 6， 5， 4， 3， 2， 1， 1， 2， 1， 1]
所以最多查找次数：6， 平均查找次数：48/17 = 2.2

在一次成功搜索中，最多和平均查找的桶数：
成功查找，需要检验的次数：[1, 1, 2, 1, 1, 1, 3, 2, 1, 1]
所以最多查找次数：3， 平均查找次数：14/10 = 1.4

*/

#include<iostream>
using namespace std;

int main()
{
    int a[] = {2, 1, 2, 1, 3, 2, 1, 6, 5, 4, 3, 2, 1, 1, 2, 1, 1};
    int sum = 0;
    for(int i = 0; i < 17; i++)
        sum += a[i];
    cout << sum;
}