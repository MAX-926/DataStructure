//对STL的copy函数的一种可行的代码
template<class iterator>
void copy(iterator start, iterator end, iterator to)
{
    while(start != end)
    {*to = *start; start++; to++;}
}