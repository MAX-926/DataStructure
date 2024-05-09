#include<iostream>
using namespace std;

template<class T>
void fill(T value, T *ta, int size, int left, int right)
{
    if(left > right){cout << "Left is bigger than right!"; return;}
    if(left >= size || right >= size){cout << "Index out of range";return;}
    for(int i = left; i <= right; i++)
        ta[i] = value;
    return;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(a)/sizeof(*a);
    fill<int>(26, a, len, 0, len-1);
    for(int i = 0; i < len; i++)
        cout << a[i] << " ";
}