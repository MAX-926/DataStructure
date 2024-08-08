#include<iostream>
using namespace std;

// template<>
// class hash<string>
// {
//     public:
//         size_t operator()(const string s)const
//         {
//             int length = s.length();
//             unsigned long hashValue = 0;
//             for(int i = 0; i < length; i++)
//             {
//                 hashValue = 5*hashValue + s.at(i);
//             }
//             return (size_t) hashValue;
//         }
// };

//一个将string数据映射成size_t类型数据的函数
size_t hashFunc(string s)
{
    int length = s.length();
    unsigned long hashValue = 0;
    for(int i = 0; i < length; i++)
        hashValue = 5*hashValue + s.at(i);
    return (size_t) hashValue;
}

// int main()
// {
//     cout << hashFunc("ab");

// }