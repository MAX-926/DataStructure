//将程序10-13得到的的整数转换为字符串

#include<iostream>
using namespace std;
//10-13
long threeToLong(string s)
{
    long answer = s.at(0);
    //移位存入信息
    answer = (answer << 8) + s.at(1);
    //移位存入信息
    return (answer << 8) + s.at(2);
}
#include<math.h>
#include"../../ch9/case/9-2.cpp"

string intToThree(long num)
{
    string answer;
    int plusor;
    char chs[3];
    int index = 0;
    int count = 0;
    arrayQueue<int> q;
    //现将整数转成二进制信息
    while(num != 0)
    {
        count++;
        q.push(num % 2);
        num /= 2;
    }
    while(count < 24)
    {
        count++;
        q.push(0);
    }
    for(int i = 0; i < 3; i++)
    {
        char ch = 0;
        for(int j = 0; j < 8; j++)
        {
            int term = pow(2, j);
            plusor = q.front();
            q.pop();
            ch += plusor*term;
        }
        chs[index++] = ch;
    }
    answer = answer + chs[2] + chs[1] + chs[0];
    return answer;
}

int main()
{
    // string s = "MAX'";
    // cout << intToThree(threeToLong(s));
    // cout << threeToLong(s);
    char ch = 'z';
    cout << (int)ch;
}