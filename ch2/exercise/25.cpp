//确定函数permutations(见程序1-32)执行了多少次交换操作？
#include"../../../MyTool.h"
#include<iterator>
using namespace std;

template<class T>
void permutations(T list[], int k, int m)
{
    
        if(k == m)
        {
            copy(list, list+m+1, ostream_iterator<T>(cout, ""));
            cout << endl;
        }
        else
        {
            for(int i = k; i <= m; i++)
            {
                swap(list[k], list[i]);
                permutations(list, k+1, m );
                swap(list[k], list[i]);
            }
        }
}

int main()
{
    char a[] = {'a', 'b', 'c'};
    permutations<char>(a, 0, GETSIZE(a)-1);
}