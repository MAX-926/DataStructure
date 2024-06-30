#include<string>
#include<iostream>
using namespace std;

struct studentRecord//这使得int()只在!=与<<之外生效
{
    int score;
    string* name;
    int operator!=(const studentRecord &x){return (score != x.score);}
    operator int()const{return score;}
};

ostream& operator<<(ostream& out, const studentRecord &x)
{
    out << x.score << ' ' << *x.name << endl;
    return out;
}