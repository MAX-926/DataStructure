//所有解决离线等价类的程序，对每一个关系和元素都至少考察一次，所以用时不可能少于O(n+r)，其中n为元素个数，r为关系个数
//寻找等价类：借助数组栈（数组线性表中数组栈的性能更好，而链式结构在插入与删除上的性能不敌数组结构）
//程序分两步
//一：根据输入(elements, relationsPairs, relationsNums)建立elements个关系列表
//二：寻找等价类

// #include<iostream>
// #include"8-4.cpp"
// using namespace std;

// int main()
// {
//     int n,//元素个数
//         r;//关系数目
//     cout << "Enter number of elements" << endl;
//     cin >> n;
//     if(n < 2)
//     {
//         cout << "Too few elements" << endl;
//         return 1;
//     }
//     cout << "Enter number of relations" << endl;
//     cin >> r;
//     if(r < 1)
//     {
//         cout << "Too few relations" << endl;
//         return 1;
//     }
//     //建立空栈组成的数组,stack[0]不用
//     arrayStack<int>* list = new arrayStack<int>[n+1];

//     //输入r个关系，存储在表中
//     int a, b;//(a, b)是一个关系
//     for(int i = 1; i <= r; i++)
//     {
//         cout << "Enter next relation/pair" << endl;
//         cin >> a >> b;
//         list[a].push(b);
//         list[b].push(a);
//     }

//     //初始化以输出等价类
//     arrayStack<int> unprossedList;
//     bool* out  = new bool[n+1];//判断元素是否已从unprossedList中删除
//     for(int i = 1; i <= n; i++)
//         out[i] = false;
//     //输出等价类
//     for(int i = 1; i <= n; i++)
//     {
//         if(!out[i])
//         {//启动一个新类
//             cout << "Next class is " << i << endl;
//             out[i] = true;
//             unprossedList.push(i);
//             //从unprocessedList中取类的剩余元素
//             while(!unprossedList.empty())
//             {
//                 int j = unprossedList.top();
//                 unprossedList.pop();
//                 //表list[j]中的元素属于同一类
//                 while(!list[j].empty())
//                 {
//                     int q = list[j].top();
//                     list[j].pop();
//                     if(!out[q])
//                     {
//                         cout << q << " ";
//                         out[q] = true;
//                         unprossedList.push(q);
//                     }
//                 }
//             }
//         }
//         cout << endl;
//     }
//     cout << "End of list of equivalence classes" << endl;
//     return 0;
// }

#include<iostream>
#include"8-4.cpp"
using namespace std;

int main()//考虑异常为O(n+r)，无异常为θ(n+r)
{
    int n,
        r;
    cout << "Enter number of elements:\n";
    cin >> n;
    if(n < 2)
    {
        cout << "Too few elements\n";
        return 1;
    }
    cout << "Enter number of relations:\n";
    cin >> r;
    if(r < 1)
    {
        cout << "Too few relations:\n";
        return 1;
    }
    //创建关系列表,list[0]弃用
    arrayStack<int>* list = new arrayStack<int>[n+1];//O(n)
    //输入关系
    int a, b;
    for(int i = 1; i <= r; i++)//O(r)
    {
        cout << "Enter next relations:\n";
        cin >> a >> b;
        list[a].push(b);//O(1)
        list[b].push(a);//O(1)
    }
    //寻找等价类
    arrayStack<int> unprossedList;//O(1)
    bool* out = new bool[n+1];//O(1)?,不会超过O(n)
    for(int i = 1; i <= n; i++)//O(n)
        out[i] = false;//O(1)
    // for(int i = 1; i <= n; i++)
    // {
    //     if(!out[i])
    //     {
    //         cout << "New class: " << i << " ";
    //         unprossedList.push(i);
    //         out[i] = true;
    //         while(!unprossedList.empty())
    //         {
    //             int j = unprossedList.top();
    //             unprossedList.pop();
    //             //寻找j的同类
    //             while(!list[j].empty())
    //             {
    //                 int q = list[j].top();
    //                 list[j].pop();
    //                 if(!out[q])
    //                 {
    //                     cout << q << " ";
    //                     out[q] = true;
    //                     unprossedList.push(q);
    //                 }
    //             }
    //         }
    //     }
        // cout << endl;
    // }
    // cout << "End of list of equivalence classes\n";
    // return 0;
    for(int i = 1; i <= n; i++)//O(n)
    {
        if(!out[i])//O(1)
        {
            cout << "New classes: " << i << " ";//O(1)
            out[i] = true;//O(1)
            unprossedList.push(i);//O(1)
            while(!unprossedList.empty())
            {
                int j = unprossedList.top();//O(1)
                unprossedList.pop();//O(1)
                while(!list[j].empty())
                {
                    int q = list[j].top();//O(1)
                    list[j].pop();//O(1)
                    if(!out[q])//O(1)
                    {
                        cout << q << " ";//O(1)
                        out[q] = true;//O(1)
                        unprossedList.push(q);//O(1)
                    }
                }
            }
        }
        cout << endl;//O(1)
    }
    cout << "End of list of equivalence classes\n";//O(1)
    return 0;//O(1)
}


//2,3 1,4 4,5
//1,4,5 2,3