#include"8-4.cpp"
//使用栈求解hanoi问题
//全局变量，tower[1:3]表示三个塔
// arrayStack<int> tower[4];

// void moveAndShow(int, int, int, int);

// void towersOfHanoi(int n)
// {//函数moveAndShow的预处理函数
//     for(int i = n; i > 0; i--)//初始化
//         tower[1].push(i);//把碟子i加到塔1
//     //把n个碟子从塔1移到塔3
//     moveAndShow(n, 1, 2, 3);
// }

// // void showState()
// // {
// //     for(int i = 0; i < )
// // }

// void moveAndShow(int n, int x, int y, int z)
// {//把塔x顶部的n个碟子移到塔y，显示移动后的布局
//  //用塔z作为中转塔
//     if(n > 0)
//     {
//         moveAndShow(n-1, x, z, y);
//         int d = tower[x].top();
//         tower[x].pop();
//         tower[y].push(d);
//         // showState();//显示塔3的布局
//         moveAndShow(n-1, z, y, x);
//     }
// }

// int main()
// {
//     towersOfHanoi(3);
// }

arrayStack<int> towers[4];

void moveAndShow(int, int, int, int);

void towersOfHanoi(int n)
{//moveAndShow
    for(int d = n; d > 0; d--)
        towers[1].push(d);
    moveAndShow(n, 1, 2, 3);
}

void moveAndShow(int n, int x, int y, int z)
{
    if(n > 0)
    {
        moveAndShow(n-1, x, z, y);
        int d = towers[x].top();
        towers[x].pop();
        towers[y].push(d);
        // showStatus();
        moveAndShow(n-1, z, y, x);
    }
}