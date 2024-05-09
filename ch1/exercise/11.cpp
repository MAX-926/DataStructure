#include<iostream>
using namespace std;

template<class T>
int count(int value, T* ta, int size)
{
    if(size < 1) throw "size should > 1";
    int re = 0;
    for(int i = 0; i < size; i++)
        if(ta[i] == value) re++;
    return re;
}

int main()
{
    int a[] = {1, 1, 1, 4, 7, 4, 5, 0, 8, 9, 4, 2};
    int len = sizeof(a)/sizeof(*a);
    try{ cout << count<int>(0, a, 0);}
    catch(char* e)
    {
        cout << e << endl;
    }
}