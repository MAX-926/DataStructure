#include<iostream>

template<class T>
bool is_sorted(T* ta, int size)
{
    for(int i = 0; i < size; i++)
        for(int j = i+1; j < size; j++)
            if(ta[i] > ta[j]) return false;
    return true;
}

int main()
{
    int a[] = {300, 1, 2, 3, 4, 4};
    int len = sizeof(a)/sizeof(*a);
    std::cout << is_sorted(a, len);
    return 0;
}