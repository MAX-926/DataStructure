#include<string>
#include<iostream>

struct studentRecord
{
    int score;
    std::string* name;
    int operator!=(const struct studentRecord &x)const{ return score != x.score;}
};

std::ostream& operator<<(std::ostream& out, const struct studentRecord &x)
{
    out << x.score << ' ' << *x.name << std::endl;
    return out;
}