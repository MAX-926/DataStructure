#include<iostream>
// using namespace std;

//[4, 3, 9, 7, 3] {2, 0, 4, 1, 3}

template<class T>
void rank(T a[], int n, int r[])
{
    int ranking = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            if(a[j] < a[i] && i != j)
                ranking++;
            else if(a[j] == a[i] && j < i)
                ranking++;
    r[i] = ranking;
    ranking = 0;
    }
}

template<class T>
void rankN(T a[], int n, int r[])
{
    for(int i = 0; i < n; i++)
        r[i] = 0;
    for(int i = 1; i < n; i++)
        for(int j = 0; j < i; j++)
            if(a[i] >= a[j]) r[i]++;
            else r[j]++;
}
// 1+2+3+4+5+...+n-1 = n*(n-1)/2

// int main()
// {
//     int a[] = {4, 3, 9, 3, 7};
//     int r[5] = {0};
//     // rank<int>(a, 5, r);
//     rankN(a, 5, r);
//     for(int i = 0; i < 5; i++)
//         std::cout << r[i] << " ";
// }