#include<iostream>
#include<fstream>
#include<string.h>
#include"hashChains.h"
using namespace std;

//字典有关数据
int DIVISOR = 4099;//divisor为素数
hashChains<long, short> h(DIVISOR);
//使用long，提供32位存储空间 > 12位前缀 + 8位后缀 = 20位空间；使用short，
//提供16位空间，为解压方便，所有的code都被设置为12位，short size > code size

//输入输出流
ifstream in;
ofstream out;

//输出有关数据
bool bitsLeftOver = false;
const int MASK1 = 255;//11 111 111
const int MASK2 = 15;//to binary:1 111
const int EXCESS = 4;
const int BYTE_SIZE = 8;

void setFiles(int argc, char* argv[]);

void compress();

void output();

// int main(int argc, char* argv[])
// {
//     cout << sizeof(long);
//     // setFiles();
//     // compress();
//     // output();
// }

void setFiles(int argc, char* argv[])
{//建立输入和输出流
    char outputFile[54], inputFile[50];
    //检查是否有文件地址
    if(argc >= 2)
        strcpy(inputFile, argv[1]);
    else
    {//没有文件名，要求提供文件名
        cout << "Enter name of file to compress\n";
        cin >> inputFile;
    }
    //打开二进制文件
    in.open(inputFile, ios::binary);
    if(in.fail())
    {
        cerr << "Cannot open " << inputFile << endl;
        exit(1);
    }
    strcpy(outputFile, inputFile);
    strcat(outputFile, ".zzz");
    out.open(outputFile, ios::binary);
}

void output(long pcode)//pcode是
{//输出8位，把剩余位保存
    int c, d;
    if(bitsLeftOver)
    {//把code的前8位
        d = int(pcode & MASK1);

    }
}

int main()
{
    int a = 9;
    for(int i = 0; i < 4; i++)
        cout << ((a >> i) & 1);
}
//011 001