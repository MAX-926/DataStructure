/* 程序8-8
// arrayStack<int> towers[4];

// void moveAndShow(int, int, int, int);

// void towersOfHanoi(int n)
// {//moveAndShow
//     for(int d = n; d > 0; d--)
//         towers[1].push(d);
//     moveAndShow(n, 1, 2, 3);
// }

// void moveAndShow(int n, int x, int y, int z)
// {
//     if(n > 0)
//     {
//         moveAndShow(n-1, x, z, y);
//         int d = towers[x].top();
//         towers[x].pop();
//         towers[y].push(d);
//         // showStatus();
//         moveAndShow(n-1, z, y, x);
//     }
// }

*/
//使用栈，将汉诺塔的状态显示出来

#include"../case/8-4.cpp"

arrayStack<int>* tower = new arrayStack<int>[4];
// int diskNum = 0;

// void showState()
// {//显示三座塔的状态
//     for(int i = 1; i < 4; i++)
//     {
//         tower[i].showStack();
//         cout << "tower " << i << endl;
//     }
// }

void showStateEnchanced()
{//水平列印tower的信息,不同的数字不同颜色

    //先找到三座塔高度的最大值
    int maxHeight = 0;
    for(int i = 1; i <= 3; i++)
    {
        if(tower[i].size() > maxHeight)
            maxHeight = tower[i].size();
    }
    while(maxHeight != 0)
    {
        for(int i = 1; i <= 3; i++)
        {
            if(tower[i].size() < maxHeight)
            {
                cout << " " << "\t";
            }
            else 
            {
                int num = tower[i].get(maxHeight-1);
                switch(num)
                {
                    case 1:
                        cout << "\033[32m1\033[0m" << '\t';
                        break;
                    case 2:
                        cout << "\033[33m2\033[0m" << '\t';
                        break;
                    case 3:
                        cout << "\033[34m3\033[0m" << '\t';
                        break;
                    case 4:
                        cout << "\033[35m4\033[0m" << '\t';
                        break;
                    default:
                        printf("\033[36m%d\033[0m\t", num);
                        // cout << num << '\t';
                }
                // cout << tower[i].get(maxHeight-1)  << "\t";
            }
        }
        cout << endl;
        maxHeight--;
    }
    cout << "tower1\ttower2\ttower3\n";
}

void moveAndShow(int n, int x, int y, int z)
{
    if(n > 0)
    {
        moveAndShow(n-1, x, z, y);
        //将1座顶部的碟子移动到2座顶部
        int d = tower[x].top();
        tower[x].pop();
        tower[y].push(d);
        //展示三座塔的状态
        showStateEnchanced();
        moveAndShow(n-1, z, y, x);
    }
}

void towersOfHanoi(int n)
{//主函数，负责初始化moveAndShow函数需要的资源
    //tower[0]弃用
    if(n > 0)
    {
    //初始化tower[1]的状态
        for(int i = n; i >= 1; i--)
            tower[1].push(i);
        showStateEnchanced();
        moveAndShow(n, 1, 2, 3);
    }
}

int main()
{
    towersOfHanoi(5);
}