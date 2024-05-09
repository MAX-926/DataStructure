//copy(start, end, to)
#include<iostream>
#include<iterator>
using namespace std;

template<class T>
bool copy(T* start, T* end, T* to)
{
    for(int i = 0; i < end-start; i++)
        to[i] = start[i];
    return true;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    int* ip1, *ip2;
    ip1 = ip2 = NULL;
    ip1 = new int[5];
    copy<int>(a, a+5, ip1);
    for(int i = 0; i < 5; i++)
        cout << ip1[i] << " ";
    return 0;
}