#include<iostream>
#include"../../Tool.h"
using namespace std;

template<class T>
class matrixAs2DArray
{
    public:
        matrixAs2DArray(int theRows = 0, int theColumns = 0);
        matrixAs2DArray(const matrixAs2DArray<T> &m);
        ~matrixAs2DArray();
        //ADT methods:
        //matrix +
        matrixAs2DArray<T> operator+()const;// Unary +
        matrixAs2DArray<T> operator+(const matrixAs2DArray<T>& m)const;
        //matrix -
        matrixAs2DArray<T> operator-()const;// Unary -
        matrixAs2DArray<T> operator-(const matrixAs2DArray<T> &m)const;
        //matrix *
        matrixAs2DArray<T> operator*(const matrixAs2DArray<T> &m)const;
        //matrix +=
        matrixAs2DArray<T>& operator+=(const T& theValue);
        //matrix -=
        matrixAs2DArray<T>& operator-=(const T &theValue);
        //matrix *=
        matrixAs2DArray<T>& operator*=(const T& theValue);
        //matrix /=
        matrixAs2DArray<T>& operator/=(const T &theValue);
        // =
        matrixAs2DArray<T>& operator=(const matrixAs2DArray<T> &m);
        // ()
        T& operator()(int i, int j)const;
        //transpose()
        matrixAs2DArray<T> transpose()const;
        //output function
        void output(ostream& out)const;
        //get rows and columns:
        int rows()const{return theRows;}
        int columns()const{return theColumns;}
    protected:
        int theRows;
        int theColumns;
        T** element;
};

template<class T>
matrixAs2DArray<T>::matrixAs2DArray(int theRows, int theColumns)
{
    if(theRows < 0 || theColumns < 0)
        throw illegalParameter("theRows and theColumns must be >= 0");
    if((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
        throw illegalParameter("Either both or neither rows and columns should be zero");
    //创建数组
    element = new T*[theRows];
    for(int i = 0; i < theRows; i++)
        element[i] = new T[theColumns];
    this->theRows = theRows;
    this->theColumns = theColumns; 
}

template<class T>
matrixAs2DArray<T>::matrixAs2DArray(const matrixAs2DArray<T>& m)
{
    // for(int i = 0; i < theRows; i++)
    // {
    //     delete []element[i];
    // }
    // delete []element;
    //创建数组
    theRows = m.theRows;
    theColumns = m.theColumns;
    element = new T*[theRows];
    for(int i = 0; i < theRows; i++)
        element[i] = new T[theColumns];
    //元素复制
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < theColumns; j++)
            element[i][j] = m.element[i][j];
}

template<class T>
matrixAs2DArray<T>::~matrixAs2DArray()
{
    if(element != nullptr)
    {
        for(int i = 0; i < theRows; i++)
            delete []element[i];
        delete []element;
    }
    return;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator+()const
{
    return matrixAs2DArray<T>(*this);
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator+(const matrixAs2DArray<T> &m)const
{
    if(theRows != m.theRows || theColumns != m.theColumns)
        throw matrixSizeMimatch();
    matrixAs2DArray<T> w(*this);
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < theColumns; j++)
            w.element[i][j] += m.element[i][j];
    return w;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator-()const
{
    matrixAs2DArray<T> w(*this);
    for(int i = 0; i < w.theRows; i++)
        for(int j = 0; j < w.theColumns; j++)
            w.element[i][j] *= -1;
    return w;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator-(const matrixAs2DArray<T> &m)const
{
    if(theRows != m.theRows || theColumns != m.theColumns)
        throw matrixSizeMimatch();
    matrixAs2DArray<T> w(*this);
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < theColumns; j++)
            w.element[i][j] -= m.element[i][j];
    return w;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator*(const matrixAs2DArray<T> &m)const
{
    if(theColumns != m.theRows)
        throw matrixSizeMimatch();
    matrixAs2DArray<T> w(theRows, m.theColumns);
    //初始化结果矩阵
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < m.theColumns; j++)
            w.element[i][j] = 0;
    //赋值
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < m.theRows; j++)
            for(int k = 0; k < m.theColumns; k++)
                w.element[i][k] += element[i][j] * m.element[j][k];
    return w;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator+=(const T& theValue)
{
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < theColumns; j++)
            element[i][j] += theValue;
    return *this;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator-=(const T &theValue)
{
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < theColumns; j++)
            element[i][j] -= theValue;
    return *this;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator*=(const T &theValue)
{
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < theColumns; j++)
            element[i][j] *= theValue;
    return *this;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator/=(const T &theValue)
{
    if(theValue == 0)
        throw illegalParameter("the divisor shouldn't be zero");
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < theColumns; j++)
            element[i][j] /= theValue;
    return *this;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator=(const matrixAs2DArray<T> &m)
{
    if(this != &m)
    {
        if(theRows != m.theRows || theColumns != m.theColumns)
        {
            for(int i = 0; i < theRows; i++)
                delete []element[i];
            delete []element;
            theRows = m.theRows;
            theColumns = m.theColumns;
            element = new T*[m.theRows];
            for(int i = 0; i < theRows; i++)
                element[i] = new T[m.theColumns];
        }
        //赋值
        for(int i = 0; i < theRows; i++)
            for(int j = 0; j < theColumns; j++)
                element[i][j] = m.element[i][j];
    }
    return *this;
}

template<class T>
T& matrixAs2DArray<T>::operator()(int i, int j)const
{
    if((i <= 0 || j <= 0) || (i > theRows || j > theColumns))
        throw matrixIndexOutOfBounds();
    return element[i-1][j-1];
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::transpose()const
{
    matrixAs2DArray<T> w(theColumns, theRows);
    for(int i = 0; i < theColumns; i++)
        for(int j = 0; j < theRows; j++)
            w.element[i][j] = element[j][i];
    return w;
}

template<class T>
void matrixAs2DArray<T>::output(ostream& out)const
{
    for(int i = 0; i < theRows; i++)
        for(int j = 0; j < theColumns; j++)
        {
            out << element[i][j] << " ";
            if((j+1) % theColumns == 0)
                out << endl;
        }
}

template<class T>
ostream& operator<<(ostream& out, const matrixAs2DArray<T> &m)
{
    m.output(out);
    return out;
}

int main()
{
    // matrixAs2DArray<int> m1(3, 5);
    // for(int i = 1; i <= 3; i++)
    //     for(int j = 1; j <= 5; j++)
    //         m1(i, j) = 2;
    // cout << "m1:" << endl << m1; 
    // cout << "m1Trans:" << endl << m1.transpose();
    // // m1/=0;
    // cout << "m1:" << endl << m1;
    matrixAs2DArray<int> m1(2, 2), m2(2, 3);
    m1(1, 1) = 1;
    m1(1, 2) = 2;
    m1(2, 1) = 3;
    m1(2, 2) = 4;
    matrixAs2DArray<int> m11(m1);
    m2(1, 1) = 1;
    m2(1, 2) = 2;
    m2(1, 3) = 3;
    m2(2, 1) = 4;
    m2(2, 2) = 5;
    m2(2, 3) = 6;
    cout << "m1:" << endl << m1;
    cout << "m2:" << endl << m2;
    // cout << "m11:" << endl << m11;
    cout << "m1+m11:" << endl << m1+m11;

    // cout << "m1*m2:" << endl << m1*m2;
    // cout << "m1Trans:" << endl << m1.transpose();
}