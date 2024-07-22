/*
对4个碟子的汉诺塔问题，用笔计算出碟子的移动序列

1 
2
3
4

移动序列： 1->3 1->2 3->2 1->3 2->1 2->3 1->3 1->2 3->2 3->1 2->1 3->2 1->3 1->2 3->2
*/

#include<iostream>
using namespace std;

void hanoi(int n, int x, int y, int z)
{
    if(n > 0)
    {
        hanoi(n-1, x, z, y);
        cout << "Move disk from " << x << " to " << y << endl;
        hanoi(n-1, z, y, x);
    }
}

int main()
{
    hanoi(4, 1, 2, 3);
}