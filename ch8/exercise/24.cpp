//车厢重排问题
//为列车排序
#include<iostream>
// #include<stack>
#include"../case/8-4.cpp"
using namespace std;

arrayStack<int>* track;
int theNumsOfCars;
int theNumsOfTrack;
int theSmallestCar;//人为规定的一个极大值，以此寻找最小车辆的编号
int itsTrack = 0;


bool putInHoldingTrack(int);
void outputHoldingCar();

bool railRoad(int cars[], int numsOfCars, int numsOfTracks)
{//传入一个序列，对序列进行排序，如果成功返回true，否则返回false
//扫描序列，如果当前处理的对象是需要输出的，则直接置入出轨道
//否则置入缓冲轨道
//如果有合适的缓冲轨道则置入，若没有则算法退出，返回false
//若当前最小车辆为需要输出的，处在缓冲轨道中，则将其输出，并寻找下一个最小车辆
    theNumsOfCars = numsOfCars;
    theNumsOfTrack = numsOfTracks;
    theSmallestCar = numsOfCars+2;
    track = new arrayStack<int>[numsOfTracks+1];

    int nextCarToOutput = 1;
    for(int i = 1; i <= theNumsOfCars; i++)
    {
        if(cars[i] == nextCarToOutput)
        {
            cout << "Move car " << cars[i] << " to output track directly\n";
            nextCarToOutput++;
            while(theSmallestCar == nextCarToOutput)
            {
                outputHoldingCar();//需要对theSmallestCar进行更新
                nextCarToOutput++;
            }
        }
        else
        {//不是能够直接输出的车，则为其寻找合适的缓冲轨道

            if(!putInHoldingTrack(cars[i])) return false;
        }
    }
    if(!track[1].empty())
    {
        while(!track[1].empty())
        {
            cout << "Move car " << track[1].top() << " from holding track " << 1 << " to output track\n";
            track[1].pop();
        }
    }
    return true;
}

//将车辆压入缓冲轨道
bool putInHoldingTrack(int c)
{//将车辆压入缓冲轨道，如果成功返回true，失败返回false
//入栈的原则：车应进入最合适的车厢
    int bestTrack = 0;
    int bestCar = theNumsOfCars + 2;
    for(int i = 1; i <= theNumsOfTrack; i++)
    {
        //如果车厢非空，则需要
        if(!track[i].empty())
        {
            int topCar = track[i].top();
            if(bestCar > topCar && topCar > c)
            {
                bestTrack = i;
                bestCar = topCar;
            }
        }
        else if(bestTrack == 0)
        {
            bestTrack = i;
        //     return true;
        }
    }
    if(bestTrack == 0) return false;
    track[bestTrack].push(c);
    cout << "Move car " << c << " from input track to holding track " << bestTrack << endl;
    if(c < theSmallestCar)
    {
        theSmallestCar = c;
        itsTrack = bestTrack;
    }
    return true;
}
//将车辆从缓冲轨道弹出
void outputHoldingCar()
{//将缓冲轨道中编号最小的车辆弹出
    cout << "Move car " << theSmallestCar << " from holding track to output track\n";
    track[itsTrack].pop();
    //寻找栈中最小的元素
    theSmallestCar = theNumsOfCars+2;
    itsTrack = 0;
    for(int i = 1; i <= theNumsOfTrack; i++)
    {
        if(!track[i].empty())
        {
            int topCar = track[i].top();
            if(topCar < theSmallestCar)
            {
                theSmallestCar = topCar;
                itsTrack = i;
            }
        }
    }
}

template<class T>
int length(T*& array)
{
    return sizeof(array)/sizeof(array[0]);
}

int main()
{
    int cars[] = {0, 5, 3, 6, 1, 2, 4, 8, 7, 9};
    int len = sizeof(cars)/sizeof(cars[0]);
    if(railRoad(cars, 9, 3))
        cout << "Has a way to solve railRoad problem\n";
    else cout << "There is no enough buffer to solve railRoad problem";
}
