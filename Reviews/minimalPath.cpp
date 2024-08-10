#include"../ch9/case/9-2.cpp"

struct position
{
    int row;
    int col;
    position(int theRow = 0, int theCol = 0):row(theRow), col(theCol){}
    bool operator==(const position rightValue)const
    {
        return (row == rightValue.row && col == rightValue.col);
    }

};

int** grid;
int size = 7;

int pathLength;
position* path;

position start(3, 2);    
position finish(4, 6);

ostream& operator<<(ostream& out, const position& thePos)
{
    out << '(' << thePos.row << ',' << thePos.col << ')' << " ";
    return out;
}
//寻找最短路径

bool findPath()
{//如果找到，返回true，否则返回false
    for(int i = 0; i <= size + 1; i++)
    {
        grid[0][i] = grid[size + 1][i] = 1;
        grid[i][0] = grid[i][size + 1] = 1;
    }
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;
    offset[1].row = 1; offset[1].col = 0;
    offset[2].row = 0; offset[2].col = -1;
    offset[3].row = -1; offset[3].col = 0;

    position here = start;
    grid[here.row][here.col] = 2;
    position nbr;
    int numOfNbrs = 4;
    if(here == finish)
    {
        pathLength = 0;
        return true;
    }
    arrayQueue<position> q;

    while(true)
    {//持续标价距离，直到抵达终点或无路可走
        for(int i = 0; i < numOfNbrs; i++)
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if(grid[nbr.row][nbr.col] == 0)
            {
                grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
                q.push(nbr);
            }
            if(nbr == finish) break;
        }
        if(nbr == finish) break;
        if(q.empty()) return false;
        here = q.front();
        q.pop();
    }
    //重构路径
    here = finish;
    pathLength = grid[finish.row][finish.col] - 2;
    path = new position[pathLength];
    for(int j = pathLength - 1; j >= 0; j--)
    {
        for(int i = 0; i < numOfNbrs; i++)
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if(grid[nbr.row][nbr.col] == j + 2)
                break;
        }
        path[j] = nbr;
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