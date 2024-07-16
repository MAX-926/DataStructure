//车厢重排问题
// #include"8-4.cpp"

// //列车车厢重排程序的全局变量
// arrayStack<int> *track;//缓冲轨道数组
// int numberOfCars;
// int numberOfTracks;
// int smallestCar;//在缓冲轨道中编号最小的车厢
// int itsTrack;//停靠着最小编号车厢的缓冲轨道

// bool railRoad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
// {//从初始顺序开始重排车厢
//  //如果重排成功返回true，否则返回false
//     numberOfCars = theNumberOfCars;
//     numberOfTracks = theNumberOfTracks;
//     //创建用于缓冲轨道的栈
//     track = new arrayStack<int>[numberOfTracks+1];
//     int nextCarToOutput = 1;//前提是序列从1开始！！！
//     smallestCar = numberOfCars+1;//缓冲轨道中无车厢,(最末尾车厢？)
    
//     //重排车厢
//     for(int i = 1; i <= numberOfCars; i++)//遍历所有的车厢，以进行安排
//     {
//         //如果当前处理的车辆是下一个要移入出轨道的
//         if(inputOrder[i] == nextCarToOutput)
//         {//将车厢inputOrder[i]直接移到出轨道
//             cout << "Move car " << inputOrder[i] << " from inputTrack to outputTrack\n";
//             nextCarToOutput++;
//         //从缓冲轨道移到出轨道
//             while(smallestCar == nextCarToOutput)
//             {
//                 outputFromHoldingTrack();
//                 nextCarToOutput++;
//             }
//         }
//         else
//             //将车厢inputOrder[i]移到一个缓冲轨道
//             if(!putInHoldingTrack(inputOrder[i]))
//                 return false;
//     }
// }


//车厢重排程序
#include"8-4.cpp"
#include<iostream>
using namespace std;

arrayStack<int>* tracks;
int numberOfCars;//需要重排的车厢数量
int numberOfTracks;//缓冲轨道数目
int smallestCar;//在缓冲轨道中编号最小的车厢
int itsTrack;//停靠着最小编号车厢的缓冲轨道

void outputFromHoldingTrack();
bool putInHoldingTrack(int c);

bool railRoad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
{//重排车厢
    numberOfCars = theNumberOfCars;
    numberOfTracks = theNumberOfTracks;
    tracks = new arrayStack<int>[numberOfTracks+1];
    int nextCarToOutput = 1;
    smallestCar = numberOfCars + 1;//取一个无效值，这样所有对这个值查询的条件都不会满足
    for(int i = 1; i <= numberOfCars; i++)
        if(inputOrder[i] == nextCarToOutput)
        {//直接将车厢移到出轨道
            cout << "Move car " << inputOrder[i] << " from inputOrder to outputOrder\n";
            nextCarToOutput++;
        //检查是否有缓冲轨道的车厢可以移入出轨道
            while(smallestCar == nextCarToOutput)
            {
                outputFromHoldingTrack();
                nextCarToOutput++;
            }
        }
        //若不能移到出轨道，则压入缓冲轨道
        else
            if(!putInHoldingTrack(inputOrder[i]))
                return false;
    return true;
}

//outputFromHoldiingTrack
void outputFromHoldingTrack()
{//将编号最小的车厢从缓冲轨道移到出轨道
//从itsTrack中删除编号最小的车厢
    tracks[itsTrack].pop();
    cout << "Move car " << smallestCar << " from holding track " << itsTrack << "to output track\n";
    //检查所有栈顶，寻找编号最小的车厢以及其所属的栈itsStack
    for(int i = 1 ;i <= numberOfTracks; i++)
        if(tracks[i].top() < smallestCar && !tracks[i].empty())
        {
            smallestCar = tracks[i].top();
            itsTrack = i;
        }
}

bool putInHoldingTrack(int c)
{//将车厢c移到一个缓冲轨道。返回false，当且仅当没有可用的缓冲轨道

    //为车厢c寻找最合适的缓冲轨道
    //初始化
    int bestTrack = 0;
    int bestTop = numberOfCars+1;
    //扫描缓冲轨道
    for(int i = 1; i <= numberOfTracks; i++)
        if(!tracks[i].empty())
        {//缓冲轨道i不为空
            int topCar = tracks[i].top();
            if(c < topCar && topCar < bestTop)
            {//缓冲轨道i的栈顶具有编号更小的车厢
                bestTop = topCar;
                bestTrack = i;
            }
        }
        else//缓冲轨道i为空
            if(bestTrack == 0) bestTrack = i;
        if(bestTrack == 0) return false;//没有可用的缓冲轨道

        //把车厢c移到轨道bestTrack
        tracks[bestTrack].push(c);
        cout << "Move car " << c << " from input track " << " to holding track " << bestTrack << endl;

        //如果需要，更新smallestCar 和 itsTrack
        if(c < smallestCar)
        {
            smallestCar = c;
            itsTrack = bestTrack;
        }

        return false;
}