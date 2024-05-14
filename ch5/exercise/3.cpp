//changeLength2D
#include"../../MyTool.h"
#include<algorithm>
template<class T>
void myChangeLength2D(T ** &a, int numberOfRows, int numberOfColumns, int newRows, int newColumns)
{
    int rEle = numberOfRows > newRows?newRows:numberOfRows;
    int cEle = numberOfColumns > newColumns?newColumns:numberOfColumns;
    T ** tmp = new T*[rEle];
    for(int i =0; i < rEle; i++)
    {
        tmp[i] = new T[cEle];
        std::copy(a[i], &a[i][cEle], tmp[i]);
        delete []a[i];
    }
    delete a;
    a = tmp;
}

template<class T>
void changeLength2D(T ** &a, int oldRows, int oldColumns, int copyRows, int copyColumns, int newRows, int newColumns)
{
    //参数检查
    if(copyRows > newRows || copyColumns > newColumns)
    throw IllegalParameter("new dimensions are too small");
    if(copyRows > oldRows || copyColumns > oldColumns)
    throw IllegalParameter("copy dimensions are too big");
    //create new 2D array
    T ** tmp = new T*[newRows];//                              O(1)
    // for(int i = 0; i < newRows; i++) 抽风
    //     tmp = new T*[newRows]; 抽风
    for(int i = 0; i < newRows; i++)//                              O(newRows+1)
        tmp[i] = new T[newColumns];//                           O(newColumns*newRows)
    //copy element
    for(int i = 0; i < copyRows; i++)//                              O(copyRows+1)
    {
        std::copy(a[i], a[i]+copyColumns, tmp[i]);//              O(copyColumns*copyRows)
        delete [] a[i];//                                                  O(copyOfRows)
    }
    //清除余下的oldRows
    for(int i = copyRows; i < oldRows; i++)//                       O(oldRows-copyRows+1)
        delete [] a[i];//                                                   O(oldRows-copyRows)
    delete []a;//                                                           O(1)
    a = tmp;//                                                             O(1)
}


int main()
{
    int **a, **b;
    create2DArray<int>(a, 2, 3);
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[1][0] = 4;
    a[1][1] = 5;
    a[1][2] = 6;
    changeLength2D<int>(a, 2, 3, 2, 2, 2, 5);
    // a[0][3] = 26;
    // a[0][4] = 26;
    // a[1][3] = 26;
    // a[1][4] = 26;
    // a[0][5] = 3;
    // std::cout << a[0][5];
    print_2D_array<int>(a, 2, 5);
}