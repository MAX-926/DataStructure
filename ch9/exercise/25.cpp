//寻找矩阵中两定点之间的最短距离
#ifndef FINDPATH_H
#define FINDPATH_H

#include"../case/9-2.cpp"
#include<iostream>
#include"../../Tool.h"

using namespace std;

struct position
{
    int row;
    int col;
    position(int theRow = 0, int theCol = 0):row(theRow), col(theCol){}
};

int size = 7;//表示迷阵尺寸
int** maze;//表示迷阵所在的存储空间
int pathLength;
position* path;


ostream& operator<<(ostream& out, const position& pos)
{
    out << "(" << pos.row << ", " << pos.col << ")" << " ";
    return out;
}

position start(1, 4);
position finish(2, 2);

bool findPath()
{
    if(start.row == finish.row && start.col == finish.col)
    {
        pathLength = 0;
        return true;
    }

    for(int i = 0; i <= size + 1; i++)
    {
        maze[0][i] = maze[size + 1][i] = 1;
        maze[i][0] = maze[i][size + 1] = 1;
    }
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;
    offset[1].row = 1; offset[1].col = 0;
    offset[2].row = 0; offset[2].col = -1;
    offset[3].row = -1; offset[3].col = 0;

    maze[start.row][start.col] = 2;

    arrayQueue<position> q;
    int numOfNbrs = 4;
    position here = start;
    position nbr;
    while(true)
    {
        for(int opt = 0; opt < numOfNbrs; opt++)
        {
            nbr.row = here.row + offset[opt].row;
            nbr.col = here.col + offset[opt].col;
            if(maze[nbr.row][nbr.col] == 0)
            {
                maze[nbr.row][nbr.col] = maze[here.row][here.col] + 1;
                if(nbr.row == finish.row && nbr.col == finish.col)
                    break;
                q.push(nbr);
            }
        }
        if(nbr.row == finish.row && nbr.col == finish.col)
            break;
        if(q.empty()) return false;
        here = q.front();
        q.pop();
    }
    //路径标记
    here = finish;
    pathLength = maze[finish.row][finish.col] - 2;
    path = new position[pathLength];
    for(int i = pathLength - 1; i >= 0; i--)
    {
        for(int j = 0; j <=  numOfNbrs; j++)
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

#endif //FINDPATH_H
// int main()
// {
//     // 分配maze的空间
//     // maze = new int*[9];
//     // for(int i = 0; i < 9; i++)
//     //     maze[i] = new int[9];
//     make2dArray<int>(maze, size+2, size+2);
//     for(int i = 0; i <= size+1; i++)
//         for(int j = 0; j <= size + 1; j++)
//             maze[i][j] = 0;
//     // for(int i = 0; i <= size+1; i++)
//     // {
//     //     maze[0][i] = 1; maze[size+1][i] = 1;
//     //     maze[i][0] = 1; maze[i][size + 1] = 1;
//     // }

//     // cout << maze[0][0];    
//     //初始化迷宫障碍
//     maze[1][3] = 1;
    
//     maze[2][3] = 1;
//     maze[2][4] = 1;

//     maze[3][5] = 1;
    
//     maze[4][4] = 1;
//     maze[4][5] = 1;
    
//     maze[5][1] = 1;
//     maze[5][5] = 1;
    
//     maze[6][1] = 1;
//     maze[6][2] = 1;
//     maze[6][3] = 1;
    
//     maze[7][1] = 1;
//     maze[7][2] = 1;
//     maze[7][3] = 1;

//     // for(int i = 0; i <= size+1; i++)
//     //     for(int j = 0; j <= size + 1; j++)
//     //     {
//     //         cout << maze[i][j] << " ";
//     //         if(((j+1) % 9 == 0)) cout << endl;

//     //     }
//     // output_2DArray<int>(maze, 9, 9);
//     leePath();

//     for(int i = 0; i < pathLength; i++)
//     {
//         cout << path[i] << " ";
//     }
// }