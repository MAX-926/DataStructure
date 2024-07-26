//图元识别
#include"9-2.cpp"

struct position
{
    position(int r = 0, int c = 0):row(r), col(c){}
    int row;
    int col;
};

int size = 7;//二值图片的尺寸
int** pixel;//二值图片
position offset[4];
int numTag = 2;//最小的图元编号
arrayQueue<position> q;//用队列来处理随程序进行下去衍生的新待处理对象：要处理的一个个排好队！！

void classify(int, int);

void labelComponents()
{//找出二值图片中的所有图元并进行分类
    //为二值图像添加边框
    for(int i = 0; i < size + 1; i++)
    {
        pixel[0][i] = pixel[size+1][i] = 0;
        pixel[i][0] = pixel[i][size+1] = 0;
    }
    //设置偏移量表
    offset[0].row = 0; offset[0].col = 1;
    offset[1].row = 1; offset[1].col = 0;
    offset[2].row = 0; offset[2].col = -1;
    offset[3].row = -1; offset[3].col = 0;

    //扫描图片，为图元分类
    for(int i = 1; i <= size; i++)
        for(int j = 1; j <= size; j++)
        {
            if(pixel[i][j] == 1)
            {//分类
                classify(i, j);
                numTag = numTag+1;
            }
        }
}

void classify(int r, int c)
{//将与pos相邻的节点标记为numTag
    pixel[r][c] = numTag;
    position here(r, c);
    position nbr;
    int numOfNbrs = 4;
    do
    {
        for(int i = 0; i < numOfNbrs; i++)
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if(pixel[nbr.row][nbr.col] == 1)
            {
                pixel[nbr.row][nbr.col] = numTag;
                q.push(nbr);//之后需要检查nbr是否还有相邻的图元
            }
        }
        if(q.empty()) return;
        else
        {
            here = q.front();
            q.pop();
        }
    }while(true);
}

int main()
{
    make2dArray<int>(pixel, size + 2, size + 2);
    for(int i = 0; i <= size + 1; i++)
        for(int j = 0; j <= size + 1; j++)
            pixel[i][j] = 0;
    //初始化图元
    pixel[1][3] = 1;

    pixel[2][3] = 1;
    pixel[2][4] = 1;
    
    pixel[3][5] = 1;
    
    pixel[4][4] = 1;
    pixel[4][5] = 1;
    
    pixel[5][2] = 1;
    pixel[5][5] = 1;
    pixel[5][7] = 1;

    pixel[6][1] = 1;
    pixel[6][2] = 1;
    pixel[6][3] = 1;
    pixel[6][7] = 1;

    pixel[7][1] = 1;
    pixel[7][2] = 1;
    pixel[7][3] = 1;
    pixel[7][6] = 1;
    pixel[7][7] = 1;

    labelComponents();
    output_2DArray<int>(pixel, size + 2, size + 2);
}