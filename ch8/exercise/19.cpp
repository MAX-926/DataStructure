//对碟子数运用归纳法，证明程序8-7的正确性

#include<iostream>
using namespace std;
void towersOfHanoi(int n, int x, int y, int z)
{
    if(n > 0)
    {
        towersOfHanoi(n-1, x, z, y);
        cout << "move top of the disk from " << x << " to " << y << endl;
        towersOfHanoi(n-1, z, y, x);
    }
}

/*
归纳基础：

hanoi(1, 1, 2, 3):
    hanoi(0, 1, 3, 2)->return;
        move top of the disk from 1 to 2
            hanoi (0, 3, 2, 1)->return;
结论正确


归纳假设：

假设hanoi(n, 1, 2, 3)正确

归纳步骤：
要证明hanoi(n+1, 1, 2, 3)正确

即将n个碟子移到3号柱，再把最大的碟子移到2号柱，最后将n个碟子从3号柱移到2号柱
hanoi(n+1, 1, 2, 3)
    hanoi(n, 1, 3, 2)//即算法会正确地将n个碟子从1号座移到3号座
        move top of the disk from 1 to 3//显而易见操作将被正确执行
            hanoi(n, 3, 2, 1)//此时最大的碟子在2号座的底部，对与从3号座以正确的方式将n个碟子移到2号座来说没有影响

*/