//LZW algorithm

/*
table
a->0 b->1

input = abaaab

previous = null
current = a

p = p+c = a
a is in table, so
p = a



*/

#include<iostream>
#include"hashChains.h"
using namespace std;

// void LZW(string s)
// {
//     //初始化词根字典
//     hashChains<string, int> table;
//     table.insert(pair<string, int>("a", 0));
//     table.insert(pair<string, int>("b", 1));

//     int tag = 2;
//     string p, c;
//     int length = s.length();
//     for(int i = 0; i < length;)
//     {//扫描s的每一个字符
//         c = s[i];
//         if(table.find(p+c) != nullptr && table.find(p+c)->first == p+c)
//         {//在字典中存在当前序列
//             // cout << table.find(c)->second;
//             p = p+c;
//             i++;
//         }
//         else//在字典中没有记录该序列
//         {
//             table.insert(pair<string, int>(pair<string, int>(p + c, tag++)));
//             cout << table.find(p)->second;
//             p = s[i++];
//         }
//     }
// }


void LZW(string s)
{//输出对s的压缩结果
    int length = s.length();
    string p, c;
    hashChains<string, int> table;
    //对字母表进行初始化
    //假设仅有a、b两个元素
    table.insert(pair<string, int>("a", 0));
    table.insert(pair<string, int>("b", 1));
    int tag = 2;
    //对s进行压缩处理
    for(int i = 0; i < length; i++)
    {
        c = s[i];
        pair<const string, int>* pointer = table.find(p+c);
        if(pointer != nullptr && pointer->first == p + c)
        {
            p = p + c;
            if(i == length - 1)
            {
                cout << table.find(p)->second;
            }
        }
        else
        {
            table.insert(pair<string, int>(p+c, tag++));
            cout << table.find(p)->second;
            if(i == length - 1)
            {
                cout << table.find(p + c)->second;
            }
            p = c;
        }
    }
    // cout << "below is table:\n" << table;
}

int main()
{
    string s = "aaabbbbbbaabaaba";
    LZW(s);
    // hashChains<string, int> table;
    // table.insert(pair<string, int>("a", 0));
    // table.insert(pair<string, int>("b", 1));
    // cout << (table.find("ab") == nullptr);

}