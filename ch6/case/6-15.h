#include<string>
#include<iostream>

using namespace std;

struct studentRecord
{
    int score;
    string* name;
    operator int(){ return score;}
    //从student到int的类型转换
};

ostream& operator<<(ostream& out, const studentRecord &x)
{
    out << x.score << ' ' << *x.name << endl;
    return out;
}