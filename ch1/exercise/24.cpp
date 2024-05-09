//编写一个递归模版函数， 确定元素x是否属于数组a[0:n-1]。
#include<iostream>
using namespace std;

template<class T>
bool find(T x, T ta[], int len)
{
    static int n = 0;
    //basic part
    if(n == len) return false;
    else
    {
    if(ta[n] == x) return true;
    else 
    {
        n++;
        find(x, ta, len);
    }
    }
}

template<class T>
void showResult(bool fp(T, T[], int), T x, T ta[], int len)
{
    if(fp(x, ta, len)) 
    {
        // cout << "x is in a[0:" << len << "]" << endl;
        // cout << "a[0:" << len << "] = ";
        // for(int i = 0; i < len; i++)
        //     cout << ta[i] << " ";
        cout << x << " is in a[0:" << len << "]" << endl;
        cout << "a[0:" << len << "] = {";
        for(int i = 0; i < len; i++)
            if(i == len-1) cout << ta[i];
            else cout << ta[i] << ", ";
        cout << "}";
    }
    else 
    {
        cout << x << " is not in a[0:" << len << "]" << endl;
        cout << "a[0:" << len << "] = {";
        for(int i = 0; i < len; i++)
            if(i == len-1) cout << ta[i];
            else cout << ta[i] << ", ";
        cout << "}";
    }
}

template<class T>
bool sentence(T a[], int n, const T &x)
{
    bool re = false;
    for(int i = 0; (i < n) && (a[i] == x? re = true : 1); i++);
    return re;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    // cout << find<int>(0, arr, 6);
    cout << sentence<int>(arr, sizeof(arr)/sizeof(*arr), 26);
    // showResult<int>(find, 5, arr, 6);
}
