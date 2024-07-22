#include<iostream>
using namespace std;

//当中转塔的个数>1时
//n:碟子数， x:初始塔， y:目标塔， k:中转塔个数
//当k == 2时：
void hanoiBase(int, int, int, int);
void hanoi(int n, int x, int y, int z, int z1)
{
    if(n > 0)
    {
        hanoi((n-1)/2, x, z, y, z1);
        hanoiBase((n-1)-(n-1)/2, x, z1, y);
        cout << "Move top of the disk from " << x << " to " << y << endl;
        hanoiBase((n-1)-(n-1)/2, z1, y, x);
        hanoi(n-1, z, y, x, z1);
    }
}

void hanoiBase(int n, int x, int y, int z)
{
    if(n > 0)
    {
        hanoiBase(n-1, x, z, y);
        cout << "Move top of the disk from " << x << " to " << y << endl;
        hanoiBase(n-1, z, y, x);
    }
}

int main()
{
    hanoi(4, 1, 2, 3, 4);
}

//
//1 2 3 4
//s t f f

//M柱汉诺塔问题
/*
大致思路：
S1：通过M柱汉诺塔算法将1柱的n-r个碟子由1柱移动到2柱，借助3...M柱实现
S2：通过M-1柱汉诺塔算法将1柱的r个碟子由1柱移动到M柱，借助3...M-1柱实现
S3：通过M柱汉诺塔算法将2柱的n-r个碟子由2柱移动到M柱，借助1, 3...M柱实现
S4:根据上述规则，求出所有r(1<=r<=n)情况下步数m(n), 取最小值得最终解//需要通过frame算法(M柱汉诺塔算法)循环验证查找最佳的r,这个r使得M柱汉诺塔算法取得最佳解
*/