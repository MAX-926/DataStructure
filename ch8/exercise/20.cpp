#include<iostream>
using namespace std;
void towersOfHanoi(int n, int x, int y, int z)
{//程序需要输出被移动的碟子的序号，最小的碟子为1，只对程序的输出进行改动
    if(n > 0)
    {
        towersOfHanoi(n-1, x, z, y);
        cout << "move disk " << n << " from " << x << " to " << y << endl;
        towersOfHanoi(n-1, z, y, x);
    }
}

int main()
{
    towersOfHanoi(4, 1, 2, 3);
}