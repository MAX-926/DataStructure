#include"E:\thinking in C++\MyTool.h"
#include<iostream>
using namespace std;

// template<class T>
// class Storage
// {
//     public:
//         Storage():list(0), length(0), capacity(0){}
//         Storage(int initialCapacity):length(0), capacity(initialCapacity){list = new T[initialCapacity];}
//         ~Storage();
//         void insert(const T &element);
//     private:
//         T* list;
//         int length;
//         int capacity;
//         void inflate(int rate);
// };

// template<class T>
// void Storage<T>::insert(const T &element)
// {
//     if(length >= capacity-1) inflate(2);
//     for(int i = length; i)
// }

// template<class T>
// void Storage<T>::inflate(int rate)
// {

// }

template<class T>
void insert(T a[], int n, const T& x)
{
 int i;
    for(i = n-1; i >= 0, a[i] > x; i--)
        a[i+1] = a[i];
    a[i+1] = x;
    // n++;
}   

int main()
{
    int a[] = {1, 2, 3, 4, 5, 0};
    int len = sizeof(a)/sizeof(a[0]);
    insert<int>(a, len-1, 6);
    print_1D_array<int>(a, len);   
}