// #include"8-4.cpp"
// #include<iostream>
// using namespace std;

// arrayStack<int>* track;
// int numberOfCars;
// int numberOfTracks;
// int smallestCar;
// int itsTrack;

// void outputFromHoldingTrack();
// bool putInHoldingTrack(int c);

// bool railRoad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
// {//初始化工作
//     numberOfCars = theNumberOfCars;
//     numberOfTracks = theNumberOfTracks;
//     track = new arrayStack<int>[numberOfTracks+1];
//     int nextCarToOutput = 1;
//     smallestCar = numberOfCars+1;//缓冲轨道为空
//     //扫描输入序列，完成车厢重排
//     for(int i = 1; i <= numberOfCars; i++)
//         if(inputOrder[i] == nextCarToOutput)
//         {
//             //将车厢移到出轨道
//             cout << "Move car " << inputOrder[i] << " from input track to output track\n";
//             nextCarToOutput++;
//             while(smallestCar == nextCarToOutput)
//             {
//                 outputFromHoldingTrack();
//                 nextCarToOutput++;
//             }
//         }
//         else
//         {//将车厢inputOrder[i]移入缓冲轨道
//             if(!putInHoldingTrack(inputOrder[i]))
//                 return false;
//         }
//     return true;
// }

// void outputFromHoldingTrack()
// {//从缓冲轨道移出最小的车厢到出轨道
//     track[itsTrack].pop();
//     cout << "Move car " << smallestCar << " from holding track " << itsTrack << " to output track\n";
//     //寻找下一个最小车厢及其栈顶
//     smallestCar = numberOfCars + 2;//人为规定的极大值，没有车厢的编号比它大，可以协助找出下一个最小值
//     for(int i = 1; i <= numberOfTracks; i++)
//         if(!track[i].empty() && track[i].top() < smallestCar)
//         {
//             smallestCar = track[i].top();
//             itsTrack = i;
//         }
// }

// bool putInHoldingTrack(int c)
// {//将车厢移到一个缓冲轨道，返回false，当且仅当没有合适的缓冲轨道可以移入
//    int bestTrack = 0;
//    int bestTop = numberOfCars+2;
//    //扫描缓冲轨道
//     for(int i = 1; i <= numberOfTracks; i++)
//     {
//         if(!track[i].empty())
//         {
//             int topCar = track[i].top();
//             if(c < topCar && topCar < bestTop)
//             {
//                 bestTop = topCar;
//                 bestTrack = i;
//             }
//         }
//         else//缓冲轨道i为空
//             if(bestTrack = 0)
//                 bestTrack = i;
//     }
//     if(bestTrack == 0) return false;
//     //将车厢c压入合适的缓冲轨道
//     track[bestTrack].push(c);
//     cout << "Move car " << c << " from input track to holding track " << bestTrack << endl;
//     //如果需要，更新smallestCar和itsTrack
//     if(c < smallestCar)
//     {
//         smallestCar = c;
//         itsTrack = bestTrack;
//     }
//     return true;
// }

// template<class T>
// int length(T x[])
// {
// }

// int main()
// {
//     int inputOrder[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
//     numberOfCars = sizeof(inputOrder)/sizeof(inputOrder[0]);
//     cout << railRoad(inputOrder, numberOfCars-1, 3);
// }

#include<iostream>
#include"8-4.cpp"

arrayStack<int>* track;
int numberOfCars;
int numberOfTracks;
int smallestCar;
int itsTrack;

void outputFromHoldingTrack();
bool putInHoldingTrack(int c);

bool railRoad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)//O(numberOfCars*numberOfTracks)
{
    numberOfCars = theNumberOfCars;
    numberOfTracks = theNumberOfTracks;
    track = new arrayStack<int>[numberOfTracks+1];
    smallestCar = numberOfCars+2;
    int nextCarToOutput = 1;
    for(int i = 1; i <= numberOfCars; i++)//O(numberOfCars*numberOfTracks)
        if(inputOrder[i] == nextCarToOutput)//O(numberOfCars*numberOfTracks)
        {
            cout << "Move car " << inputOrder[i] << " from input track to output track\n";
            nextCarToOutput++;
            while(smallestCar == nextCarToOutput)//O(numberOfCars*numberOfTracks)
            {
                outputFromHoldingTrack();//O(numberOfTracks)
                nextCarToOutput++;
            }
        }
        else//O(numberOfCars*numberOfTracks)
        {//将车厢移入缓冲轨道
            if(!putInHoldingTrack(inputOrder[i]))//O(numberOfCars*numberOfTracks)
                return false;
        }
        return true;
}

void outputFromHoldingTrack()//O(numberOfTracks)
{
    track[itsTrack].pop();
    cout << "Move car " << smallestCar << " from holding track " << itsTrack << " to output track\n";
    smallestCar = numberOfCars+2;
    for(int i = 1; i <= numberOfTracks; i++)//O(numberOfTracks)
        if(!track[i].empty() && track[i].top() < smallestCar)
        {
            smallestCar = track[i].top();
            itsTrack = i;
        }
}

bool putInHoldingTrack(int c)//O(numberOfTracks)
{//找到最合适的缓冲轨道移入c,返回false，当且仅当没有合适的缓冲轨道
    int bestTop = numberOfCars+2;
    int bestTrack = 0;
    for(int i = 1; i <= numberOfTracks; i++)//O(numberOfTracks)
    {
        if(!track[i].empty())//O(1)
        {
            int topCar = track[i].top();
            if(c < topCar && topCar < bestTop)
            {
                bestTop = topCar;
                bestTrack = i;
            }
        }
        else//O(1)
        {
            if(bestTrack == 0)
                bestTrack = i;
        }
    }
    if(bestTrack == 0)//O(1)
        return false;
    track[bestTrack].push(c);//O(1)
    cout << "Move car " << c << " from input track to holding track" << bestTrack << "\n";
    if(c < smallestCar)//O(1)
    {
        smallestCar = c;
        itsTrack = bestTrack;
    }
    return true;
}