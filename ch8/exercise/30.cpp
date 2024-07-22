//离线等价类问题
#include<iostream>
#include"../case/8-4.cpp"
using namespace std;

// void searchEqualClass()
// {
//     int num, 
//         relationsCount;
//     cout << "Enter elements num:\n";
//     cin >> num;
//     if(num < 2)
//     {
//         cout << "num should be > 1";
//         return;
//     }
//     cout << "Enter relationsCount:\n";
//     cin >> relationsCount;
//     if(relationsCount < 1)
//     {
//         cout << "Too few relation pairs\n";
//         return;
//     }
//     //S1：创建关系列表
//     // int* relationsMap = new int[relationsCount+1];
//     arrayStack<int>* relationsMap = new arrayStack<int>[num + 1];
//     int a, b;//(a, b)
//     for(int i = 0; i < relationsCount; i++)
//     {
//         cout << "Enter new relation pair:\n";
//         cin >> a >> b;
//         relationsMap[a].push(b);
//         relationsMap[b].push(a);
//     }
//     //S2:寻找等价类
//     arrayStack<int> unprocessedList;//可以穷尽要处理的数据域！！很重要的结构
//     bool* out = new bool[num+1];
//     for(int i = 1; i <= num; i++)
//         out[i] = false;
//     for(int i = 1; i <= num; i++)
//     {
//         if(!out[i])
//         {
//             cout << "new class:" << i << " ";
//             unprocessedList.push(i);
//             out[i] = 1;
//             while(!unprocessedList.empty())
//             {//当前类型没有处理完时
//                 int j = unprocessedList.top();
//                 unprocessedList.pop();
//                 while(!relationsMap[j].empty())
//                 {
//                     int q = relationsMap[j].top();
//                     relationsMap[j].pop();
//                     if(!out[q])
//                     {
//                         cout << q << " ";
//                         out[q] = true;
//                         unprocessedList.push(q);
//                     }
//                 }
//             }
//         }
//     }
//     cout << endl;
// }

void searchEquivalenceClasses()
{//寻找等价类
//S1：构建关系列表
    int n,//元素个数
        r;//关系个数
    cout << "Enter number of elements:\n";
    cin >> n;
    if(n < 2)
    {
        cout << "Too few elements\n";
        return;
    }
    cout << "Enter number of relation pairs\n";
    cin >> r;
    if(r < 1)
    {
        cout << "Too few relation pairs\n";
        return;
    }
    //创建关系列表
    //使用数组栈保存关系
    arrayStack<int>* list = new arrayStack<int>[n+1];//list[0]弃用
    int a, b;//(a, b)
    for(int i = 1; i <= r; i++)
    {
        cout << "Enter new relation pair\n";
        cin >> a >> b;
        list[a].push(b);
        list[b].push(a);
    }
    arrayStack<int> unprossedList;
    bool* out = new bool[n+1];
    for(int i = 1; i <= n; i++)
        out[i] = false;
    //寻找等价类
    for(int i = 1; i <= n; i++)
    {
        if(!out[i])
        {
            cout << "New class:\n";
            cout << i << " ";
            out[i] = true;
            unprossedList.push(i);
            while(!unprossedList.empty())
            {
                int j = unprossedList.top();
                unprossedList.pop();
                while(!list[j].empty())
                {
                    int q = list[j].top();
                    list[j].pop();
                    if(!out[q])
                    {
                        cout << q << " ";
                        out[q] = true;
                        unprossedList.push(q);
                    }
                }
            }
        }
        cout << endl;
    }
    cout << "End of equivalence classes search\n";
}

int main()
{
    searchEquivalenceClasses();
}