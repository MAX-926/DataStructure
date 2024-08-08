//程序在矩阵的两个定点之间寻找一条连通的路径

#include"ch8/case/8-4.cpp"
#include"Tool.h"
#include<iostream>

using namespace std;

struct position
{
    position(int theRow = 0, int theCol = 0):row(theRow), col(theCol){}
    int row;
    int col;
};

ostream& operator<<(ostream& out, const position& p)
{
    out << "(" << p.row << ',' << p.col << ')' << " ";
    return out;
}

int size = 10;
bool** maze;
position start(1, 1);
position finish(10, 10);
arrayStack<position> path;//用来存储路径

bool findARoute()
{//若找到路径则返回true，否则返回false
    if(start.row == finish.row && start.col == finish.col)
    {
        cout << "start and finish is at the same place!\n";
        return true;
    }
    //初始化迷宫外墙
    for(int i = 0; i <= size+1; i++ )
    {
        maze[0][i] = maze[size+1][i] = 1;
        maze[i][0] = maze[i][size+1] = 1;
    }
    //初始化偏移量表
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;
    offset[1].row = 1; offset[1].col = 0;
    offset[2].row = 0; offset[2].col = -1;
    offset[3].row = -1; offset[3].col = 0;

    maze[start.row][start.col] = 1;

    position here = start;

    int option = 0;
    int lastOption = 4;

    //寻找路径
    while(here.row != finish.row || here.col != finish.col)
    {
        position nbr;
        for(; option < lastOption; option++)
        {
            nbr.row = here.row + offset[option].row;
            nbr.col = here.col + offset[option].col;
            if(maze[nbr.row][nbr.col] == 0)
                break;
        }
        if(option < lastOption)
        {
            path.push(here);
            maze[nbr.row][nbr.col] = 1;
            here = nbr;
            option = 0;
        }
        else
        {//没有找到合适1的位置前进，需要回退
            if(path.empty()) return false;
            else
            {
                position next = path.top();
                path.pop();
                if(next.row == here.row)
                    option = next.col - here.col + 2;
                else
                    option = next.row - here.row + 3;
                here = next;
            }
        }
    }
    return true;
}

int main()
{
    make2dArray<bool>(maze, 12, 12);
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 12; j++)
            maze[i][j] = 0;
    //初始化迷宫矩阵
    maze[1][2] = 1;
    maze[1][3] = 1;
    maze[1][4] = 1;
    maze[1][5] = 1;
    maze[1][6] = 1;
    
    maze[2][6] = 1;
    maze[2][8] = 1;

    maze[3][4] = 1;
    maze[3][6] = 1;

    maze[4][2] = 1;
    maze[4][4] = 1;
    maze[4][6] = 1;
    maze[4][8] = 1;
    maze[4][9] = 1;

    maze[5][2] = 1;
    maze[5][4] = 1;
    maze[5][6] = 1;
    maze[5][8] = 1;

    maze[6][2] = 1;
    maze[6][3] = 1;
    maze[6][4] = 1;
    maze[6][6] = 1;
    maze[6][8] = 1;
    maze[6][10] = 1;

    maze[7][2] = 1;
    maze[7][6] = 1;
    maze[7][8] = 1;
    maze[7][10] = 1;

    maze[8][2] = 1;
    maze[8][4] = 1;
    maze[8][5] = 1;
    maze[8][6] = 1;
    maze[8][8] = 1;

    maze[9][1] = 1;
    maze[9][8] = 1;

    maze[10][5] = 1;
    maze[10][6] = 1;
    maze[10][7] = 1;
    maze[10][8] = 1;

    if(findARoute()) 
    {
        cout << "Find a route\n";
        while(!path.empty())
        {
            cout << path.top() << " ";
            path.pop();
        }
        cout << "output Path complete\n";
    }
    else
        cout << "there is no route for this maze\n";
}