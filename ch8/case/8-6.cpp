//输出匹配的括号
//从左到右扫描字符串，将遇到的左括号入栈，若遇到右括号，就将栈顶的左括号删除

#include<iostream>
#include"8-4.cpp"
using namespace std;

// void printMatchedPairs(string expr)
// {//括号匹配
//     arrayStack<int> s;
//     int length = (int)expr.size();
//     for(int i = 0; i < length; i++)
//         if(expr[i] == '{')
//             s.push(i);
//         else
//             if(expr[i] == '}')
//         try
//         {//从栈中删除匹配的左括号
//             cout << s.top() << ' ' << i << endl;
//             s.pop();
//         }catch(stackEmpty)
//         {//栈为空。没有匹配的左括号
//             cout << "No match for right parenthesis"
//                  << " at " << i << endl;
//         }
//     //栈不为空，剩余在栈中的左括号是不匹配的
//     while(!s.empty())
//     {
//         cout << "No match for left parenthesis at "
//              << s.top() << endl;
//         s.pop();
//     }
// }

/*
    int exprLength = expr.size();
    char* stack = new char[exprLength/2];
    int stackTop = -1;
    for(int i = 0; i < exprLength; i++)
    {
        if(expr[i] == '{')
            stack[++stackTop] = expr[i];
        if(expr[i] == '}')
        {
            if(stackTop != -1)
                --stackTop;
        }
    }
*/

void printMatchedPairs(string expr)
{
    int length = expr.size();
    int* stack = new int[length];
    int stackTop = -1;
    for(int i = 0; i < length; i++)
        if(expr[i] == '{')
            stack[++stackTop] = i;
        else
            if(expr[i] == '}')
                if(stackTop-1 == -2)
                    cout << "No match for right parenthesis at " << i << endl;
                else
                {
                    cout << "Matched pair at " << stack[stackTop] << ' ' << i << endl;
                    stackTop--;
                }
    while(stackTop > -1)
    {
        cout << "No match for left parenthesis at " << stack[stackTop--] << endl;
    }
}

int main()
{
    string s = "{a*{b+c}+d}";
    printMatchedPairs(s);
}