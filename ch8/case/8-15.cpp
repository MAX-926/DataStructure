//maze_mouse
//自顶向下分析、模块化地设计程序
//程序有四个模块
//1.打印提示信息
//2.输入迷宫(即布尔矩阵)
//3.寻找路径(路径是一个序列)
//4.返回路径

/*
程序的形式：
              Root
welcome intput findPath outputPath

//欢迎函数welcome
//输入函数inputMaze
//寻找路径函数findPath
//输出函数outputPath
void main()
{
    welcome();
    inputMaze();
    if(findPath())
        outputPath();
    else
        cout << "No path " << endl;
}
*/

/*
寻找路径函数的第一个版本（伪码表示）：
bool findPath()
{
    寻找迷宫中到达出口的一条路径
    if(找到路径) return true
    else return false
}
*/

/*
寻找路径函数的第二个版本（伪码表示）：
bool findPath()
{//寻找一条从入口（1， 1）到出口（m， m）的路径
//初始化迷宫四周的围墙
//初始化变量，已记录我们在迷宫的当前位置
here.row = 1;
here.col = 1;

maze[1][1] = 1;//防止回到入口

//寻找通向出口的路径
while(不是出口)do
{
    寻找可以移动的下一步
    if(下一步存在)
    {
        把下一步位置压进路径栈；
        //走到下一步，然后在这一步加入障碍物
        here = neighbor;
        maze[here.row][here.col] = 1;
    }
    else
    {
    //不能继续往下走，退回
    if(路径为空) return false;
    返回的位置在路径栈的顶部；
    }
    return true;
}
*/

//这个程序的精华：
//对程序的看法从宏观到微观：
//将程序分解为四个独立的模块：1.欢迎模块 2.输入模块 3.寻路模块 4.输出模块
//对findPath函数的设计概括到细节：进行了三个版本的细化
//从函数的输入输出进行分析，尔后对需要用到的工具：建立迷宫外墙以统一方向寻找的程序、建立偏移量表，以表示移动的方向、建立路径栈以保存经过的点、设置blocks以标记走过的路
//万事俱备后再进行寻路（寻路就是找一条路径，使得当前坐标变换到目的坐标）

//细化的寻找路径的C++代码
#include"8-4.cpp"
#include<iostream>
#include"../../Tool.h"
#include<fstream>

using namespace std;

struct position
{
    public:
        position(int theRow = 1, int theCol = 1):row(theRow), col(theCol){}
        position(const position& thePos){row = thePos.row; col = thePos.col;}
        ~position(){}
        int row;
        int col;
        // position operator+(const position& thePos)
        // {
        //     return position(row+thePos.row, col+thePos.col);            
        // }
        // position& operator+=(const position& thePos)
        // {
        //     row += thePos.row;
        //     col += thePos.col;
        //     return *this;
        // }
};

ostream& operator<<(ostream& out, const struct position& thePos)
{
    out << "(" << thePos.row << ", " << thePos.col << ")";
    return out;
}

class ratInMaze
{
    public:
        ratInMaze(int theSize):size(theSize), maze(nullptr)
        {
            path = new arrayStack<position>;
        }
        void welcome();
        void input(bool**&);
        void outputPath();
    private:
        bool findPath();
        int size;
        bool** maze;
        arrayStack<position>* path;
        arrayStack<position> reverser;
};

//Module 1:Welcome
void ratInMaze::welcome()
{//输出欢迎信息
    cout << "\033[5mWelcome To\n"
         << "RAT IN MAZE\n"
         << "Joe Bloe, 2000\n";
    return;
}

void ratInMaze::input(bool**& theMaze)
{
    if(theMaze == nullptr)
    {
        cout << "Wrong input on maze!\n";
        return;
    }
    maze = theMaze;
    return;
}

bool ratInMaze::findPath()
{//寻找一条从入口（1， 1）到出口（size， size）的路径
//如果找到返回true，否则返回false

    // arrayStack<position>* path = new arrayStack<position>;//这导致了路径并未存储在对象的path成员里
    //初始化当前位置
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;//右
    offset[1].row = 1; offset[1].col = 0;//下
    offset[2].row = 0; offset[2].col = -1;//左
    offset[3].row = -1; offset[3].col = 0;//上
    //为迷宫外墙设置障碍物
    for(int i = 0; i <= size+1; i++)
    {
        maze[0][i] = maze[size+1][i] = 1;//底部和顶部
        maze[i][0] = maze[i][size+1] = 1;//左和右
    }
    //在当前位置放入障碍物
    position here;
    // here.row = 1;
    // here.col = 1;
    maze[1][1] = 1;//防止回到路口
    int option = 0;//下一步
    int lastOption = 3;
    //寻找通向出口的路径
    while(here.row != size || here.col != size)//比使用&&更高效，因为不在终点时，大体上不会总对两个条件都进行检验
    {
        //移动
        for(int i = option; i <= lastOption; i++)
        {//没有到达出口
            //找到要移动的相邻的一步
            int r, c;
            while(option <= lastOption)
            {
                r = here.row + offset[option].row;
                c = here.col + offset[option].col;
                if(maze[r][c] == 0) break;
                option++;
            }
            //相邻的一步是否找到
            if(option <= lastOption)
            {//移到maze[r][c]
                path->push(here);
                here.row = r;
                here.col = c;
                maze[r][c] = 1;
                option = 0;
            }
            else
            {//没有相邻位置可走，返回
                if(path->empty()) return false;
                position next = path->top();
                path->pop();
                if(next.row == here.row)
                    option = 2 + next.col - here.col;
                else
                    option = 3 + next.col - here.col;
                here = next;
            }
        }   
    }
    return true;
}

void ratInMaze::outputPath()
{
    if(findPath())
    {
        cout << "find a path!\n";
        while(!path->empty())
        {
            reverser.push(path->top());
            path->pop();
        }
        while(!reverser.empty())
        {
            cout << reverser.top();
            cout << "-->";
            reverser.pop();
        }
        cout << "(" << size << ", " << size << ")";
    }
    else cout << "No path\n";
}

int main()
{
    ofstream out("maze.txt");
    //迷宫为10*10
    ratInMaze game(10);

    game.welcome();

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

    game.input(maze);

    game.outputPath();
   
    out.close();
}