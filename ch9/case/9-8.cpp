//电路布线
//分两步：距离标记与路径标记
#include<iostream>
#include"9-2.cpp"
#include"../../Tool.h"

#include<fstream>
std::ofstream out("9-8,txt");

using namespace std;


struct position
{//坐标结构
    position(int theRow = 0, int theCol = 0):row(theRow), col(theCol){}
    //纵坐标
    int row;
    //横坐标
    int col;
};

ostream& operator<<(ostream& out, const position& thePos)
{
    out << "(" << thePos.row << ", " << thePos.col << ") "; 
    return out;
}

//global variables
//start place
position start(3, 2);//起点已初始化
//finish place
position finish(4,6);//终点已初始化
//maze matrix
// bool** grid;//需要设置迷宫
int** grid;//需要设置迷宫
//迷宫尺寸
int size = 7;
//路径长度
int pathLength;
//存放路径
position* path;

bool findPath()
{//如果找到路径则返回true，否则返回false
    if(start.row == finish.row && start.col == finish.col)
    {
        pathLength = 0;
        return true;
    }
    //分两步进行：
    //1：标记距离

    // 初始化外墙
    for(int i = 0; i <= size+1; i++)
    {
        grid[0][i] = 1; grid[size+1][i] = 1;
        grid[i][0] = 1; grid[i][size + 1] = 1;
    }

    position here;
    here = start;
    int numOfNbrs = 4;//有四个相邻的可达点
    //a queue to store point that haven't be tagged
    arrayQueue<position> q;
    position offset[4];
    //初始化偏移量
    offset[0].row = 0; offset[0].col = 1;//右
    offset[1].row = 1; offset[1].col = 0;//下
    offset[2].row = 0; offset[2].col = -1;//左
    offset[3].row = -1; offset[3].col = 0;//上
    //初始化起点的距离标记
    grid[start.row][start.col] = 2;

    position nbr;
    do
    {//持续标记，直到找到出口或无路可走
        for(int i = 0; i < numOfNbrs; i++)
        {//标记可达点
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if(grid[nbr.row][nbr.col] == 0)
            {
                grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
                if(finish.row == nbr.row && finish.col == nbr.col)
                    break;
                q.push(nbr);
            }
        }
        output_2DArray<int>(grid, 9, 9);
        if(finish.row == nbr.row && finish.col == nbr.col)
            break;
        if(q.empty()) return false;//没有相邻可达点，且未达到终点，失败
        here = q.front();
        q.pop();
        cout << "output current matrix:\n";
        cout << endl;
    }while(true);
    //找到路径，重构路径
    //存放路径信息
    pathLength = grid[finish.row][finish.col] - 2;//路径长度（不包括start）
    // position path[pathLength];
    path = new position[pathLength];
    here = finish;
    for(int i = pathLength - 1; i >= 0; i-- )
    {
        path[i] = here;
        for(int j = 0; j < numOfNbrs; j++)//第一次出错是因为重复定义了循环变量i,第二次出错是没有看清楚变量的名称
        {
            nbr.row = here.row + offset[j].row;
            nbr.col = here.col + offset[j].col;
            if(grid[nbr.row][nbr.col] == i + 2) break;
        }
        here = nbr;
    }
    return true;
}

int main()
{
    // 分配grid的空间
    // grid = new int*[9];
    // for(int i = 0; i < 9; i++)
    //     grid[i] = new int[9];
    make2dArray<int>(grid, size+2, size+2);
    for(int i = 0; i <= size+1; i++)
        for(int j = 0; j <= size + 1; j++)
            grid[i][j] = 0;
    // for(int i = 0; i <= size+1; i++)
    // {
    //     grid[0][i] = 1; grid[size+1][i] = 1;
    //     grid[i][0] = 1; grid[i][size + 1] = 1;
    // }

    // cout << grid[0][0];    
    //初始化迷宫障碍
    grid[1][3] = 1;
    
    grid[2][3] = 1;
    grid[2][4] = 1;

    grid[3][5] = 1;
    
    grid[4][4] = 1;
    grid[4][5] = 1;
    
    grid[5][1] = 1;
    grid[5][5] = 1;
    
    grid[6][1] = 1;
    grid[6][2] = 1;
    grid[6][3] = 1;
    
    grid[7][1] = 1;
    grid[7][2] = 1;
    grid[7][3] = 1;

    // for(int i = 0; i <= size+1; i++)
    //     for(int j = 0; j <= size + 1; j++)
    //     {
    //         cout << grid[i][j] << " ";
    //         if(((j+1) % 9 == 0)) cout << endl;

    //     }
    // output_2DArray<int>(grid, 9, 9);
    findPath();

    for(int i = 0; i < pathLength; i++)
    {
        cout << path[i] << " ";
    }
}