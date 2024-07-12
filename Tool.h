#ifndef TOOL_H
#define TOOL_H
#include<iostream>
#include<string>
using namespace std;

template<class T>
void output_2DArray(const T** x, int r, int c)
{
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
        {
            cout << x[i][j] << " ";
            if(j % (c-1) == 0 && j != 0)
                cout << endl;
        }
}

template<class T>
void output_2DArray_wideUse(T ** &x, int numberOfRows, int rowSize[])
{
    for(int i = 0; i < numberOfRows; i++)
    {
        for(int j = 0; j < rowSize[i]; j++)
            std::cout << x[i][j] << " ";
        std::cout << std::endl;
    }
}

template<class T>
void output_1dArray(T* ta, int size)
{
    for(int i = 0; i < size; i++)
        std::cout << ta[i] << " ";
}

template<class T>
bool make2dArray_withExc(T ** &x, int numberOfRows, int numberOfColumns)
{
    try
    {
        x = new T*[numberOfRows];
        for(int i = 0; i < numberOfRows; i++)
            x[i] = new T[numberOfColumns];
        return true;
    }
    catch(...){return false;}
}

template<class T>
void make2dArray(T ** &x, int numberOfRows, int numberOfColumns)
{
    x = new T*[numberOfRows];
    for(int i = 0; i < numberOfRows; i++)
        x[i] = new T[numberOfColumns];
}
// try{make2dArray(x, r, c)}
// catch(bad_alloc e){cerr << "Could not create x" << endl; exit(1);}

template<class T>
void delete2dArray(T ** &x, int numberOfRows, int numberOfColumns)
{
    for(int i = 0; i < numberOfRows; i++)
        delete []x[i];
    delete [] x;
    x = NULL;// 防止用户访问已回收的存储空间
    return;
}

template<class T>
void make2dArray_wideUse(T ** &x, int numberOfRows, int rowSize[])
{
    x = new T*[numberOfRows];
    for(int i = 0; i < numberOfRows; i++)
        x[i] = new T[rowSize[i]];
    return;
}

template<class T>
T* changeLength1D(T* &x, int oldLength, int newLength)
{
    if(oldLength == newLength) return 0;
    T* na = new T[newLength];
    for(int i = 0; i < (oldLength > newLength?newLength:oldLength); i++)
        na[i] = x[i];
    delete []x;
    return na;
}

// x:待变换矩阵， numberOfRows:待变换矩阵的行数， numberOfColumns:待变换矩阵的列数， y：目标矩阵的地址， newRows:目标矩阵的行数， rowSize:目标矩阵的列数矩阵
// template<class T>
// void changeLength2D(T ** &x,  int numberOfRows, int numberOfColumns, T** &y, int newRows, int rowSize[])
// {
//     make2dArray_wideUse(y, newRows, rowSize);
//     for(int i = 0; i < (newRows > numberOfRows?numberOfRows:newRows); i++)
//         for(int j = 0; j < (rowSize[i] > numberOfColumns?numberOfColumns:rowSize[i]); j++)
//             y[i][j] = x[i][j];
//     delete2dArray(x, numberOfRows, numberOfColumns);
// }

class illegalParameter
{
    public:
        illegalParameter(const string& theMsg = "illegalParameter"):msg(theMsg){}
        void showMsg(){cout << msg << endl;}
    private:
        string msg;
};

class matrixIndexOutOfBounds
{
    public:
        matrixIndexOutOfBounds(string s = "index out of bounds"){message = s;}
        void outputMessage()const{cout << message;}
    private:
        string message;
};

class matrixSizeMimatch
{
    public:
        matrixSizeMimatch(string s = "matrix size mismatch"):message(s){}
        void outputMessage(){cout << message;}
    private:
        string message;
};

class stackEmpty
{
    public:
        stackEmpty(string theMsg = "stack empty"):message(theMsg){}
        void outputMessage()const{cout << message << endl;}
    private:
        string message;
};

template<class T>
void __HeaderList_fluencyTest(const T& theObj)
{
    auto iter = theObj.end();
    int size = theObj.size();
    for(int i = 0; i < 2*size + 1; i++)
        std::cout << *(iter--) << " ";
    std::cout << std::endl;
}


#endif // TOOL_H ///:~