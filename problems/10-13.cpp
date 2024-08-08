#include<iostream>
#include<cmath>
using namespace std;

//stirng有字符组成，而一个字符占一字节空间，即8位空间
long threeToLong(string s)
{//假设s.length() >= 3
    //最左边的字符
    long answer = s.at(0);

    //左移9位，加入下一个字符
    answer = (answer << 8) + s.at(1);

    //左移9位，加入下一个字符
    return answer = (answer << 8) + s.at(2);
}//把信息编码在位里面：00000000 00000000 00000000，每一段对应一个字符的ascii码，即：97 98 99连着放，得到的数字映射到一个索引空间

int main()
{
    // string s = "abc";
    // long answer = s.at(0);
    // answer >>= 7; 
    // answer = (answer << 8) + s.at(1);
    // cout << answer;
    // cout << answer;
    // cout << pow(2, 3);
    string s = "abc";
    long a = s.at(0);//_ _ _ _
    // cout << sizeof(a);
    a = (a << 8) + s.at(1);
    a = (a << 8) + s.at(2);
    // cout << a;
    // cout << sizeof(a);//
}