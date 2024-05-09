#include<iostream>

template<class T>
int mismatch(T* ta, T* tb, int size)
{
    for(int i = 0; i < size; i++)
        if(ta[i] != tb[i]) return i;
    std::cout << "ta = tb\n";
    return 0;
}

int main()
{
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    int len = sizeof(a)/sizeof(*a);
    std::cout << mismatch<int>(a, b, len);
    return 0;
}