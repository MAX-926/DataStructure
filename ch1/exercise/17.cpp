// 1) input()从标准输入流中读取Currency的值， 然后赋给调用对象。

// 2) subtract(x)从调用对象中减去参数对象x的值， 然后返回结果。

// 3) percent(x)返回一个Currency类的对象， 它的值是调用对象的x%。x的数据类型为doulble。

// 4) multiply(x)返回一个Currency类的对象， 它的值是调用对象和double型数x的乘积。

// 5) divide(x)返回一个Currency类的对象， 它的值是调用对象除以double型数x的结果。

// 实现所有成员函数， 用适当的数据检验它们的正确性。
#define CURRENCY_H
#include<iostream>
#include"../case/myExceptions.h"
using namespace std;

template<class signType>
// #define signType char
class Currency
{
    public:
        // 构造函数
        Currency(signType theSign = '+', unsigned long theDollars = 0, unsigned int theCents = 0);
        // 析构函数
        ~Currency(){}
        void setValue(signType, unsigned long, unsigned int);
        void setValue(double);
        signType getSign()const{if(amount < 0) return '-'; else return '+';}
        unsigned long getDollars()const{if(amount < 0) return (-amount) / 100;else return amount / 100;}
        unsigned int getCents()const{if(amount < 0) return (-amount) - getDollars() * 100; else return amount - getDollars() * 100;}
        Currency add(const Currency&) const;
        Currency& increment(const Currency& x){amount += x.amount; return *this;}
        void output()const;
        // input()
        void input(void)
        {
            double theAmount;
            cin >> theAmount;
            setValue(theAmount);
        }
        // subtract()
        double subtract(const Currency& cc)
        {
            char theSign;
            double theAmount = cc.amount / 100;
            if(theAmount<0)
            {
                theSign = '+';
                theAmount = -theAmount;
            }
            else theSign = '-';
            unsigned long theDollars = (unsigned long) theAmount;
            unsigned int theCents = (unsigned int) ((theAmount - theDollars) * 100);
            add(Currency(theSign, theDollars, theCents));
            if(theSign == '-') 
                return -(theDollars + theCents / 100);
            else
                return theDollars + theCents / 100;
        }
        // percent(x)返回一个Currency类的对象， 它的值是调用对象的x%。x的数据类型为doulble。
        Currency percent(double x)
        {
            double c = amount;         
            if(getSign() == '-') c = -c;
            c *= x;
            unsigned long theDollars = (unsigned long) c;
            unsigned int theCents = (unsigned int) ((c - theDollars) * 100);
            char theSign;
            if(c < 0) theSign = '-';
            else theSign = '+';
            return Currency(theSign, theDollars, theCents);
        }
        // Currency multiply(double x)
        Currency multiply(double x)
        {

        }
    private:
        long amount;
};

template<class signType>
Currency<signType>::Currency(signType theSign, unsigned long theDollars, unsigned int theCents)
{// 创建一个Currency类对象
    setValue(theSign, theDollars, theCents);
}

template<class signType>
void Currency<signType>::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{// 给调用对象赋值
    if(theCents > 99) //美分太多
        throw illegalParameterValue("Cents should be < 100");
    amount = theDollars * 100 + theCents; // 构造差异处！！！
    if(theSign == '-') amount = -amount;
    // sign = theSign;
    // dollars = theDollars;
    // cents = theCents;
}

template<class signType>
void Currency<signType>::setValue(double theAmount)
{// 给调用对象的数据成员赋值
    // if(theAmount < 0) {sign = '-'; theAmount = -theAmount;}
    // else sign = '+';
    // dollars = (unsigned long) theAmount;// 提取整数部分
    // cents = (unsigned int) (theAmount - dollars + 0.001) * 100;// 提取两位小数
    if(theAmount < 0) amount = (long)((theAmount - 0.001) * 100);
    else amount = (long)((theAmount + 0.001) * 100);
                // 取两个十位数（？？？）
}

template<class signType>
Currency<signType> Currency<signType>::add(const Currency<signType>& x)const
{//把x和*this相加
    // long a1, a2, a3;
    Currency<signType> result;
    // // 把调用对象转化为符号整数
    // a1 = dollars * 100 + cents;
    // if(sign == '-') a1 = -a1;
    // // 把x转化为符号整数
    // a2 = x.dollars * 100 + x.cents;
    // if(x.sign == '-') a2 = -a2;
    // a3 = a1 + a2;

    // // 转化为Currency对象的表达形式
    // if(a3 < 0) {result.sign = '-'; a3 = -a3;}
    // else result.sign = '+';
    // result.dollars = a3 / 100;
    // result.cents = a3 - result.dollars * 100;
    result.amount = amount + x.amount;

    return result;
}

// template<class signType>
// Currency<signType>& Currency<signType>::increment(const Currency<signType>& x)
// {// 增加x
//     // long a1, a2;
//     // a1 = dollars * 100 + cents;
//     // if(sign == minus) a1 = -a1;
//     // a2 = x.dollars * 100 + x.cents;
//     // if(x.sign == minus) a2 = -a2;
//     *this = add(x);
//     return *this;
// }

template<class signType>
void Currency<signType>::output()const
{// 输出调用对象的值
    long theAmount = amount;
    if(theAmount < 0) {cout << '-'; theAmount = -theAmount;}
    long dollars = theAmount / 100;// 美元
    cout << '$' << dollars << '.';
    int cents = theAmount - dollars * 100;// 美分
    if(cents < 10) cout << '0';
    cout << cents;
}

int main(void)
{
    Currency<char> c1, c2, c3;
    c1.setValue(15.51);
    c2.setValue(-12.38);
    c3.setValue(10);
    c1.add(c2).output();
    // cout << c1.subtract(c2);
}