#include<iostream>
#include"ch8/case/8-4.cpp"
#include"ch9/case/9-2.cpp"
using namespace std;

void searchEquivalenceClasses()
{//寻找等价类，并输出
    int n, r;
    cout << "Enter numer of elements:\n";
    cin >> n;

    cout << "Enter numer of relationss:\n";
    cin >> r;

    arrayStack<int> list[n + 1];

    int a, b;
    for(int i = 0; i < r; i++)
    {
        cout << "Enter new relation-pairs:\n";
        cin >> a >> b;
        list[a].push(b);
        list[b].push(a);
    }
    //寻找等价类
    bool out[n+1];
    arrayQueue<int> unprocessedList;
    // arrayStack<int> unprocessedList;
    for(int i = 1; i <= n; i++)
        out[i] = false;
    for(int e = 1; e <= n; e++)
    {
        if(!out[e])
        {
            cout << "New class:\n";
            out[e] = true;
            cout << e << " ";
            unprocessedList.push(e);
            while(!unprocessedList.empty())
            {
                // int topE = unprocessedList.top();
                int topE = unprocessedList.front();
                // out[topE] = true;
                unprocessedList.pop();
                while(!list[topE].empty())
                {
                    int q = list[topE].top();
                    list[topE].pop();
                    if(!out[q])
                    {
                        out[q] = true;
                        unprocessedList.push(q);
                        cout << q << " ";
                    }
                }
            }
            cout << endl;
        }
    }
}

int main()
{
    searchEquivalenceClasses();
}