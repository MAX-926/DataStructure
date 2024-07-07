//tridiagonalByRows
#include<iostream>
#include"../../Tool.h"
using namespace std;

template<class T>
class tridiagonalByRows
{
    public:
        tridiagonalByRows(int theN = 10);
        tridiagonalByRows(const tridiagonalByRows<T> &tdbr);
        ~tridiagonalByRows(){delete []element;}
        //存值
        void set(int i, int j, const T& newValue);
        //取值
        T get(int i, int j)const;
        //输出
        void output(ostream& out)const;
        //加
        tridiagonalByRows<T> operator+(const tridiagonalByRows<T> &tdbr)const;
        //减
        tridiagonalByRows<T> operator-(const tridiagonalByRows<T> &tdbr)const;
        //矩阵转置
        tridiagonalByRows<T> transpose()const;
        //输出eleme,检验元素存储顺序
        void outputElements()const;
    private:
        int n;
        T* element;
};

template<class T>
ostream& operator<<(ostream& out, const tridiagonalByRows<T> &tdbr)
{
    tdbr.output(out);
    return out;
}

template<class T>
tridiagonalByRows<T>::tridiagonalByRows(int theN)//O(1) or O(3n-2)
{
    if(theN < 2)//O(1)
        throw illegalParameter("theN must be > 1");
    else
    {
        n = theN;
        element = new T[3*n-2];//O(1) or O(3n-2)
    }
}

template<class T>
tridiagonalByRows<T>::tridiagonalByRows(const tridiagonalByRows<T> &tdbr)//O(3n-2)
{
    n = tdbr.n;
    element = new T[3*n-2];//O(1) or O(3n-2)
    copy(tdbr.element, tdbr.element+3*n-2, element);//O(3n-2)
}

template<class T>
void tridiagonalByRows<T>::set(int i, int j, const T& newValue)//O(1)
{
    if(i < 1 || j < 1 || i > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    else
    {
        switch(i-j)//O(1)
        {
            case 0:
                element[3*j-3] = newValue;
                break;
            case 1:
                element[3*j-1] = newValue;
                break;
            case -1:
                element[3*j-5] = newValue;
                break;
            default://O(1)
                if(newValue != 0)
                    throw illegalParameter("nontridiagonal elements must be zero");
        }
    }
}

template<class T>
T tridiagonalByRows<T>::get(int i, int j)const//O(1)
{
    if(i < 1 || j < 1 || i > n || j > n)//O(1)
        throw matrixIndexOutOfBounds();
    else//O(1)
    {
        switch(i-j)//O(1)
        {
            case 0:
                return element[3*j-3];
            case 1:
                return element[3*j-1];
            case -1:
                return element[3*j-5];
            default:
                return 0;
        }
    }   
}

template<class T>
tridiagonalByRows<T> tridiagonalByRows<T>::operator+(const tridiagonalByRows<T> &tdbr)const//O(1) or O(3n-2)
{
    if(n != tdbr.n)//O(1)
        throw matrixSizeMimatch();
    else//O(3n-2)
    {
        tridiagonalByRows<T> w(*this);//O(1) or O(3n-2)
        for(int i = 0; i < 3*n-2; i++)//O(3n-2)
            w.element[i] += tdbr.element[i];
        return w;
    }
}

template<class T>
tridiagonalByRows<T> tridiagonalByRows<T>::operator-(const tridiagonalByRows<T> &tdbr)const//O(1) or O(3n-2)
{
    if(n != tdbr.n)//O(1)
        throw matrixSizeMimatch();
    else//O(3n-2)
    {
        tridiagonalByRows<T> w(*this);//O(1) or O(3n-2)
        for(int i = 0; i < 3*n-2; i++)//O(3n-2)
            w.element[i] -= tdbr.element[i];
        return w;
    }
}

template<class T>
tridiagonalByRows<T> tridiagonalByRows<T>::transpose()const//O(3n-2)
{
    tridiagonalByRows<T> w(*this);//O(3n-2)
    for(int i = 1; i <= n-1; i++)//O(n)
        swap(w.element[3*i-1], w.element[3*(i+1)-5]);
    return w;    
}

template<class T>
void tridiagonalByRows<T>::output(ostream& out)const//O(n^2)
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i == j)
                out << element[3*j-3] << " ";
            else if(i-j == 1)
                out << element[3*j-1] << " ";
            else if(i-j == -1)
                out << element[3*j-5] << " ";
            else
                out << 0 << " ";
            if(j % n == 0)
                out << endl;
        }
}

template<class T>
void tridiagonalByRows<T>::outputElements()const//O(3n-2)
{
    for(int i = 0; i < 3*n-2; i++)//O(3n-2)
        cout << element[i] << " ";
}

int main()
{
    // tridiagonalByRows<int> w(4);
    // w.set(1, 1, 2);
    // w.set(1, 2, 1);
    // w.set(2, 1, 3);
    // w.set(2, 2, 1);
    // w.set(2, 3, 3);
    // w.set(3, 2, 5);
    // w.set(3, 3, 2);
    // w.set(3, 4, 7);
    // w.set(4, 3, 9);
    // w.set(4, 4, 0);
    // w.set(4, 1, 0);

    tridiagonalByRows<int> w(1);
    // w.set(1, 1, 1);
    // w.set(1, 2, 2);
    // w.set(2, 1, 3);
    // w.set(2, 2, 4);
    cout << w;
    // cout << w.get(1, 1);
    // w.outputElements();
    cout << endl << w.transpose() << endl;
    // cout << w - w.transpose();
}