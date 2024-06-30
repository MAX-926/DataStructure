//tridiagonalMatrix
#include<iostream>
#include"../../Tool.h"

using namespace std;

template<class T>
class tridiagonalMatrix
{
    public:
        tridiagonalMatrix(int theN = 10);
        tridiagonalMatrix(const tridiagonalMatrix<T> &tdm);
        ~tridiagonalMatrix();
        T get(int i, int j)const;
        void set(int i, int j, const T& newValue);
        void output(ostream& out)const;
    private:
        int n;
        T* i_equal_to_j;
        T* i_minus_j_less_than_zero;
        T* i_minus_j_bigger_than_zero;
};

template<class T>
void tridiagonalMatrix<T>::output(ostream& out)const
{
    out << "output tridiagonalMatrix:\n";
    //iterE、iterB、iterL分别为i_equal_to_j、i_minus_j_bigger_than_zero、i_minus_j_less_than_zero的迭代器
    int iterE = 0, iterB = 0, iterL = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i == j)
                out << i_equal_to_j[iterE++] << " ";
            else if(i - j == 1)
                out << i_minus_j_bigger_than_zero[iterB++] << " ";
            else if(i - j == -1)
                out << i_minus_j_less_than_zero[iterL++] << " ";
            else
                out << 0 << " ";
            if(j % n == 0)
                out << endl;
        }
}

template<class T>
ostream& operator<<(ostream& out, const tridiagonalMatrix<T> &tdm)
{
    tdm.output(out);
    return out;
}

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(int theN)
{
    if(theN <= 1)
        throw illegalParameter("theN must be > 1");
    n = theN;
    i_equal_to_j = new T[n];
    i_minus_j_less_than_zero = new T[n-1];
    i_minus_j_bigger_than_zero = new T[n-1];
}

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(const tridiagonalMatrix<T> &tdm)
{
    n = tdm.n;
    copy(tdm.i_equal_to_j, tdm.i_equal_to_j + n-1, i_equal_to_j);
    copy(tdm.i_minus_j_less_than_zero, tdm.i_minus_j_less_than_zero + n-1, i_minus_j_less_than_zero);
    copy(tdm.i_minus_j_bigger_than_zero, tdm.i_minus_j_bigger_than_zero + n-1, i_minus_j_bigger_than_zero);
}

template<class T>
tridiagonalMatrix<T>::~tridiagonalMatrix()
{
    delete []i_equal_to_j;
    delete []i_minus_j_bigger_than_zero;
    delete []i_minus_j_less_than_zero;
}

template<class T>
T tridiagonalMatrix<T>::get(int i, int j)const
{
    if(i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if(i == j)
        return i_equal_to_j[i-1];
    else if(i - j == 1)
        return i_minus_j_bigger_than_zero[i-2];
    else if(i - j == -1)
        return i_minus_j_less_than_zero[i-1];
    else
        return 0;
}

template<class T>
void tridiagonalMatrix<T>::set(int i, int j, const T& newValue)
{
    if(i < 1 || j < 1 || i  > n || j > n)
        throw matrixIndexOutOfBounds();
    if(i == j)
        i_equal_to_j[i-1] = newValue;
    else if(i - j == 1)
        i_minus_j_bigger_than_zero[i-2] = newValue;
    else if(i - j == -1)
        i_minus_j_less_than_zero[i-1] = newValue;
    else if(newValue != 0)
        throw illegalParameter("nontridiagonal elements must be 0");
    return;
}

int main()
{
    tridiagonalMatrix<int> tdm(4);
    tdm.set(1, 1, 2);
    tdm.set(2, 2, 1);
    tdm.set(3, 3, 2);
    tdm.set(4, 4, 0);

    tdm.set(1, 2, 1);
    tdm.set(2, 3, 3);
    tdm.set(3, 4, 7);

    tdm.set(2, 1, 3);
    tdm.set(3, 2, 5);
    tdm.set(4, 3, 9);

    cout << tdm;
}