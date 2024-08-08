//把一个字符串转换为不唯一的整数
#include<iostream>
using namespace std;

// int stringToInt(string s)
// {
//     int length = s.length();
//     int answer = 0;
//     if(length % 2 == 1)//如果长度为奇数
//     {
//         answer = s.at(length - 1);//取字符串的最后一位的ascii赋值给answer
//         length--;
//     }
//     //经过上部，长度从奇数转变为偶数
//     for(int i = 0; i < length; i += 2)
//     {//同时转换两个字符
//         answer += s.at(i);
//         answer += ((int) s.at(i+1)) << 8;
//     }
//     return (answer < 0) ? -answer : answer;
// }

int intToString(string s)
{
    int length = (int) s.length();
    int answer = 0;
    if(length % 2 == 1)
    {
        answer = s.at(length - 1);
        length--;
    }
    for(int i = 0; i < length - 1; i += 2)
    {
        answer += s.at(i);
        answer += ((int) s.at(i+1)) << 8;
    }
    return answer > 0 ? answer : -answer;
}

#include"../../ch8/case/8-4.cpp"
arrayStack<int> s;
int decToBinary(int num)
{//将10进制数转为2进制数
    while(num != 0)
    {
        s.push(num % 2);
        num /= 2;
    }
    return 0;
}

int main()
{
    decToBinary(356);
    while(!s.empty())
    {
        cout << s.top();
        s.pop();
    }
}