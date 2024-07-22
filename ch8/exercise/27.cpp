#include<iostream>
#include"../case/8-4.cpp"
using namespace std;

arrayStack<int>* track;
int numsOfCars;
int numsOfTracks;
int smallestCar;
int itsTrack;
const int maxSize = 1;

bool putInHoldingTrack(int);
void outputFromHoldingTrack();

bool railRoad(int cars[], int theNumsOfCars, int theNumsOfTracks)
{
    numsOfCars = theNumsOfCars;
    numsOfTracks = theNumsOfTracks;
    track = new arrayStack<int>[numsOfTracks+1];
    int nextCarToOutput = 1;
    smallestCar = numsOfCars+2;
    //扫描列车
    for(int i = 1; i <= numsOfCars; i++)
    {//如果适合，直接输出
        if(cars[i] == nextCarToOutput)
        {
            cout << "Move car " << cars[i] << " from input track to output track\n";
            nextCarToOutput++;
            while(smallestCar == nextCarToOutput)
            {
                outputFromHoldingTrack();
                nextCarToOutput++;
            }
        }
        else
        {//将车厢压入缓冲轨道

            if(!putInHoldingTrack(cars[i])) return false;
        }
    }
    return true;
}

bool putInHoldingTrack(int c)
{//找到合适的缓冲轨道压入c,这个缓冲轨道要尽可能大
    int bestCar = numsOfCars+2;//key point!
    int bestTrack = 0;
    //扫描轨道选择合适的缓冲栈
    for(int i = 1; i <= numsOfTracks; i++)
    {
        if(!track[i].empty())
        {
            int topCar = track[i].top();
            if(c < topCar && topCar < bestCar)
            {
                bestCar = topCar;
                bestTrack = i;
            }
        }
        else if(bestTrack == 0)
            bestTrack = i;
    }
    if(bestTrack == 0) return false;
    if(track[bestTrack].size() == maxSize)//如果缓冲轨道容量受限为maxSize
    {
        cout << "track[" << bestTrack << "]" << " doesn't have enough space to hold car " << c << endl;
        cout << "Failed to find a holding track\n";
        return false;
    }
    cout << "Move car " << c << " from input track to holding track " << bestTrack << endl;
    track[bestTrack].push(c);
    if(c < smallestCar)
    {
        smallestCar = c;
        itsTrack = bestTrack;
    }
    return true;
}

void outputFromHoldingTrack()
{//从缓冲栈中输出编号最小的车厢
    cout << "Move car " << smallestCar << " from holding track to output track\n";
    track[itsTrack].pop();
    //找到下一个最小编号的车厢
    smallestCar = numsOfCars+2;
    itsTrack = 0;
    for(int i = 1; i <= numsOfTracks; i++)
        if(!track[i].empty())
        {
            int topCar = track[i].top();
            if(topCar < smallestCar)
            {
                smallestCar = topCar;
                itsTrack = i;
            }
        }
}

int main()
{
    // int cars[] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // int cars[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
    int cars[] = {0, 3, 1, 6, 7, 2, 8, 5, 4};
    int len = sizeof(cars)/sizeof(cars[0])-1;
    // railRoad(cars, len, 3);
    railRoad(cars, len, 3);
}