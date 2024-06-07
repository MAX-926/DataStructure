#include"43.cpp"

template<class T>
void split(doublyLinkedList<T> &a, doublyLinkedList<T> &b, const doublyLinkedList<T> &c)
{//a中包含索引为奇数的元素，b包含其它元素
    int index = 0;
    int lsC = c.size();
    auto iterC = c.begin();
    while(index < lsC)
    {
        if(index % 2 != 0)
        {
            a.push_back(*(iterC++));
            index++;
        }
        else
        {
            b.push_back(*(iterC++));
            index++;
        }
    }
    return;
}

template<class T>

int main()
{
    doublyLinkedList<int> a, b, c;
    for(int i = 0; i < 1; i++)
        c.insert(i, i);
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
    split(a, b, c);
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
}