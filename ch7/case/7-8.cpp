//对角矩阵是特殊的方阵
#include<iostream>
#include"../../Tool.h"

using namespace std;

template<class T>
class diagonalMatrix
{
    public:
        diagonalMatrix(int theN = 10);
        diagonalMatrix(const diagonalMatrix<T> &d);
        ~diagonalMatrix(){if(element != nullptr) delete []element;}
        void set(int, int, const T&);
        T get(int,int)const;
        //20：输入 待解
        //20：输出
        void output(ostream &out)const;
        //加
        diagonalMatrix<T> operator+(const diagonalMatrix<T>& dm)const;
        //减
        diagonalMatrix<T> operator-(const diagonalMatrix<T>& dm)const;
        //乘
        diagonalMatrix<T> operator*(const diagonalMatrix<T> &dm)const;
        //转置
        diagonalMatrix<T> transpose()const;
    private:
        int n;//方阵的维数
        T* element;
};

template<class T>
ostream& operator<<(ostream& out, const diagonalMatrix<T> &d)//O(n^2)
{
    d.output(out);
    return out;
}

template<class T>
void diagonalMatrix<T>::output(ostream& out)const//O(n^2)
{
    if(element != nullptr)
    {
        out << "output diagonalMatrix:\n";
        int iter = 0;
        for(int i = 0; i < n; i++)//O(n^2)
            for(int j = 0; j < n; j++)
            {
                if(i == j)
                    out << element[iter++] << " ";
                else
                    out << 0 << " ";
                if(j % (n-1) == 0 && j != 0)
                    out << endl;
            }
    }
}

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN)//O(n) or O(1)
{
    if(theN < 1)//O(1)
        throw illegalParameter("Matrix dimenssion should be > 0");
    n = theN;
    element = new T[n];//O(n) or O(1)
}

template<class T>
diagonalMatrix<T>::diagonalMatrix(const diagonalMatrix<T> &d)//O(n)
{
    n = d.n;
    element = new T[n];//O(n) or O(1)
    copy(d.element, d.element + d.n, element);//O(n)
}

template<class T>
void diagonalMatrix<T>::set(int i, int j, const T& newValue)//O(1)
{
    if((i < 1 || j < 1) || (i > n || j > n))//O(1)
        throw matrixIndexOutOfBounds();
    if(i == j)//O(1)
        element[i-1] = newValue;
    else
        if(newValue != 0)//O(1)
            throw illegalParameter("nondiagonal elements  must be zero");
}

template<class T>
T diagonalMatrix<T>::get(int i, int j)const//O(1)
{
    if(i < 1 || j < 1 || i > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    if(i == j)//O(1)
        return element[i-1];
    else return 0;//O(1)
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator+(const diagonalMatrix<T> &dm)const//O(1) or O(n)
{
    if(n == dm.n)//O(n)
    {
        diagonalMatrix<T> w(n);//O(1) or O(n)
        T theValue = 0;
        for(int i = 0; i < n; i++)//O(n)
        {
            theValue = element[i] + dm.element[i];
            w.element[i] = theValue;
        }
        return w;
    }
    else//O(1)
        throw matrixSizeMimatch();
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator-(const diagonalMatrix<T> &dm)const//O(1) or O(n)
{
    if(n == dm.n)//O(n)
    {
        diagonalMatrix<T> w(n);//O(1) or O(n)
        T theValue = 0;
        for(int i = 0; i < n; i++)//O(n)
        {
            theValue = element[i] - dm.element[i];
            w.element[i] = theValue;
        }
        return w;
    }
    else//O(1)
        throw matrixSizeMimatch();
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator*(const diagonalMatrix<T> &dm)const//O(1) or O(n)
{
    if(n == dm.n)//O(n)
    {
        diagonalMatrix<T> w(n);//O(1) or O(n)
        T theValue = 0;
        for(int i = 0; i < n; i++)//O(n)
        {
            theValue = element[i]*dm.element[i];
            w.element[i] = theValue;
        }
        return w;
    }
    else//O(1)
        throw matrixSizeMimatch();
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::transpose()const//O(n)
{
    return diagonalMatrix<T>(*this);
}

int main()
{
    diagonalMatrix<int> dm(5);
    dm.set(1, 1, 1);
    dm.set(2, 2, 2);
    dm.set(3, 3, 3);
    dm.set(4, 4, 4);
    dm.set(5, 5, 5);
    diagonalMatrix<int> dm1(dm);
    cout << dm.transpose();
}