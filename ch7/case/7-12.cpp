//lowerTriangularMatrix 行主列映射
//如果改为列映射，则需要确定列映射的映射函数（i，j -> index），即可完成set和get函数，对于output则只需循环打印每一列的第i个元素
#include<iostream>
#include"../../Tool.h"
using namespace std;

template<class T>
class lowerTriangularMatrix
{
    public:
        lowerTriangularMatrix(int theN = 10);
        lowerTriangularMatrix(const lowerTriangularMatrix<T> &ltm);
        ~lowerTriangularMatrix(){delete []element;}
        void set(int i, int j, const T& newValue);
        T get(int i, int j)const;
        void output(ostream& out)const;
    private:
        int n;
        T* element;
};

template<class T>
ostream& operator<<(ostream& out, const lowerTriangularMatrix<T> &ltm)
{
    ltm.output(out);
    return out;
}

template<class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int theN)
{
    if(theN < 1)
        throw illegalParameter("theN must be > 0");
    n = theN;
    element = new T[(1+n)*n/2];
}

template<class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(const lowerTriangularMatrix<T> &ltm)
{
    n = ltm.n;
    copy(ltm.element, ltm.element + (1+n)*n/2, element);
}

template<class T>
void lowerTriangularMatrix<T>::set(int i, int j, const T& newValue)
{
    if(i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if(i >= j)
        element[i*(i-1)/2+j-1] = newValue;
    else
        if(newValue != 0)
            throw illegalParameter("nonLowerTriangularMatrix elements must be zero");
}

template<class T>
T lowerTriangularMatrix<T>::get(int i, int j)const
{
    if(i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if(i >= j)
        return element[i*(i-1)/2 + j-1];
    else return 0;
}

template<class T>
void lowerTriangularMatrix<T>::output(ostream& out)const
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i >= j)
                out << element[i*(i-1)/2 + j-1] << " ";
            else out << 0 << " ";
            if(j % n == 0) out << endl;
        }
}

int main()
{
    lowerTriangularMatrix<int> ltm(3);
    ltm.set(1, 1, 1);
    ltm.set(2, 1, 2);
    ltm.set(2, 2, 3);
    ltm.set(3, 1, 4);
    ltm.set(3, 2, 5);
    ltm.set(3, 3, 6);
    cout << ltm;
    // ltm.set(2, 3, 6);
    cout << ltm.get(2, 3);
}