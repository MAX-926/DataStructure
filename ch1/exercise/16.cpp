// 拓展程序1-13的类Currency， 添加下列成员函数：
// 1) input()从标准输入流中读取Currency的值， 然后赋给调用对象。

// 2) subtract(x)从调用对象中减去参数对象x的值， 然后返回结果。

// 3) percent(x)返回一个Currency类的对象， 它的值是调用对象的x%。x的数据类型为doulble。

// 4) multiply(x)返回一个Currency类的对象， 它的值是调用对象和double型数x的乘积。

// 5) divide(x)返回一个Currency类的对象， 它的值是调用对象除以double型数x的结果。

// 实现所有成员函数， 用适当的数据检验它们的正确性。

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
        signType getSign()const{return sign;}
        unsigned long getDollars()const{return dollars;}
        unsigned int getCents()const{return cents;}
        Currency add(const Currency&) const;
        Currency& increment(const Currency&);
        void output()const;
        // 1) input()从标准输入流中读取Currency的值， 然后赋给调用对象。
        void input(void){double in; cin >> in; setValue(in); return;}
        // 2) subtract(x)从调用对象中减去参数对象x的值， 然后返回结果。
        double subtract(const Currency& x)
        {
            long a1, a2, a3;
            a1 = dollars*100 + cents;
            if(sign == '-') a1 = -a1;
            a2 = x.dollars*100 + x.cents;
            if(x.sign == '-') a2 = -a2;
            a3 = a1 - a2;
            if(a3 < 0) {sign = '-'; a3 = -a3;}
            else sign = '+';
            dollars = (unsigned long)(a3 / 100);
            cents = (unsigned int) (a3 - dollars* 100 + 0.001);
            return dollars + cents / 100;
        }
        // 3) percent(x)返回一个Currency类的对象， 它的值是调用对象的x%。x的数据类型为doulble。
        Currency percent(double x)const
        {
            double theAmount;
            unsigned int theCents;
            if(x > 0 && x < 1)
            { 
                theAmount = x * (dollars + cents / 100);
                theCents = theAmount * 100 - ((unsigned long)theAmount * 100);
                return Currency(sign, (unsigned long)theAmount, cents);
            }
            else throw valueError("Needed a value that is not out of range(0, 1)");
        }
        // 4) multiply(x)返回一个Currency类的对象， 它的值是调用对象和double型数x的乘积。
        Currency multiply(double x)const
        {
            double theAmount = dollars + cents / 100;
            theAmount *= x;
            char s;
            if(theAmount < 0)
            {
                s = '-';
                theAmount = -theAmount;
            }
            else s = '+';
            unsigned long theDollars = (unsigned long)theAmount;
            unsigned int theCents = (unsigned int)(theAmount - (unsigned long)theAmount + 0.001) * 100;
            return Currency(s, theDollars, theCents);
        }
        // 5) divide(x)返回一个Currency类的对象， 它的值是调用对象除以double型数x的结果。
        Currency divide(double x)
        {
            double a1;
            a1 = dollars + cents / 100;
            if(sign == '-') a1 = -a1;
            a1 /= x;
            if(a1 < 0) {sign = '-'; a1 = -a1;}
            else sign = '+';
            a1 *= 100;
            dollars = (unsigned long)(((unsigned long) a1) / 100);
            cents = (unsigned int) ((unsigned long)a1 - dollars * 100);
            return Currency(sign, dollars, cents);
        }
    private:
        signType sign;// 对象的符号
        unsigned long dollars;// 美元的数量
        unsigned int cents;// 美分的数量
};

template<class signType>
Currency<signType>::Currency(signType theSign, unsigned long theDollars, unsigned int theCents)
{
    setValue(theSign, theDollars, theCents);
}

template<class signType>
void Currency<signType>::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
    if(theCents > 99) //美分太多
        throw illegalParameterValue("Cents should be < 100");
    sign = theSign;
    dollars = theDollars;
    cents = theCents;
}

template<class signType>
void Currency<signType>::setValue(double theAmount)
{// 给调用对象的数据成员赋值
    if(theAmount < 0) {sign = '-'; theAmount = -theAmount;}
    else sign = '+';
    dollars = (unsigned long) theAmount;// 提取整数部分
    cents = (unsigned int) (theAmount - dollars + 0.001) * 100;// 提取两位小数
}

template<class signType>
Currency<signType> Currency<signType>::add(const Currency<signType>& x)const
{//把x和*this相加
    long a1, a2, a3;
    Currency<signType> result;
    // 把调用对象转化为符号整数
    a1 = dollars * 100 + cents;
    if(sign == '-') a1 = -a1;
    // 把x转化为符号整数
    a2 = x.dollars * 100 + x.cents;
    if(x.sign == '-') a2 = -a2;
    a3 = a1 + a2;

    // 转化为Currency对象的表达形式
    if(a3 < 0) {result.sign = '-'; a3 = -a3;}
    else result.sign = '+';
    result.dollars = a3 / 100;
    result.cents = a3 - result.dollars * 100;

    return result;
}

template<class signType>
Currency<signType>& Currency<signType>::increment(const Currency<signType>& x)
{// 增加x
    // long a1, a2;
    // a1 = dollars * 100 + cents;
    // if(sign == minus) a1 = -a1;
    // a2 = x.dollars * 100 + x.cents;
    // if(x.sign == minus) a2 = -a2;
    *this = add(x);
    return *this;
}

template<class signType>
void Currency<signType>::output()const
{// 输出调用对象的值
    if(sign == '-') cout << '-';
    cout << '$' << dollars << '.';
    if(cents < 10) cout << '0';
    cout << cents << endl;
}

int main(void)
{
    Currency<char> c1, c2, c3;
    c1.setValue(30);
    c2.setValue(25);
    c3.setValue(5);
    // c1.input();
    // c3.subtract(c2);
    // c1.percent(0.2).output();
    // c4.output();
    // c3.output();
    // c1.multiply(-5).output();
    // c1.divide(4).output();
}