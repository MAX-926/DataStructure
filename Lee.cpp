//寻找矩阵中两个定点之间的最小距离
#include"ch9/case/9-2.cpp"//arrayQueue
#include"ch8/case/8-4.cpp"
#include<iostream>

using namespace std;

struct position
{
    //坐标
    position(int x = 0 ,int y = 0):row(x), col(y){}
    int row;
    int col;
};

ostream& operator<<(ostream& out, const position& pos)
{
    out << "(" << pos.row << "," << pos.col << ")" << " ";
    return out;
}

int** maze;//迷阵
int size = 7;//迷阵的尺寸
position start(3, 2);
position finish(4, 6);
int pathLength;
position* path;

bool leePath()
{//若找到最短路径，则返回ture，否则返回false
    //1.距离标记

    if(finish.row == start.row && finish.col == start.col)
    {
        pathLength = 0;
        return true;
    }

    for(int i = 0; i <= size+1; i++)
    {
        maze[0][i] = maze[size+1][i] = 1;
        maze[i][0] = maze[i][size+1] = 1;
    }
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;
    offset[1].row = 1; offset[1].col = 0;
    offset[2].row = 0; offset[2].col = -1;
    offset[3].row = -1; offset[3].col = 0;
    
    position nbr, here;
    here = start;
    maze[start.row][start.col] = 2;
    const int numOfNbrs = 4;
    arrayQueue<position> q;//存储待处理节点
    // arrayStack<position> s;

    while(true)
    {//持续标记距离，直到标记终点或无路可走
        for(int i = 0; i < numOfNbrs; i++)
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if(maze[nbr.row][nbr.col] == 0)
            {
                maze[nbr.row][nbr.col] = maze[here.row][here.col] + 1;
                if(nbr.row == finish.row && nbr.col == finish.col)
                    break;
                q.push(nbr);//这个节点周围的节点需要进行标记，加入队列
            }
        }
        if(finish.row == nbr.row && finish.col == nbr.col)
            break;
        if(q.empty()) return false;//代表未到达终点且无路可走
        // if(s.empty()) return false;//代表未到达终点且无路可走

        here = q.front();
        // here = s.top();
        q.pop();
        // s.pop();
    }
    //2.路径标记
    pathLength = maze[finish.row][finish.col] - 2;
    path = new position[pathLength];
    here = finish;
    for(int i = pathLength - 1; i >= 0 ; i--)
    {
        path[i] = here;
        for(int j = 0; j < numOfNbrs; j++)
        {
            nbr.row = here.row + offset[j].row;
            nbr.col = here.col + offset[j].col;
            if(maze[nbr.row][nbr.col] == i + 2)
                break;
        }
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
    leePath();

    for(int i = 0; i < pathLength; i++)
    {
        cout << path[i] << " ";
    }
}