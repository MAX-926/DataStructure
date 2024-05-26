#include"../case/6-2.h"
#include<time.h>
#include"../../ch5/case/5-3.h"
using namespace std;

template<class T>
class chainListWithConverser:public chain<T>
{
    public:
        chainListWithConverser(int initialCapacity = 10):chain<T>(initialCapacity){}
        void fromList(const arrayList<T> &theList);
        arrayList<T>* toList()const;
};

template<class T>
void chainListWithConverser<T>::fromList(const arrayList<T> &theList)
{
    int theListSize = theList.size();
    if(theListSize == 0)//O(chainListSize)
    {
        while (this->firstNode)
        {
            chainNode<T>* nextNode = (this->firstNode)->next;
            delete (this->firstNode);
            (this->firstNode) = nextNode;
        }
        this->listSize = 0;
        this->firstNode = NULL;
        return;
    }
    else
    {
        if(theListSize <= this->listSize)//O(chainListSize)
        {
            chainNode<T>* current = (this->firstNode);
            int i;
            for(i = 0; i < theListSize-1; i++)
            {
                current->element = theList.get(i);
                current = current->next;
            }
            current->element = theList.get(i);
            while(current->next)
            {
                chainNode<T>* nextNode = current->next->next;
                delete current->next;
                current->next = nextNode;
            }
            current->next = NULL;
            this->listSize = theListSize;
            return;
        }
        else//O(theListSize)
        {
            chainNode<T>* current = this->firstNode;
            chainNode<T>* previous;
            for(int i = 0; i < theListSize; i++)
            {
                if(!current)
                {
                    current = new chainNode<T>(0, NULL);
                    this->firstNode = current;//要記得更新firstNode的值！！！
                }
                current->element = theList.get(i);
                previous = current;
                if(!(current = current->next))
                {
                    previous->next = new chainNode<T>(0, NULL);
                    current = previous->next;
                }
            }
            delete previous->next;
            previous->next = NULL;
            this->listSize  = theListSize;
            return;
        }
    }
}


template<class T>
arrayList<T>* chainListWithConverser<T>::toList()const//O(listSize)
{
    arrayList<T>* targetList = new arrayList<T>;
    chainNode<T>* current = this->firstNode;
    int i = 0;
    while(current)
    {
        targetList->insert(i++, current->element);
        current = current->next;
    }
    return targetList;
}

// int main()
// {
//     chainListWithConverser<int> x;
//     arrayList<int> y;
//     for(int i = 0; i < 0; i++)
//     {
//         x.insert(i, i+1);
//         // y.insert(i, i+100);//x.size == y.size
//     }
//     for(int i = 0; i < 2; i++)
//     {
//         y.insert(i, i+5);
//     }
//     // y不赋值,x赋值 y < x
//     // y.insert(0, 1);
//     cout << "x:";
//     cout << x << endl;
//     cout << "y:";
//     cout << y << endl;
//     x.fromList(y);
//     cout << "after fromList(y):" << endl;
//     cout << "x:";
//     cout << x << endl;
//     cout << "x.toList():" << endl;
//     cout << "x:" << *(x.toList());
// }

// int main()
// {
//     chainListWithConverser<int> x;
//     arrayList<int> y;
//     int step = 100;
//     double clocksPerMillis = CLOCKS_PER_SEC/1000;
//     std::cout << "Scale" << '\t' << "converse costs" << endl;
//     for(int n = 0; n <= 50000; n+=step)
//     {
//         double repeations = 0;
//         time_t startTime = clock();
//         do
//         {
//             repeations++;
//             for(int i = 0; i < n; i++)
//                 x.insert(i, i+1);//連續new Node插入鏈表1，使得鏈表節點在内存中的分佈也是連續的，所以toList的開銷是O(1)(即減少了緩存miss的情況)
//             // clock_t startTime = clock();
//             // x.toList();
//         }while(clock()-startTime < 1000);
//         double converse_costs =(double)(clock()-startTime);
//         converse_costs/=clocksPerMillis;
//         converse_costs/=repeations;
//         cout << n << '\t' << converse_costs << endl;
//         if(n == 1000) step = 1000;
//         if(n == 10000) step = 10000;
//     }
// }

/*
Scale   converse costs
0       0.000185385
100     1.31234
200     3.84615
300     5.98214
400     7.98413
500     9.6
600     11.6092
700     14.0833
800     16
900     18.0357
1000    20.04
2000    30.4545
3000    44.913
4000    60.1765
5000    82.1538
6000    111.333
7000    143.143
8000    175.167
9000    212.2
10000   258.5
20000   1011
30000   2263
40000   3981
50000   6322


Scale   converse costs
0       8.82207e-06
100     0.0286361
200     0.0806192
300     0.173491
400     0.295072
500     0.451671
600     0.656168
700     0.868056
800     1.1325
900     1.44653
1000    1.79856
2000    8.19672
3000    18.537
4000    32.9032
5000    52.7368
6000    76.4286
7000    104.8
8000    138
9000    177
10000   222.6
20000   963.5
30000   2203
40000   3957
50000   6217

*/


// int main()
// {
//     chainListWithConverser<int> x;
//     arrayList<int> y;
//     int step = 100;
//     double clocksPerMillis = CLOCKS_PER_SEC/1000;
//     std::cout << "Scale" << '\t' << "converse costs" << endl;
//     for(int n = 0; n <= 50000; n+=step)
//     {
//         double repeations = 0;
//         time_t startTime = clock();
//         do
//         {
//             repeations++;
//             for(int i = 0; i < n; i++)
//                 y.insert(i, i+1);
//                 // x.insert(i, i+1);//連續new Node插入鏈表1，使得鏈表節點在内存中的分佈也是連續的，所以toList的開銷是O(1)(即減少了緩存miss的情況)
//             // clock_t startTime = clock();
//             x.fromList(y);
//         }while(clock()-startTime < 1000);
//         double converse_costs =(double)(clock()-startTime);
//         converse_costs/=clocksPerMillis;
//         converse_costs/=repeations;
//         cout << n << '\t' << converse_costs << endl;
//         if(n == 1000) step = 1000;
//         if(n == 10000) step = 10000;
//     }
// }

/*
Scale   converse costs
0       1.55903e-05
100     1.32802
200     4.82212
300     9.02703
400     13.8889
500     19.7255
600     26.8947
700     33.1613
800     41.24
900     48.6667
1000    57.9444
2000    121.889
3000    188.333
4000    250
5000    332
6000    421.333
7000    515
8000    605
9000    707
10000   830.5
20000   1736
30000   2635
40000   3837
50000   5665

Scale   converse costs
0       1.79441e-05
100     1.0352
200     4.08571
300     8.50847
400     13.6216
500     20.4286
600     26.0769
700     33.8667
800     40.68
900     48.5714
1000    58.2778
2000    123.333
3000    195.667
4000    271.25
5000    356.333
6000    443.667
7000    547
8000    630.5
9000    736.5
10000   852.5
20000   1782
30000   2705
40000   3927
50000   5343
*/