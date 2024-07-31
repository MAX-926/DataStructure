//重复的电路布线
//重用grid数组

void refresh();
void outputCircuit(int**, int, int);

//设计一个完整的电路布线程序
#include"../../Tool.h"
#include"../case/9-2.cpp"
struct position
{
    int row;
    int col;
    position(int theRow = 0, int theCol = 0):row(theRow), col(theCol){}
};

ostream& operator<<(ostream& out, const position& pos)
{
    out << "(" << pos.row << "," << pos.col << ")";
    return out;
}

int size;//电路板尺寸
int** maze;
int pathLength;
position* path = nullptr;
char selection;

bool found = false;

position start;
position finish;

void welcome()
{//输出欢迎界面
    cout << "WELCOM\n";
    cout << "This is a program for wire-plan\n";
}

void input()
{
    cout << "Enter circuit size:\n";
    cin >> size;
    if(size < 1)
        throw illegalParameter("size must be > 1");
    make2dArray<int>(maze, size + 2, size + 2);
    cout << "Enter the circuit, from (1, 1) to (size, size)\n";
    for(int i = 1; i <= size; i++)
        for(int j = 1; j <= size; j++)
            cin >> maze[i][j];
    //对输入的合法性做检查
    int x, y;
    cout << "Enter start point:\n";
    cin >> x >> y;
    //对输入的合法性做检查
    start = position(x, y);
    cout << "Enter finish point\n";
    cin >> x >> y;
    //对输入的合法性做检查
    finish = position(x, y);
}

bool findPath()
{
    if(start.row == finish.row && start.col == finish.col)
    {
        pathLength = 0;
        if(pathLength > 1) delete[] path;
        path = nullptr;
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

void outputPath()
{//输出结果
    if(!found)
    {
        cout << "There is no path between point (" << start.row << ',' << start.col << ")" << " and point " << "(" << finish.row << ',' << finish.col << "), please try again\n";
        selection = 'N';//重新输入所有参数
    }
    else
    {//找到路径，输出它们
        if(pathLength == 0)
            cout << "start point is finsih point\n";
        else
            for(int i = 0; i < pathLength; i++)
                cout << path[i] << " ";
        cout << "path output complete\n";
        cout << "Do you want to keep wiring this circuit? Y/N\n";
        cin >> selection;
        if(selection == 'y') selection = 'Y';
        if(selection == 'n') selection = 'N';
        switch(selection)
        {
            case 'Y':
                refresh();
                //展示maze情况
                // output_2DArray<int>(maze, size + 2, size + 2);                
                outputCircuit(maze, size, size);
                break;
            case 'N':
                cout << "Exit now";
                break;
            default:
                cout << "Wrong input, exit now\n";
                selection = 'N';
        }
    }
}

void refresh()
{//将数组清零，然后对上一轮搜索得到的路径在电路板上进行标记
    if(found)
    {
        // for(int i = 1; i <= size; i++)
        //     for(int j = 1; j <= size; j++)
        //         maze[i][j] = 0;
        // for(int i = 0; i < pathLength; i++)
        //     maze[path[i].row][path[i].col] = 1;
        position nbr, here = start;
        int numOfNbrs = 4;
        arrayQueue<position> q;
        position offset[4];
        offset[0].row = 0; offset[0].col = 1;
        offset[1].row = 1; offset[1].col = 0;
        offset[2].row = 0; offset[2].col = -1;
        offset[3].row = -1; offset[3].col = 0;
        while(true)
        {
            for(int i = 0; i < numOfNbrs; i++)
            {
                nbr.row = here.row + offset[i].row;
                nbr.col = here.col + offset[i].col;
                if(maze[nbr.row][nbr.col] > 1)
                {
                    maze[nbr.row][nbr.col] = 0;
                    q.push(nbr);
                }
            }
            if(q.empty()) break;
            here = q.front();
            q.pop();
        }
        //将路径上的坐标封锁
        maze[finish.row][finish.col] = 1;
        for(int i = pathLength - 1; i >= 0; i--)
        {
            maze[path[i].row][path[i].col] = 1;
        }
        if(path != nullptr) delete[] path;
    }
}

int main()
{
    //欢迎函数，只显示一次
    welcome();
    //输入迷阵
    input();
    //输出结果
    while(true)
    {
        found = findPath();
        outputPath();
        if(selection == 'Y')
        {
            int x, y;
            cout << "Enter start point:\n";
            cin >> x >> y;
            //对输入的合法性做检查
            start = position(x, y);
            cout << "Enter finish point\n";
            cin >> x >> y;
            //对输入的合法性做检查
            finish = position(x, y);
        }
        else
            break;
    }
    cout << "\n GoodBye!\n";
}

void outputCircuit(int** circuit, int sizeR, int sizeC)
{
    for(int i = 1; i <= sizeR; i++)
        for(int j = 1; j <= sizeC; j++)
        {
            cout << circuit[i][j] << " ";
            if(j % size == 0) cout << endl;
        }
}