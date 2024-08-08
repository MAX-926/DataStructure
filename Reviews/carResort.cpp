//车厢重排
//输入 车厢编号序列 返回bool型，若重排成功则返回true，否则返回false
#include"ch8/case/8-4.cpp"

bool putInHoldingTrack(int c);
void outputFromHoldingTrack();

arrayStack<int>* track;
int numsOfCars;
int numsOfTracks;
int smallestCar;
int itsTrack;

bool railRoad(int inputOrder[], int theNumsOfCars, int theNumsOfTracks)
{//返回true，当且仅当存在重排方式
    //初始化全局变量
    numsOfCars = theNumsOfCars;
    numsOfTracks = theNumsOfTracks;
    track = new arrayStack<int>[numsOfTracks+1];//track[0]弃用

    smallestCar = numsOfCars + 2;//代表缓冲轨道初始状态：空
    int nextCarToOutput = 1;
    //扫描车厢，处理inputOrder
    for(int i = 1; i <= numsOfCars; i++)
    {//若inputOrder[i] == nextCarToOutput
        if(inputOrder[i] == nextCarToOutput)
        {
            cout << "Move car " << inputOrder[i] << " from input track to output track\n";
            nextCarToOutput++;
            //输出一个车厢之后，可能有车厢可以从缓冲栈中输出
            while(smallestCar == nextCarToOutput)
            {
                outputFromHoldingTrack();
                nextCarToOutput++;
            }
        }
        else
            if(!putInHoldingTrack(inputOrder[i]))
                return false;
    }
    return true;
}

bool putInHoldingTrack(int c)
{//若找到缓冲轨道压入c，则返回true，否则返回false
    int bestTop = numsOfCars+2;
    int bestTrack = 0;
    for(int i = 1; i <= numsOfTracks; i++)
    {
        if(!track[i].empty())
        {
            int topCar = track[i].top();
            if(topCar > c && topCar < bestTop)
            {
                bestTop = topCar;
                bestTrack = i;
            }
        }
        else
            if(bestTrack == 0)
                bestTrack = i;
    }
    if(bestTrack == 0) return false;
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
{//将最小编号的车厢从缓冲轨道弹出
    cout << "Move car " << smallestCar << " from holding track to output track\n";
    track[itsTrack].pop();
    //寻找缓冲轨道中编号最小的车厢以及其轨道编号
    smallestCar = numsOfCars+2;
    for(int i = 1; i <= numsOfTracks; i++)
    {
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
}

int main()
{
    int cars[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
    int len = sizeof(cars)/sizeof(cars[0])-1;
    railRoad(cars, len, 3);
}
/*
Move car 5 from input track to holding track 1
Move car 8 from input track to holding track 2
Move car 1 from input track to output track
Move car 7 from input track to holding track 2
Move car 4 from input track to holding track 1
Move car 2 from input track to output track
Move car 9 from input track to holding track 3
Move car 6 from input track to holding track 2
Move car 3 from input track to output track
Move car 4 from holding track to output track
Move car 5 from holding track to output track
Move car 6 from holding track to output track
Move car 7 from holding track to output track
Move car 8 from holding track to output track
Move car 9 from holding track to output track


carResort without stack
Move car 5 from input track to holding track 1
Move car 8 from input track to holding track 2
Move car 1 from input track to output track
Move car 7 from input track to holding track 2
Move car 4 from input track to holding track 1
Move car 2 from input track to output track
Move car 9 from input track to holding track 3
Move car 6 from input track to holding track 2
Move car 3 from input track to output track
Move car 4 from holding track to output track
Move car 5 from holding track to output track
Move car 6 from holding track to output track
Move car 7 from holding track to output track
Move car 8 from holding track to output track
Move car 9 from holding track to output track

Move car 5 from input track to holding track 1
Move car 8 from input track to holding track 2
Move car 1 from input track to output track
Move car 7 from input track to holding track 2
Move car 4 from input track to holding track 1
Move car 2 from input track to output track
Move car 9 from input track to holding track 3
Move car 6 from input track to holding track 2
Move car 3 from input track to output track
Move car 4 from holding track to output track
Move car 5 from holding track to output track
Move car 6 from holding track to output track
Move car 7 from holding track to output track
Move car 8 from holding track to output track
Move car 9 from holding track to output track
*/