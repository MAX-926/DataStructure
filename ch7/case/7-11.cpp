//tridiagonalMatrix
//用待定系数法解决映射函数：y = m*i + n*j + c
#include<iostream>
#include<string.h>
#include"../../Tool.h"
#include"7-2.cpp"
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
        //输出
        void output(ostream& out)const;
        //加
        tridiagonalMatrix<T> operator+(const tridiagonalMatrix<T> &tdm)const;
        //减
        tridiagonalMatrix<T> operator-(const tridiagonalMatrix<T> &tdm)const;
        //乘
        matrix<T> operator*(const tridiagonalMatrix<T> &tdm)const;
        //矩阵转置
        tridiagonalMatrix<T> transpose()const;
    private:
        int n;
        T* element;
        // T* i_equal_to_j;
        // T* i_minus_j_less_than_zero;
        // T* i_minus_j_bigger_than_zero;
};

template<class T>
void tridiagonalMatrix<T>::output(ostream& out)const//O(n^2)
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i == j)
                out << element[n+i-2] << " ";
            else if(i - j == 1)
                out << element[-i+2*j] << " ";
            else if(i - j == -1)
                out << element[2*n-1+2*i-j] << " ";//
            else
                out << 0 << " ";
            if(j % n == 0)
                out << endl;
        }
}

template<class T>
ostream& operator<<(ostream& out, const tridiagonalMatrix<T> &tdm)//O(n^2)
{
    tdm.output(out);
    return out;
}

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(int theN)//O(1) or O(3n-2)
{
    if(theN <= 1)//O(1)
        throw illegalParameter("theN must be > 1");
    n = theN;
    element = new T[n + 2*(n-1)];//O(1) or O(3n-2)
}

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(const tridiagonalMatrix<T> &tdm)//O(3n-2)
{
    n = tdm.n;
    element = new T[3*n-2];//O(1) or O(3*n-2)
    copy(tdm.element, tdm.element + n + 2*(n-1), element);//O(3n-2)
    // for(int i = 0; i < 3*n-2; i++)
    //     element[i] = tdm.element[i];
}

template<class T>
tridiagonalMatrix<T>::~tridiagonalMatrix()//O(1) or O(3n-2)
{
    // if(element != nullptr)
        delete []element;//O(1) or O(3n-2)
}

template<class T>
T tridiagonalMatrix<T>::get(int i, int j)const//O(1)
{
    if(i < 1 || j < 1 || i > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    switch(i - j)//O(1)
    {
        case 1:
            return element[-i+2*j];//O(1)
        case 0:
            return element[n+i-2];//O(1)
        case -1:
            return element[2*n-1+2*i-j];//O(1)
        default: return 0;//O(1)
    }
}

template<class T>
void tridiagonalMatrix<T>::set(int i, int j, const T& newValue)//O(1)
{
    if(i < 1 || j < 1 || i  > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    if(i == j)
        element[n+i-2] = newValue;//O(1)
    else if(i - j == 1)
        element[-i+2*j] = newValue;//O(1)
    else if(i - j == -1)
        element[2*n-1+2*i-j] = newValue;//O(1)
    else
        if(newValue != 0)//O(1)
            throw illegalParameter("nontridiagonal elements must be zero");
}

template<class T>
tridiagonalMatrix<T> tridiagonalMatrix<T>::operator+(const tridiagonalMatrix<T> &tdm)const//O(1) or O(3n-2)
{
    if(n == tdm.n)
    {
        tridiagonalMatrix<T> w(*this);//O(3n-2)
        for(int i = 0; i < 3*n-2; i++)//O(3n-1)
            w.element[i] += tdm.element[i];
        return w;
    }
    else//O(1)
        throw matrixSizeMimatch();
}

template<class T>
tridiagonalMatrix<T> tridiagonalMatrix<T>::operator-(const tridiagonalMatrix<T> &tdm)const//O(1) or O(3n-2)
{
    if(n == tdm.n)
    {
        tridiagonalMatrix<T> w(*this);//O(3n-2)
        for(int i = 0; i < 3*n-2; i++)//O(3n-1)
            w.element[i] -= tdm.element[i];
        return w;
    }
    else//O(1)
        throw matrixSizeMimatch();
}

template<class T>
matrix<T> tridiagonalMatrix<T>::operator*(const tridiagonalMatrix<T> &tdm)const//O(1) or O(n^3)
{
    if(n == tdm.n)//O(n^3)
    {
        //创建结果矩阵，size为n*n
        matrix<T> re(n, n);//O(1) or O(n*n)
        
        for(int i = 1; i <= n; i++)//O(n*n*n)
            for(int j = 1; j <= n; j++)
            {
                T theValue = 0;
                for(int k = 1; k <= n; k++)
                {
                    theValue += get(i, k) * tdm.get(k, j);
                }
                re(i, j) = theValue;//O(1)
            }
        return re;
    }
    else//O(1)
        throw matrixSizeMimatch();
}

template<class T>
tridiagonalMatrix<T> tridiagonalMatrix<T>::transpose()const//O(3n-2)
{
    tridiagonalMatrix<T> w(*this);//O(3n-2)
    for(int i = 0; i < n-1; i++)//O(n)
        swap(w.element[i], w.element[2*n-1+i]);//O(1)
    return w;
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
    cout << endl;
    // tridiagonalMatrix<int> tdmCopy(tdm);
    cout << tdm.transpose();
    // tridiagonalMatrix<int> dm2(3);
    // cout << tdm*tdmCopy;
    // cout << tdmCopy;
    // cout << tdm.get(2, 4);
}