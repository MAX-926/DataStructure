//寻找等价类
//1.生成关系列表
//2.寻找等价类

#include"ch8/case/8-4.cpp"
#include<iostream>

int searchEquivalenceClasses(int n, int r)
{
    if(n < 2)
    {
        cout << "Too few elements\n";
        return 1;
    }
    if(r < 1)
    {
        cout << "Too few relation-pairs\n";
        return 1;
    }
    //创建关系列表
    arrayStack<int> list[n+1];
    int a, b;
    for(int i = 0; i < r; i++)
    {
        cout << "Enter new relation-pairs:\n";
        cin >> a >> b;
        list[a].push(b);
        list[b].push(a);
    }

    arrayStack<int> unprocessedList;
    bool out[n+1] = {false, };
    //寻找等价类
    for(int i = 1; i <= n; i++)
    {//为每一个元素寻找等价类
        if(!out[i])
        {
            cout << "\nNew class:\n";
            cout << i << " ";
            out[i] = true;
            unprocessedList.push(i);
            while(!unprocessedList.empty())
            {
                int j = unprocessedList.top();
                unprocessedList.pop();
                while(!list[j].empty())
                {
                    int q = list[j].top();
                    list[j].pop();
                    if(!out[q])
                    {
                        unprocessedList.push(q);
                        out[q] = true;
                        cout << q << " ";
                    }
                }
            }
        }
    }
    cout << "search for equivalence classes complete\n";
}

int main()
{
    searchEquivalenceClasses(5, 3);
}