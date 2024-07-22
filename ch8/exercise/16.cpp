//寻找匹配的圆括号和匹配的方括号

#include<iostream>
#include"../case/8-4.cpp"
using namespace std;

void searchMatchedPairs(string str)
{//输入一个字符串，打印匹配的括号对
    int len = str.length();
    arrayStack<char> s;
    arrayStack<int> index;
    for(int i = 0; i < len; i++)//O(len)
    {
        if(str[i] == '(')//O(1)
        {
            index.push(i);
            s.push(str[i]);
        }
        else if(str[i] == '[')//O(1)
        {
            index.push(i);
            s.push(str[i]);
        }
        if(str[i] == ')')//O(1)
        {//检查栈顶元素是否匹配
            if(!s.empty())//O(1)
            {
                if(s.top() == '(')//O(1)
                {
                    cout << '(' << index.top() << ',' << i << ")" << endl;
                    index.pop();
                    s.pop();
                }
                else//O(1)
                {//mismatch
                    cout << "wrong match\n";
                    cout << "(" << index.top() << "," << i << ')' << endl;
                    index.pop();
                    s.pop();
                }
            }
            else
            {
                cout << "failed to match "
                     << "at elements " << i << endl;
                // return;
            }
        }
        else if(str[i] == ']')//O(1)
        {
            if(!s.empty())//O(1)
            {
                if(s.top() == '[')//O(1)
                {
                    cout << '(' << index.top() << ',' << i << ")" << endl;
                    index.pop();
                    s.pop();                
                }
                else//O(1)
                {//mismatch
                    cout << "wrong match\n";
                    cout << "(" << index.top() << "," << i << ')' << endl;
                    index.pop();
                    s.pop();
                }
            }
            else//O(1)
            {
                cout << "failed to match "
                     << "at elements " << i << endl;
                // return;
            }
        }
    }
}

int main()
{
    string str = "(a+[b*(c-d)+f])";
    string str1 = "(a+[b*(c-d)+f)])()";
    searchMatchedPairs(str1);
}