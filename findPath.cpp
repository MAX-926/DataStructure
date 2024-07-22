#include"ch8/case/8-4.cpp"
#include<iostream>
#include<fstream>


struct position
{
    position(int theX = 0, int theY = 0):x(theX), y(theY){}
    int x;
    int y;
};
//position类型的输出函数
ostream& operator<<(ostream& out, const struct position& thePos)
{
    out << "(" << thePos.x << "," << thePos.y << ")" << " ";
    return out;
}

class ratInMaze
{
    public:
        ratInMaze(bool** &theMaze, int theDimension):maze(theMaze), dimension(theDimension), size(theDimension-2){path = new arrayStack<position>;}
        void outputPath();
    private:
        bool findPath();//寻找路径
        bool** maze;//二维矩阵
        int dimension;//布尔矩阵的维度
        int size;//迷宫大小
        arrayStack<position>* path;
};

bool ratInMaze::findPath()
{//寻找路径，找到则返回true，未找到则返回false
//从（1， 1）移动到（size， size）
    //初始化行为
    //初始化迷宫围墙
    for(int i = 0; i < dimension; i++)
    {
        maze[0][i] = maze[size+1][i] = 1;
        maze[i][0] = maze[i][size+1] = 1;
    }
    //设置偏移量表
    position offset[4];//0-R, 1-D, 2-L, 3-U
    offset[0].x = 0, offset[0].y = 1;
    offset[1].x = 1, offset[1].y = 0;
    offset[2].x = 0, offset[2].y = -1;
    offset[3].x = -1, offset[3].y = 0;
    //初始化当前位置
    position here;
    here.x = 1;
    here.y = 1;
    //在当前位置放入障碍物，以免重走老路
    maze[1][1] = 1;
    //搜索路径：深度优先
    int option = 0;//只需要while循环第一次执行时option为0，所以定义在while循环前
    const int lastOption = 3;
    while(here.x != size || here.y != size)//未抵达终点时，持续寻找
    {
        //寻找移动方向
        int r,c;
        for(;option <= lastOption; option++)
        {
            r = here.x + offset[option].x;
            c = here.y + offset[option].y;
            if(maze[r][c] != 1) break;
        }
        if(option <= lastOption)
        {
            path->push(here);
            here.x = r;
            here.y = c;
            maze[r][c] = 1;
            option = 0;
        }
        else//if(option > lastOption)
        {//找不到相邻可达的位置，回退
            if(path->empty()) return false;
            position next = path->top();
            path->pop();
            if(next.x == here.x)
                option = next.x - here.x + 2;
            else
                option = next.x - here.x + 3;
            here = next;//移动到next
        }
    }
    return true;
}

void ratInMaze::outputPath()
{
    if(findPath())
    {
        while(!path->empty())
        {
            cout << path->top();
            path->pop();
        }
    }
}
int main()
{
    ofstream out("maze.txt");
    //迷宫为10*10

    // game.welcome();

    bool** maze;
    make2dArray<bool>(maze, 12, 12);

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

    ratInMaze game(maze, 12);
    game.outputPath();
   
    out.close();
}