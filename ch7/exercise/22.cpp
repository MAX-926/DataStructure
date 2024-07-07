//tridiagonalByColumns
//keypoints:将三对角矩阵的元素列出，为每条对角线的元素建立索引公式
#include<iostream>
#include"../../Tool.h"
using namespace std;

bool nontridiagonalElements(int i, int j)
{
    if(i-j < 0) return (j-i > 1);
    else return (i-j) > 1;
}

template<class T>
class tridiagonalByColumns
{
    public:
        tridiagonalByColumns(int theN = 10);
        tridiagonalByColumns(const tridiagonalByColumns<T> &tdbc);
        ~tridiagonalByColumns(){delete []element;}
        //ADT methods:
        //存值
        void set(int i, int j, const T& newValue);
        //取值
        T get(int i, int j)const;
        //加
        tridiagonalByColumns<T> operator+(const tridiagonalByColumns<T> &tdmbc)const;
        //减
        tridiagonalByColumns<T> operator-(const tridiagonalByColumns<T> &tdmbc)const;
        //矩阵转置
        tridiagonalByColumns<T> transpose()const;
        //输出
        void output(ostream& out)const;
        void outputElements()const;
    private:
        int n;
        T* element;
};

template<class T>
void tridiagonalByColumns<T>::outputElements()const
{
    for(int i = 0; i < 3*n-2; i++)
        cout << element[i] << " ";
}

template<class T>
ostream& operator<<(ostream& out, const tridiagonalByColumns<T> &tdbc)//O(n^2)
{
    tdbc.output(out);
    return out;
}

template<class T>
tridiagonalByColumns<T>::tridiagonalByColumns(int theN)//O(1) or O(3n-2)
{
    if(n < 2)//O(1)
        throw illegalParameter("theN must be >= 2");
    else
    {
        n = theN;//O(1)
        element = new T[3*n-2];//O(1) or O(3n-2)
    }
}

template<class T>
tridiagonalByColumns<T>::tridiagonalByColumns(const tridiagonalByColumns<T>& tdbc)//O(3n-2)
{
    n = tdbc.n;
    element = new T[3*n-2];//O(1) or O(3n-2)
    copy(tdbc.element, tdbc.element + 3*n-2, element);//O(3n-2)
}

template<class T>
void tridiagonalByColumns<T>::set(int i, int j, const T& newValue)//O(1)
{
    if(i < 1 || j < 1 || i > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    switch(i - j)
    {
        case 0:
            element[3*j-3] = newValue;//O(1)
            return;
        case 1:
            element[3*j-2] = newValue;//O(1)
            return;
        case -1:
            element[4*i-j] = newValue;//O(1)
            return;
        default://O(1)
            if(newValue != 0)   throw illegalParameter("nontridiagonalElements must be zero");
    }
}

template<class T>
T tridiagonalByColumns<T>::get(int i, int j)const//O(1)
{
    if(i < 1 || j < 1 || i > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    switch(i-j)//O(1)
    {
        case 0:
            return element[3*j-3];//O(1)
        case 1:
            return element[3*j-2];//O(1)
        case -1:
            return element[4*i-j];//O(1)
        default: return 0;//O(1)
    }
}


template<class T>
tridiagonalByColumns<T> tridiagonalByColumns<T>::operator+(const tridiagonalByColumns<T> &tdbc)const//O(1) or O(3n-2)
{
    if(n == tdbc.n)//O(3n-2)
    {
        tridiagonalByColumns<T> w(*this);//O(3n-2)
        for(int i = 0; i < 3*n-2; i++)//O(3n-2)
            w.element[i] += tdbc.element[i];
        return w;
    }
    else//O(1)
        throw matrixSizeMimatch();
}

template<class T>
tridiagonalByColumns<T> tridiagonalByColumns<T>::operator-(const tridiagonalByColumns<T> &tdbc)const//O(1) or O(3n-2)
{
    if(n == tdbc.n)//O(3n-2)
    {
        tridiagonalByColumns<T> w(*this);//O(3n-2)
        for(int i = 0; i < 3*n-2; i++)//O(3n-2)
            w.element[i] -= tdbc.element[i];
        return w;
    }
    else//O(1)
        throw matrixSizeMimatch();
}

template<class T>
tridiagonalByColumns<T> tridiagonalByColumns<T>::transpose()const//O(3n-2)
{
    tridiagonalByColumns<T> w(*this);//O(3n-2)
    //swap diagonalElements 3j-2 4i-j
    for(int i = 1; i <= n-1; i++)//O(n)
        swap(element[4*i-(i+1)], element[3*i-2]);
    return w;
}

template<class T>
void tridiagonalByColumns<T>::output(ostream& out)const//O(n^2)
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(nontridiagonalElements(i, j)) out << 0 << " ";//O(1)
            else//O(1)
            {
                if(i == j)
                    out << element[3*j-3] << " ";
                else if(i - j == 1)
                    out << element[3*j-2] << " ";
                else if(i - j == -1)
                    out << element[4*i-j] << " ";
            }
            if(j % n == 0) out << endl;//O(1)
        }
}

int main()
{
    tridiagonalByColumns<int> w(4);
    w.set(1, 1, 2);
    w.set(1, 2, 1);
    w.set(2, 1, 3);
    w.set(2, 2, 1);
    w.set(2, 3, 3);
    w.set(3, 2, 5);
    w.set(3, 3, 2);
    w.set(3, 4, 7);
    w.set(4, 3, 9);
    w.set(4, 4, 0);
    // w.set(4, 1, 0);

    cout << w;
    w.outputElements();
}