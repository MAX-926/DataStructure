#include<iostream>
using namespace std;
template<class T>
T* changeLength1D(T* &x, int oldLength, int newLength)
{
    if(oldLength == newLength) return 0;
    T* na = new T[newLength];
    for(int i = 0; i < (oldLength > newLength?newLength:oldLength); i++)
        na[i] = x[i];
    delete []x;
    return na;
}

int main()
{
    int* ip = new int[9];
    for(int i = 1; i < 10; i++)
        ip[i-1] = i;
    int* nip = changeLength1D(ip, 9, 12);
    for(int i = 0; i < 12; i++)
        cout << nip[i] << " ";
}