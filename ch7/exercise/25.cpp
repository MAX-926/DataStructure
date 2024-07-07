//tridiagonalAsIrregularArray
#include<iostream>
#include"../../Tool.h"
using namespace std;

template<class T>
class tridiagonalAsIrregularArray
{
    public:
        tridiagonalAsIrregularArray(int theN = 10);
        tridiagonalAsIrregularArray(const tridiagonalAsIrregularArray<T> &tdaia);
        ~tridiagonalAsIrregularArray();
        //存值
        void set(int i, int j, const T& newValue);
        //取值
        T get(int i, int j)const;
        //输出
        void output(ostream& out)const;
        //加
        tridiagonalAsIrregularArray<T> operator+(const tridiagonalAsIrregularArray<T> &tdaia)const;
        //减
        tridiagonalAsIrregularArray<T> operator-(const tridiagonalAsIrregularArray<T> &tdaia)const;
        //矩阵转置
        tridiagonalAsIrregularArray<T> transpose()const;
    private:
        int n;
        T **element;
};

template<class T>
ostream& operator<<(ostream& out, const tridiagonalAsIrregularArray<T> &tdaia)
{
    tdaia.output(out);
    return out;
}

template<class T>
tridiagonalAsIrregularArray<T>::tridiagonalAsIrregularArray(int theN)//O(1) or O(n)
{
    if(theN < 2)//O(1)
        throw illegalParameter("theN must be > 1");
    else//O(1) or O(n)
    {
        n = theN;
        element = new T*[n];
        for(int i = 1; i < n-1; i++)
            element[i] = new T[3];
        element[0] = new T[2];
        element[n-1] = new T[2];
    }
}

template<class T>
tridiagonalAsIrregularArray<T>::tridiagonalAsIrregularArray(const tridiagonalAsIrregularArray<T> &tdaia)//O(n)
{
    n = tdaia.n;
    element = new T*[n];//O(1)
    for(int i = 0; i < n; i++)//O(n)
    {
        if(i == 0 || i == n-1)//O(1)
        {
            element[i] = new T[2];//O(1)
            // copy(tdaia.element[i], tdaia.element[i] + 2, element[i]);//O(1)
        }
        else//O(1)
        {
            element[i] = new T[3];//O(1)
            // copy(tdaia.element[i], tdaia.element[i] + 3, element[i]);//O(1)
        }
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i-j <= 1 ||j-i <= 1)
                element[i-1][j-1] = tdaia.element[i-1][j-1];
        }

}

template<class T>
tridiagonalAsIrregularArray<T>::~tridiagonalAsIrregularArray()//O(n)
{
    for(int i = 0; i < 3; i++)
        delete[] element[i];
    delete[] element;
}

template<class T>
void tridiagonalAsIrregularArray<T>::set(int i, int j, const T& newValue)//O(1)
{
    if(i < 1 || j < 1 || i > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    else//O(1)
    {
        if(i-j <= 1 || j-i <= 1)
        {
            if(i == 1)
                element[i-1][j-1] = newValue;
            else if(i == n)
                element[i-1][j-n+1] = newValue;
            else
                element[i-1][-i+j+1] = newValue;
        }
        else//O(1)
            if(newValue != 0)
                throw illegalParameter("nontridiagonal elements must be zero");
    }
}

template<class T>
T tridiagonalAsIrregularArray<T>::get(int i, int j)const//O(1)
{
    if(i < 1 || j < 1 || i > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    else
        if(i-j > 1 || j-i > 1)
            return 0;
        else//O(1)
        {
            if(i == 1) return element[i-1][j-1];
            else if(i == n) return element[i-1][j-n+1];
            else return element[i-1][-i+j+1];
        }
}

template<class T>
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::operator+(const tridiagonalAsIrregularArray<T> &tdaia)const//O(1) or O(3n-2)
{
    if(n != tdaia.n)//O(1)
        throw matrixSizeMimatch();
    else//O(3n-2)
    {
        tridiagonalAsIrregularArray<T> w(*this);//O(3n-2)
        for(int i = 0; i < n; i++)//O(3n-2)
            for(int j = 0; j < ((i == 0 || i == n-1)?2:3); j++)
                w.element[i][j] += tdaia.element[i][j];
        return w;
    } 
}

template<class T>
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::operator-(const tridiagonalAsIrregularArray<T> &tdaia)const//O(1) or O(3n-2)
{
    if(n != tdaia.n)//O(1)
        throw matrixSizeMimatch();
    else//O(3n-2)
    {
        tridiagonalAsIrregularArray<T> w(*this);//O(3n-2)
        for(int i = 0; i < n; i++)//O(3n-2)
            for(int j = 0; j < ((i == 0 || i == n-1)?2:3); j++)
                w.element[i][j] -= tdaia.element[i][j];
        return w;
    } 
}

template<class T>
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::transpose()const//O(3n-2)
{
    tridiagonalAsIrregularArray<T> w(*this);//O(3n-2)
    for(int i = 1; i < n; i++)//O(n)
        swap(w.element[i-1][i], w.element[i][i-1]);
    return w;
}

template<class T>
void tridiagonalAsIrregularArray<T>::output(ostream& out)const//O(n^2)
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i-j>1 || j-i>1)
                out << 0 << " ";
            else
            {
                if(i == 1) out << element[i-1][j-1] << " ";
                else if(i == n) out << element[i-1][j-n+1] << " ";
                else out << element[i-1][-i+j+1] << " ";
            }
            if(j % n == 0)
                out << endl;
        }
}

int main()
{
    tridiagonalAsIrregularArray<int> w(4);
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

    // tridiagonalAsIrregularArray<int> w(1);
    // w.set(1, 1, 1);
    // w.set(1, 2, 2);
    // w.set(2, 1, 3);
    // w.set(2, 2, 4);
    cout << w;
    // cout << endl << w.transpose();
    // tridiagonalAsIrregularArray<int> cpy(w);
    // cout << w.get(3, 4);
    
    // cout << cpy;
    // cout << w.get(1, 1);
    // w.outputElements();
    // cout << endl << w.transpose() << endl;
    // cout << w - w.transpose();
}