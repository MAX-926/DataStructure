//判定字符串中是否有不匹配的括号，不使用栈
//我的双指针法：从串的两端遍历的错误原因在于算法给出的匹配成功可能是假性的，如{{}{}}，算法会给出匹配失败，
//因为算法错误的将第二位置的左括号与第5位置的右括号进行了匹配，实际上第二位置的左括号应该和与它最接近的第三位置的右括号进行匹配
//这里用计数器抓取异常匹配
//航船法？！
#include<iostream>
using namespace std;

bool hasMismatchPairs(string str)//O(len),算法需要对每一个元素进行检查
{//若匹配成功返回false，匹配失败返回true
    int numOfL = 0;//安全标准海平面
    int len = str.length();//查找次数
    for(int i = 0; i < len; i++)//O(len)
    {
        if(str[i] == '{')
            numOfL++;//船上升
        if(str[i] == '}')
            numOfL--;//船下降
        if(numOfL < 0)//若果船低于安全的水位线，即多了一个右括号时，匹配失败
        {
            cout << "Has mismatch R pairs, shutdown immediately\n";
            return true;
        }
    }
    if(numOfL != 0)//船什天了！不可能的case，即左括号过多，匹配失败
    {
        cout << "Has mismatch L pairs\n";
        return true;
    }
    cout << "Has no mismatch pairs\n";
    return false;
}

int main()
{
    string str = "}{{}{}}{";
    cout << hasMismatchPairs(str);
}