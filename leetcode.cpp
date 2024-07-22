#include<iostream>
#include<vector>
#include<stack>
using namespace std;

// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) 
//     {
//         vector<int> result;
//         for(int i = 0; i < nums.size()-1; i++)
//             for(int j = i+1; j <= nums.size()-1; j++)
//                 if(nums[i] +nums[j] == target)
//                 {
//                     result.push_back(i);
//                     result.push_back(j);
//                 }
//         return result;
//     }
// };


//回文针数
// class Solution {
// public:
//     bool isPalindrome(int x) 
//     {//括号匹配同类
//         stack<int> stack;
//         if(x < 0) return false;//负数一定不是回文针数
//         else if(x < 10) return true;
//         else if(x < 100)
//         {
//             if(x % 11 != 0) return false;
//             else return true;
//         }
//         else
//         {//括号匹配处理法
//          //对于位数为偶数的数
//             //先检查x的位数
//             int test = x;
//             int divisor = 10;
//             int times = 1;//次数
//             while(test / divisor != 0)
//             {
//                 divisor *= 10;
//                 times++;
//             }
//             // cout << "times = " << times;
//             //若x的位数不为偶数，则将x的位数调整为偶数
//             // int cutter;
//             if(times%2 != 0)
//             {//调整x为偶数位数
//                 int cutter = times/2;//cutter描述了可能相同回文数的对数，如12321，对数为2
//                 for(int i = 0; i < cutter; i++)//12321
//                     divisor /= 10;
//                 test /= divisor;
//                 test *= divisor;//利用整数除法的性质，将多余的位数归零
//                 test /= 10;
//                 //得到了左部
//                 divisor /= 10;
//                 int rPart = x % divisor;
//                 x = test + rPart;
//                 if(x < 100)
//                     if(x % 11 == 0) return true;
//                     else return false;
//             }
//             //检查是否为回文针数
//             x /= 10;
//             while(x > 9)
//             {
//                 int digit = x % 10;
//                 x /= 10;
//                 if(stack.empty())
//                     stack.push(digit);
//                 else
//                     if(digit == stack.top())
//                         stack.pop();
//                     else
//                         stack.push(digit);
//             }
//             // x < 10
//             if(!stack.empty())
//                 if(stack.top() == x)
//                     stack.pop();
//                 else
//                     stack.push(x);
//         }
//         if(stack.empty())
//             return true;
//         else return false;
//     }
// };

// class Solution {
// public:
//     bool isPalindrome(int x) {
//         long rem,rev,i=x;
//         cout << "firstTime: rev = " << rev << endl; 
//         while(i!=0){//将传入的整数倒着构建
//             rem=i%10;
//             rev=(rev*10)+rem;
//             i=i/10;
//         }
//         if((rev==x && rev >= 0)&&(rev < INT_MAX && rev > INT_MIN)){
//             return true;
//         }
//         else{
//             return false;
//         }
//     }
// };

class Solution
{
    public:
        bool isPalindrome(int x)
        {//扫描一遍数字，并将数字倒序构造，若得到的数字等于x且大于0，并且数字在允许的范围内，则返回true，否则返回false。算法用时O(x.length)
            long rev, rem, i = x;//初始状态rem，rev皆被初始化为0
            while(i != 0)
            {
                rem = i % 10;
                rev = rev*10 + rem;
                i /= 10;
            }
            // if(x == 0) return true;
            if((rev == x && rev >= 0 )&& (rev < INT_MAX && rev > INT_MIN))
                return true;
            else return false;
        }
};

int main()
{
    // func();
    Solution s;
    int n;
    while(1)
    {
        cin >> n;
        switch(s.isPalindrome(n))
        {
            case 0: cout << "False\n"; break;
            case 1: cout << "True\n";
        }
        
    }
}
