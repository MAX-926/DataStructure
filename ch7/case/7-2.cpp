#include<iostream>
#include"../../Tool.h"
#include<string.h>
using namespace std;

template<class T>
class matrix
{
    public:
        matrix(int theRows = 0, int theColumns = 0);
        matrix(const matrix<T>& theMatrix);
        ~matrix(){if(element) delete []element;}

        int rows()const{return theRows;}
        int columns()const{return theColumns;}
        T& operator()(int i, int j)const;
        matrix<T>& operator=(const matrix<T>& theMatrix);
        matrix<T> operator+()const;// unary +
        matrix<T> operator+(const matrix<T>& theMatrix)const;
        matrix<T> operator-()const;// unary -
        matrix<T> operator-(const matrix<T>& theMatrix)const;
        matrix<T> operator*(const matrix<T>& theMatrix)const;
        matrix<T>& operator+=(const T& theValue);
        //15.cpp: operator-=()、operator*=()、operator/=()
        matrix<T> operator-=(const T& theValue)const;
        matrix<T> operator*=(const T& theValue)const;
        matrix<T> operator/=(const T& theValue)const;
        //16.cpp: transpose()
        matrix<T> transpose()const;
        //output matrix:
        void output(ostream &out)const;
    protected:
        int theRows;//矩阵的行数
        int theColumns;//矩阵的列数
        T *element;//数组element
};

template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
    if(theRows < 0 || theColumns < 0)
    {
        throw illegalParameter("theRows and theColumns must be >= 0");
    }
    if((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
    {
        throw illegalParameter("Either both or neither theRows and theColumns should be 0");
    }
    this->theRows = theRows;
    this->theColumns = theColumns;
    this->element = new T[theRows*theColumns];//O(1) or O(theRows*theColumns)
}

template<class T>
matrix<T>::matrix(const matrix<T> &theMatrix)
{
    theRows = theMatrix.theRows;
    theColumns = theMatrix.theColumns;
    element = new T[theRows*theColumns];
    //复制m的每一个元素
    // for(int i = 0; i < theRows*theColumns; i++)
    //     element[i] = theMatrix.element[i];
    std::copy(theMatrix.element, theMatrix.element+theRows*theColumns, element);
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& theMatrix)
{//（*this）= theMatrix
    //赋值 不能自己赋值自己
    if(this != &theMatrix)
    {
        theRows = theMatrix.theRows;
        theColumns = theMatrix.theColumns;
        delete []element;
        element = new T[theRows*theColumns];
        std::copy(theMatrix.element, theMatrix.element + theRows*theColumns, element);
    }
    return *this;
}

template<class T>
T& matrix<T>::operator()(int i, int j)const
{
    if(i < 1 || i > theRows || j < 1 || j > theColumns)
        throw matrixIndexOutOfBounds();
    return element[theColumns*(i-1) + (j-1)];
}

//unary +
template<class T>
matrix<T> matrix<T>::operator+()const
{
    matrix<T> w(*this);
    return w;
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& theMatrix)const
{
    if(theRows != theMatrix.theRows || theColumns != theMatrix.theColumns)
        throw matrixSizeMimatch();
    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < theRows*theColumns; i++)
        w.element[i] = element[i] + theMatrix.element[i];
    return w;
}

template<class T>
matrix<T> matrix<T>::operator-()const
{
    matrix<T> w(*this);
    for(int i = 0; i < w.theRows * w.theColumns; i++)
        w.element[i] = -w.element[i];
    return w;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T> &theMatrix)const
{
    if(theRows != theMatrix.theRows || theColumns != theMatrix.theColumns)
        throw matrixSizeMimatch();
    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < w.theRows * w.theColumns; i++)
        w.element[i] = element[i] - theMatrix.element[i];
    return w;
}

// template<class T>
// matrix<T> matrix<T>::operator*(const matrix<T>& theMatrix)const
// {
//     if(theColumns != theMatrix.theRows)
//         throw matrixSizeMimatch();
//     matrix<T> w(theRows, theMatrix.theColumns);
//     //对新对象w的element做归零初始化:欲规避此步则需要创建一个变量用于存放内积的结果
//     // memset(w.element, 0, sizeof(T) * theRows*theMatrix.theColumns);
//     //矩阵乘法

//     //1.
//     // for(int i = 1; i <= theRows; i++)
//     //     for(int j = 1; j <= theMatrix.theRows; j++)
//     //         for(int k = 1; k <= theMatrix.theColumns; k++)
//     //         {
//     //             w(i, k) += (*this)(i, j) * theMatrix(j, k);
//     //         }

//     //2.
//     int ct = 0, cm = 0, cw = 0;
//     for(int i = 1; i <= theRows; i++)
//     {//计算结果矩阵的第i行
//         for(int j = 1; j <= theMatrix.theColumns; j++)
//         {//计算w(i ,j)的第一项
//             T sum = element[ct] * theMatrix.element[cm];
//             //累加其余所有项
//             for(int k = 2; k <= theColumns; k++)
//             {
//                 ct++;
//                 cm += theMatrix.theColumns;
//                 sum += element[ct] * theMatrix.element[cm];
//             }
//             w.element[cw++] = sum;
//             //从行的起点和下一列重新开始
//             ct -= theColumns - 1;
//             cm = j;
//         }
//         //从下一列和第一列重新开始
//         ct += theColumns;
//         cm = 0;
//     }

//     return w;
// }

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& theMatrix)const
{
    if(theColumns != theMatrix.theRows)
        throw matrixSizeMimatch();
    matrix<T> w(theRows, theMatrix.theColumns);
    // memset(w.element, 0, sizeof(T)*theRows*theMatrix.theColumns);
    int ct = 0, cm = 0, cw = 0;
    for(int i = 1; i <= theRows; i++)
    {
        for(int j = 1; j <= theMatrix.theColumns; j++)
        {//
            T sum = element[ct] * theMatrix.element[cm];
            // cm += theMatrix.theColumns;
            for(int k = 2; k <= theColumns; k++)
            {
                cm += theMatrix.theColumns;
                ct++;//!!!
                sum += element[ct] * theMatrix.element[cm];
            }
            w.element[cw++] = sum;
            ct -= theColumns-1;//回到起点
            cm = j;
        }
        //从新一行和第0列重新开始
        ct += theColumns;
        cm = 0;
    }
    return w;
}

template<class T>
matrix<T>& matrix<T>::operator+=(const T &theValue)
{
    for(int i = 0; i < theRows * theColumns; i++)
        element[i] += theValue;
    return *this;
}

template<class T>
matrix<T> matrix<T>::operator-=(const T& theValue)const
{
    matrix<T> w(theRows, theColumns);
    memset(w.element, 0, sizeof(T)*theRows*theColumns);
    for(int i = 0; i < theRows*theColumns; i++)
        w.element[i] = element[i] - theValue;
    return w;
}

template<class T>
matrix<T> matrix<T>::operator*=(const T& theValue)const
{
    matrix<T> w(*this);
    for(int i = 0; i < theRows*theColumns; i++)
        w.element[i] *= theValue;
    return w;
}

template<class T>
matrix<T> matrix<T>::operator/=(const T& theValue)const
{
    if(theValue == 0)
        throw illegalParameter("the Divisor mustn't be zero");
    matrix<T> w(*this);
    for(int i = 0; i < theRows*theColumns; i++)
        w.element[i] /= theValue;
    return w;
}

template<class T>
matrix<T> matrix<T>::transpose()const
{
    matrix<T> w(theColumns, theRows);
    int cw = 0, ct = 0;
    for(int i = 0; i < theColumns; i++)
    {
        for(int j = 0; j < theRows; j++)
        {
            w.element[cw++] = element[ct];
            ct += theColumns;
        }
        ct = i;
        ct++;
    }
    return w;
}

template<class T>
void matrix<T>::output(ostream& out)const
{
    for(int i = 0, tag = 1; i < theRows * theColumns; i++, tag++)
    {
        out << element[i] << " ";
        if(tag % theColumns == 0)
            out << endl;
    }
}

template<class T>
ostream& operator<<(ostream& out, const matrix<T>& theMatrix)
{
    theMatrix.output(out);
    return out;
}

// int main()
// {
//     matrix<double> m1(5,2), m2(3, 4);
//     for(int i = 1; i <= 5; i++)
//         for(int j = 1; j <= 2; j++)
//             m1(i, j) = 2;

//     for(int i = 1; i <= 3; i++)
//         for(int j = 1; j <= 4; j++)
//             m2(i, j) = 2;
//     cout << m1.transpose();
//     cout << "m1: " << endl << m1;
//     cout << "m2: " << endl << m2;
//     // matrix<int> m3 = m1*m2;
//     // cout << "m3: " << endl << m3 << endl;
// }