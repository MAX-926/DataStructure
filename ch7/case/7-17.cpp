#include"7-13.cpp"
using namespace std;

template<class T>
void sparseMatrix<T>::add(sparseMatrix<T> &b, sparseMatrix<T> &c)
{//计算*this + b = c
//检验相容性
    if(rows != b.rows || cols != b.cols)
        throw matrixSizeMimatch();
    //设置结果矩阵的特征
    c.rows = rows;
    c.cols = cols;
    c.terms.clear();
    int csize = 0;

    //定义*this和b的迭代器
    arrayList<matrixTerm<T>>::iterator it = terms.begin();
    arrayList<matrixTerm<T>>::iterator ib = b.terms.begin();
    arrayList<matrixTerm<T>>::iterator itEnd = terms.end();
    arrayList<matrixTerm<T>>::iterator iBEnd = b.terms.end();
      
}