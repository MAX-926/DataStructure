//电路布线问题：
//实质：在网格中寻找一两个定点的最短距离
//需要用到的结构：队列

#include<iostream>
#include"Tool.h"
#include"ch9/case/9-2.cpp"

using namespace std;


struct position
{
    //constructor
    position(int theRow = 0, int theCol = 0):row(theRow), col(theCol){}
    //纵坐标
    int row;
    //横坐标
    int col;
};

ostream& operator<<(ostream& out, const position& pos)
{
    out << "(" << pos.row << "," << pos.col << ")" << " ";
    return out;
}

//运行前初始化参数
position start(3, 4);
position finish(4, 6);
int** maze;//迷宫
int size = 7;//迷宫的尺寸
int pathLength;
position* path;


bool findPath()
{//寻找矩阵中两定点的最短距离
//若找到路径返回true，若失败返回false
//S1：标记距离 S2：标记路径
    if(start.row == finish.row && start.col == finish.col)//若终点与起点相同，返回
    {
        pathLength = 0;
        return true;
    }
    //构建迷宫外墙
    for(int i = 0; i <= size+1; i++)
    {
        maze[0][i] = maze[size+1][i] = 1;
        maze[i][0] = maze[i][size+1] = 1;
    }
    //偏移量表
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;
    offset[1].row = 1; offset[1].col = 0;
    offset[2].row = 0; offset[2].col = -1;
    offset[3].row = -1; offset[3].col = 0;

    maze[start.row][start.col] = 2;//解决1的歧义：既表达障碍又表达距离
    //持续标记，直到找到终点或无路可走
    position nbr;
    int numOfNbrs = 4;
    position here = start;
    arrayQueue<position> q;
    do
    {//标记可达的位置
        for(int i = 0; i < numOfNbrs; i++)
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if(maze[nbr.row][nbr.col] == 0)
            {
                maze[nbr.row][nbr.col] = maze[here.row][here.col] + 1;
                q.push(nbr);
            }
            if(finish.row == nbr.row && finish.col == nbr.col)
                break;
        }
        if(finish.row == here.row && finish.col == here.col)
            break;//转去重构路径

        if(q.empty()) return false;

        here = q.front();
        q.pop();
    }while(true);
    //重构路径
    pathLength = maze[finish.row][finish.col] - 2;
    path = new position[pathLength];
    here = finish;
    for(int i = pathLength-1; i >= 0; i--)
    {
        for(int j = 0; j < numOfNbrs; j++)
        {
            nbr.row = here.row + offset[j].row;
            nbr.col = here.col + offset[j].col;
            if(maze[nbr.row][nbr.col] == i + 2)
                break;
        }
        path[i] = nbr;
        here = nbr;
    }
    return true;
}

int main()
{
    // 分配maze的空间
    // maze = new int*[9];
    // for(int i = 0; i < 9; i++)
    //     maze[i] = new int[9];
    make2dArray<int>(maze, size+2, size+2);
    for(int i = 0; i <= size+1; i++)
        for(int j = 0; j <= size + 1; j++)
            maze[i][j] = 0;
    // for(int i = 0; i <= size+1; i++)
    // {
    //     maze[0][i] = 1; maze[size+1][i] = 1;
    //     maze[i][0] = 1; maze[i][size + 1] = 1;
    // }

    // cout << maze[0][0];    
    //初始化迷宫障碍
    maze[1][3] = 1;
    
    maze[2][3] = 1;
    maze[2][4] = 1;

    maze[3][5] = 1;
    
    maze[4][4] = 1;
    maze[4][5] = 1;
    
    maze[5][1] = 1;
    maze[5][5] = 1;
    
    maze[6][1] = 1;
    maze[6][2] = 1;
    maze[6][3] = 1;
    
    maze[7][1] = 1;
    maze[7][2] = 1;
    maze[7][3] = 1;

    // for(int i = 0; i <= size+1; i++)
    //     for(int j = 0; j <= size + 1; j++)
    //     {
    //         cout << maze[i][j] << " ";
    //         if(((j+1) % 9 == 0)) cout << endl;

    //     }
    // output_2DArray<int>(maze, 9, 9);
    findPath();

    for(int i = 0; i < pathLength; i++)
    {
        cout << path[i] << " ";
    }
}
