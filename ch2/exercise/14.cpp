//数组a[0:8] = {g, h, i, f, c, a, d, b, e}
//实现原地重排

#include"../../../MyTool.h"
#include"9.cpp"

template<class T>
void sort_in_place(T a[], int n, int r[])
{
    for(int i = 0; i < n; i++)
        while(r[i] != i)
        {
             std::swap(a[i], a[r[i]]);
             std::swap(r[i], r[r[i]]);
        }
}

int main()
{
    char  a[9] = {'g', 'h', 'i', 'f', 'c', 'a', 'd', 'b', 'e'};
    // 6, 7, 8, 5, 2, 0, 3, 1, 4
    int r[GETSIZE(a)];
    rank<char>(a, GETSIZE(a), r);
    sort_in_place<char>(a, GETSIZE(a), r);
    print_1D_array_incpp<char>(a, GETSIZE(a));
}
// g,  h, i,  f, c,  a, d, b, e
// 6, 7, 8, 5, 2, 0, 3, 1, 4

//d, h, i, f, c, a, g, b, e
//3, 7, 8, 5, 2, 0, 6, 1, 4

//f, h, i, d, c, a, g, b, e
//5, 7, 8, 3, 2, 0, 6, 1, 4

//a, h, i, d, c, f, g, b, e
//0, 7, 8, 3, 2, 5, 6, 1, 4

//a, b, i, d, c, f, g, h, e
//0, 1, 8, 3, 2, 5, 6, 7, 4

//a, b, e, d, c, f, g, h, i
//0, 1, 4, 3, 2, 5, 6, 7, 8

//a, b, c, d, e, f, g, h, i
//0, 1, 2, 3, 4, 5, 6, 7, 8