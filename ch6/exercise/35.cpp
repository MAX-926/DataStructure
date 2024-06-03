#include"29.cpp"
#include<iostream>
#include<time.h>
#include<fstream>

template<class T>
void split(circularList<T> &a, circularList<T> &b, const circularList<T> &c)//要注意輸入的初始狀態！！
{
    if(a.size()) a.clear();//O(a.listSize)
    if(b.size()) b.clear();//O(b.listSize)
    if(!c.size()) return;//O(1)
    int indexC = 0;//O(1)
    while(indexC < c.size())//O(c.listSize)
    {
        if(indexC % 2 != 0)//O(1)
        {
            a.push_back(c.get(indexC++));//O(indexC)
        }
        else
        {
            b.push_back(c.get(indexC++));//O(indexC)
        }
    }
    return;
}

// int main()
// {
//     circularList<int> a, b, c;
//     for(int i = 0; i < 10; i++)
//     {
//         c.insert(i, i+1);
//         a.insert(i, -1);
//         b.insert(i, -2);
//     }
//     std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
//     split(a, b, c);
//     std::cout << "a:" << a << std::endl << "b:" << b << std::endl << "c:" << c << std::endl;
// }

int main()
{
    std::ofstream out("35_Test.txt"); 
    circularList<int> a, b, c;
    time_t clocksPerMillis = CLOCKS_PER_SEC / 1000;
    int steps = 100;
    int numsOfRepetions = 0;
    // std::cout << "n:" << '\t' << "clocks:" << '\t' << "Time cost per split:\n";
    out << "n:" << '\t' << "clocks:" << '\t' << "Time cost per split:\n";
    for(int n = 0; n < 100000; n += steps)
    {
        numsOfRepetions = 0;
        time_t startTime = clock();
        do
        {
            numsOfRepetions++;
            for(int i = 0; i < n; i++)
                c.insert(i, i);
            split(a, b, c);
        }while(clock() - startTime < 1000);
        double elapsedTime = (clock()-startTime)/clocksPerMillis;
        // std::cout << n << '\t' << elapsedTime << '\t' << elapsedTime/numsOfRepetions << std::endl;
        out << n << '\t' << elapsedTime << '\t' << elapsedTime/numsOfRepetions << std::endl;
        if(n == 1000) steps = 1000;
        if(n == 10000) steps = 10000;
    }
    out.close();
}