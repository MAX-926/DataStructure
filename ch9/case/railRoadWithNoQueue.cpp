//railRoadWithNoQueue
//使用其它变量代替队列，获得与使用队列一样的重排结果
#include<iostream>
#include<string.h>
using namespace std;

int numOfCars;
int numOfTracks;
int smallestCar;

int* whichTrack;//代表所有车辆处在输入队列中
int* lastCar;;//代表每个轨道还没有车辆进入

void outputFromHoldingTrack();
bool putInHoldingTrack(int);

bool railRoadWithNoQueue(int car[], int theNumOfCars, int theNumOfTracks)
{
    numOfCars = theNumOfCars;
    numOfTracks = theNumOfTracks;

    whichTrack = new int[numOfCars+1];
    lastCar = new int[numOfTracks+1];
    memset(whichTrack, 0, sizeof(int) * (numOfCars + 1));
    memset(lastCar, 0, sizeof(int) * (numOfTracks + 1));

    smallestCar = numOfCars + 2;
    int nextCarToOutput = 1;
    for(int i = 1; i <= numOfCars; i++ )
    {
        if(nextCarToOutput == car[i])
        {
            cout << "Move car " << car[i] << " from input track to output track\n";
            nextCarToOutput++;
            while(nextCarToOutput == smallestCar)
            {
                //j将车厢从缓冲轨道移入出轨道
                outputFromHoldingTrack();
                nextCarToOutput++;
            }
        }
        else
            if(!putInHoldingTrack(car[i]))
                return false;
    }
    return true;
}

void outputFromHoldingTrack()
{//从缓冲栈中输出编号最小的车厢
    cout << "Move car " << smallestCar << " from track " << whichTrack[smallestCar] << " to output track " << 0 << endl;
    //将whichTrack[smallestCar]标记为-1，表示到达输出轨道
    whichTrack[smallestCar] = -1;
    //寻找下一个编号最小的车辆
    smallestCar = numOfCars + 2;
    for(int i = 1; i <= numOfCars; i++)
        if(whichTrack[i] != 0 && whichTrack[i] != -1)
        {
            smallestCar = i;
            break;
        }
}

bool putInHoldingTrack(int c)
{//将车厢c送入缓冲轨道
    int bestCar = 1;
    int bestTrack = 0;
    for(int i = 1; i < numOfTracks; i++)
    {
        if(lastCar[i] != 0)
        {
            if(c > lastCar[i] && lastCar[i] > bestTrack)
            {
                bestCar = lastCar[i];
                bestTrack = i;
            }
        }
        else
            if(bestTrack == 0)
                bestTrack = i;
    }
    if(bestTrack == 0) return false;
    cout << "Move car " << c << " from input track " << whichTrack[c] << " to holding track " << bestTrack << endl;
    whichTrack[c] = bestTrack;
    lastCar[bestTrack] = c;
    //检查是否需要更新smallestCar
    for(int i = 1; i <= numOfCars; i++)
        if(whichTrack[i] != 0 && whichTrack[i] != -1)
        {
            smallestCar = i;
            break;
        }
    return true;
}

// int main()
// {
//     int car[] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
//     int len = sizeof(car) / sizeof(car[0]);
//     if(!railRoadWithNoQueue(car, len-1, 3))
//         cout << "There is no enough holding track to solve railRoad problem\n";
// }