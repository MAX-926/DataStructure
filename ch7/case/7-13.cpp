#include<iostream>
#include"../../Tool.h"
#include"../../ch5/case/5-11.cpp"
using namespace std;

template<class T>
struct matrixTerm
{
    // terms(int i, int j, const T& theValue){this->i = i; this->j = j; value = theValue;}
    matrixTerm<T>& operator=(const matrixTerm<T>& mt)
    {
        row = mt.row;
        col = mt.col;
        value = mt.value;
        return *this;
    }
    int row;
    int col;
    T value;
};
//类sparseMatrix唯一的构造函数为缺省构造函数
template<class T>
class sparseMatrix
{
    public:
        void transpose(sparseMatrix<T> &b);
        void add(sparseMatrix<T> &b, sparseMatrix<T> &c);
        friend ostream& operator<<(ostream&, sparseMatrix<T>&);
        friend istream& operator>>(istream&, sparseMatrix<T>&);
    private:
        int rows;
        int cols;
        arrayList<matrixTerm<T>> terms;
};

// template<class T>
// ostream& operator<<(ostream& out, sparseMatrix<T> &x)
// {//将x放入输出流

// //输出矩阵特征
//     out << "rows = " << x.rows << " columns = " << x.cols << endl;
//     out << "nonzero terms = " << x.terms.size() << endl;

//     //输出矩阵项，一行一个
//     for(arrayList<matrixTerms<T>>::iterator i = x.terms.begin();
//         i != x.terms.end(); i++ )
//         out << "a(" << (*i).row << ',' << (*i).col << ") = " << (*i).value << endl;
//     return out;
//     // for(int i = 0; i < x.terms.size(); i++)
//     //     out << x.terms.element[i] << endl;
// }

template<class T>
ostream& operator<<(ostream& out, sparseMatrix<T>& b)
{
    //输出矩阵特征
    out << "row, column, and #terms" << endl;
    out << b.rows << " " << b.cols << " " << b.terms.size() << endl;

    //输出矩阵项
    for(arrayList<matrixTerm<T>>::iterator i = b.terms.begin(); i != b.terms.end(); i++)
        out << "a(" << (*i).row << "," << (*i).col << ") = " << (*i).value << endl;
    return out;  
}

// template<class T>
// istream& operator>>(istream& in, sparseMatrix<T> &x)
// {//输入一个稀疏矩阵

//     //输入矩阵特征
//     int numberOfTerms;
//     cout << "Enter number of rows, columns, and #terms"
//          endl;
//     in >> x.rows >> x.cols >> numberOfTerms;
//     //这里应该检验输入的合法性
//     if(numberOfTerms > rows*cols/3 || numberOfTerms < 1)
//         throw IllegalParameter("not a sparse matrix");
//     //设置x.terms的大小，确保足够的容量
//     x.terms.reSet(numberOfTerms);
//     //输入项
//     matrixTerm<T> mTerm;
//     for(int i = 0; i < numberOfTerms; i++)
//     {
//         cout << "Enter row, column, and value of term"
//              << (i+1) << endl;
//         in >> mTerm.row >> mTerm.col >> mTerm.value;
//         //这里应该检验输入的合法性
//         if(x.rows < mTerm.row || x.cols < mTerm.col || mTerm.row < 1 || mTerm.col < 1)
//             throw matrixIndexOutOfBounds();
//         x.terms.set(i, mTerm);
//     }
//     return in;
// }

template<class T>
istream& operator>>(istream& in, sparseMatrix<T> &b)
{
    //输入矩阵特征
    int numberOfTerms = 0;
    cout << "Enter matrix row, column and number of terms\n";
    in >> b.rows >> b.cols >> numberOfTerms;
    if(numberOfTerms < 0 || numberOfTerms > b.rows*b.cols/3)
        throw illegalParameter("not a sparseMatrix");
    b.terms.reSet(numberOfTerms);
    //输入矩阵项
    matrixTerm<T> mt;
    for(int i = 0; i < numberOfTerms; i++)
    {
        cout << "Enter matrixTerm row, col and value\n";
        in >> mt.row >> mt.col >> mt.value;
        if(mt.row < 1 || mt.col < 1 || mt.row > b.rows || mt.col > b.cols)
            throw matrixIndexOutOfBounds();
        b.terms.set(i, mt);
    }
    return in;
}

// template<class T>
// void sparseMatrix<T>::transpose(sparseMatrix<T> &b)
// {//返回b中*this的转置
//     //设置矩阵特征
//     b.rows = cols;
//     b.cols = rows;
//     b.terms.reSet(terms.size());
//     //初始化已实现转置
//     int* colSize = new int[cols+1];
//     int* rowNext = new int[cols+1];
//     //寻找*this中每一列项的数目
//     for(int i = 1; i <= cols; i++) //初始化
//         colSize[i] = 0;
//     for(arrayList<matrixTerm<T>>::iterator i = terms.begin();
//         i != terms.end(); i++)
//         colSize[(*i).col]++;
//     //寻找b中每一行的起始点
//     rowNext[1] = 0;
//     for(int i = 2; i <= cols; i++)
//         rowNext[i] = rowNext[i-1] + colSize[i-1];
//     //实施从*this到b的转置复制
//     matrixTerm<T> mTerm;
//     for(arrayList<matrixTerm<T>>::iterator i = terms.begin();
//         i != terms.end(); i++)
//     {
//         int j = rowNext[(*i).col]++;//b中的位置
//     }
// }

template<class T>
void sparseMatrix<T>::transpose(sparseMatrix<T> &b)
{
    //打造容器
    b.rows = cols;
    b.cols = rows;
    b.terms.reSet(terms.size());
    //为了搬运元素，需要知道转置后元素的起点（需要知道每一列前面有几个元素）
    int* colSize = new int[cols + 1];
    int* rowNext = new int[cols + 1];

    for(int i = 1; i <= cols; i++)
        colSize[i] = 0;
    for(arrayList<matrixTerm<T>>::iterator i = terms.begin(); i != terms.end(); i++)
        colSize[(*i).col]++;
    //寻找b中每一行的起点（rowNext为起点矩阵）
    rowNext[1] = 0;
    for(int i = 2; i <= cols; i++)
        rowNext[i] = rowNext[i-1] + colSize[i-1];
    //*this实施从*this到b的转置复制
    matrixTerm<T> mTerm;
    for(arrayList<matrixTerm<T>>::iterator i = terms.begin(); i != terms.end(); i++)
    {
        int j = rowNext[(*i).col]++;
        mTerm.row = (*i).col;
        mTerm.col = (*i).row;
        mTerm.value = (*i).value;
        b.terms.set(j, mTerm);
    }
    return;
}