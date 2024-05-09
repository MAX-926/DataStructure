#include<iostream>
#include<algorithm>
#include<iterator>
using namespace std;

template<class T>
void permutation(T list[], int k, int m)
{
    sort(list, list+m+1);
    do
    {
        copy(list, list+m+1, ostream_iterator<T>(cout, " "));
        cout << endl;
    }while(next_permutation(list, list+m+1));
}

int main()
{
    int list[] = {5, 4, 3, 2, 1};
    permutation(list, 0 ,4);
}