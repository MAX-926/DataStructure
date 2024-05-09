#ifndef CURRENCY_H
#define CURRENCY_H
#include<iostream>
#include"myExceptions.h"
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
    cout << cents;
}

#endif // CURRENCY_H