#include"29.cpp"

//编写一个循环链表的merge函数
template<class T>
void merge(const circularList<T> &a, const circularList<T> &b, circularList<T> &c)//best O(1) normal O(a.listSize + b.listSize)
{
    if(!(a.size() + b.size())) return;//O(1)
    if(!c.size()) c.clear();//O(c.listSize), 這步為準備工作
    if(!a.size())//O(b.listSize)
    {
        for(int i = 0; i < b.size(); i++)
            c.push_back(b.get(i));
        return;
    }
    if(!b.size())//O(a.listSize)
    {
        for(int i = 0; i < a.size(); i++)
            c.push_back(a.get(i));
        return;
    }
    //a, b皆非空, O(a.listSize + b.listSize)
    int len = 2*std::min(a.size(), b.size());
    int indexA = 0, indexB = 0;
    bool cross = true;
    for( ;indexA < a.size() && indexB < b.size();)
    {
        if(a.get(indexA) > b.get(indexB))
        {
            c.push_back(b.get(indexB++));
            continue;
        }
        else if(a.get(indexA) < b.get(indexB))
        {
            c.push_back(a.get(indexA++));
            continue;
        }
        else
        {
            if(cross)
            {
                c.push_back(a.get(indexA++));
                cross = !cross;
                continue;
            }
            else
            {
                c.push_back(b.get(indexB++));
                cross = !cross;
                continue;
            }
        }
    }
    while(indexA < a.size())
        c.push_back(a.get(indexA++));
    while(indexB < b.size())
        c.push_back(b.get(indexB++));
}

int main()
{
    circularList<int> a, b, c;
    for(int i = 0; i < 1; i++)
    {
        a.insert(i, i+3);
    }
    for(int i = 0; i < 0; i++)
    {
        b.insert(i, i+1);
    }
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl;
    try{merge<int>(a, b, c);}catch(IllegalParameter ip){ip.outputMessage();}
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl;
    std::cout << "c:" << c << std::endl;
}