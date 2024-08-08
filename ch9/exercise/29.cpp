//使用栈重写labelComponents程序
//优缺点分析：
//从时间开销与空间开销两个角度：
//空间开销上：栈的占用空间小于队列（因为队列多了一个描述队尾位置的int型变量）
//时间开销上：大致相当
#include"../../ch8/case/8-4.cpp"//引入arrayStack
#include"../../Tool.h"

int** pixel;//指代二值图像
int size;//指代图像大小

struct position
{
    int row;
    int col;
    position(int theRow = 0, int theCol = 0):row(theRow), col(theCol){}
};

void welcome()
{
    cout << "Welcom!\nThis is a Primitive Recognition program\n"
         << "please input a binary\n";
}

void input()
{
    cout << "Enter image size:\n";
    cin >> size;
    //对size的合法性进行检查
    //创建二值图像的存储空间
    make2dArray<int>(pixel, size + 2, size + 2);
    cout << "Enter image:\n";
    for(int i = 1; i <= size; i++)
        for(int j = 1; j <= size; j++)
            cin >> pixel[i][j];
    cout << "image was created successfully! please wait.\n";
}

void labelComponentsWithStack()
{//对图像中的图元进行标记
    //初始化图片外框
    for(int i = 0; i <= size + 1; i++)
    {
        pixel[0][i] = pixel[size + 1][i] = 0;
        pixel[i][0] = pixel[i][size + 1] = 0;
    }
    //初始化偏移量表
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;
    offset[1].row = 1; offset[1].col = 0;
    offset[2].row = 0; offset[2].col = -1;
    offset[3].row = -1; offset[3].col = 0;
    int lastOption = 3;
    int numOfNbrs = 4;
    position nbr;
    arrayStack<position> s;

    int label = 1;
    for(int i = 1; i <= size; i++)
    //扫描每一个像素点，为属于同一类的像素标记相同数字
        for(int j = 1; j <= size; j++)
        {
            if(pixel[i][j] == 1)
            {//说明图元来自新的集合
                position here(i, j);
                pixel[here.row][here.col] = ++label;
                while(true)
                {
                    for(int opt = 0; opt <= lastOption; opt++ )
                    {
                        nbr.row = here.row + offset[opt].row;
                        nbr.col = here.col + offset[opt].col;
                        if(pixel[nbr.row][nbr.col] == 1)
                        {
                            pixel[nbr.row][nbr.col] = label;
                            s.push(nbr);
                        }
                    }
                    if(s.empty()) break;
                    here.row = s.top().row;
                    here.col = s.top().col;
                    s.pop();
                }
            }
        }
}

void output()
{
    // output_2DArray<int>(pixel, size + 2, size + 2);
    for(int i = 1; i <= size; i++)
        for(int j = 1; j <= size; j++)
        {
            cout << pixel[i][j] << " ";
            if(j % size == 0)
                cout << endl;
        }
}

// int main()
// {
//     welcome();
//     input();
//     labelComponentsWithStack();
//     output();
// }