//车厢重排
#include"9-2.cpp"

arrayQueue<int>* track;//有一条轨道直接通向出轨道
arrayQueue<int> outputTrack;
int numOfCars;
int numOfTracks;
int smallestCar;
int itsTrack;

void outputFromHoldingTrack();
bool putInHoldingTrack(int);

//寻找一个重排车厢的方法，存在则返回true，否则返回false
bool railRoad(int inputOrder[], int theNumOfCars, int theNumOfTracks)
{
    numOfCars = theNumOfCars;
    numOfTracks = theNumOfTracks;
    track = new arrayQueue<int>[theNumOfTracks + 1];//track[0]弃用，工友numOfTrack-1条缓冲轨道

    smallestCar = numOfCars + 2;
    //扫描车厢
    int nextCarToOutput = 1;
    for(int i = 1; i <= numOfCars; i++)//inputOrder[0]弃用
    {
        if(inputOrder[i] == nextCarToOutput)
        {
            cout << "Move car " << inputOrder[i] << " from input track to output track " << numOfTracks << endl;
            // track[numOfTracks].push(inputOrder[i]);//送入出轨道
            outputTrack.push(inputOrder[i]);
            nextCarToOutput++;
            //检查缓冲队列中是否有可以输出的车厢
            while(smallestCar == nextCarToOutput)
            {
                //将车厢从缓冲队列中输出到出轨道
                outputFromHoldingTrack();
                nextCarToOutput++;
            }
        }
        else
        {//将车厢压入缓冲队列，若失败则返回false
            if(!putInHoldingTrack(inputOrder[i]))
                return false;
        }
    }
    return true;
}

void outputFromHoldingTrack()
{//从缓冲队列中将编号最小的车厢输出
    cout << "Move car " << smallestCar << " from holding track " << itsTrack <<  " to output track " << numOfTracks << endl;
    // track[numOfTracks].push(smallestCar);
    outputTrack.push(smallestCar);
    track[itsTrack].pop();
    smallestCar = numOfCars + 2;
    //更新缓冲轨道中编号最小的车厢的信息
    for(int i = 1; i < numOfTracks; i++)
    {
        if(!track[i].empty())
        {
            int frontCar = track[i].front();
            if(frontCar < smallestCar)
            {
                smallestCar = frontCar;
                itsTrack = i;
            }
        }
    }
}

//栈的时候找大于当前c的最小者（最紧上界），队列的时候找小于当前c的最大者（最紧下界）
bool putInHoldingTrack(int c)
{//将车厢c压入合适的缓冲轨道，若未找到则返回false，否则返回true
    int bestTrack = 0;
    // int bestCar = numOfCars + 2;
    int bestCar = 1;//缓冲轨道中没有车厢的编号会小于1
    //原书中定义bestCar = 0; 的理由是什么？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
    for(int i = 1; i < numOfTracks; i++)
    {   
        if(!track[i].empty())
        {
            int backCar = track[i].back();
            if(backCar < c && backCar > bestCar)
            {
                bestCar = backCar;
                bestTrack = i;
            }
        }
        else
            if(bestTrack == 0)
                bestTrack = i;
    }
    if(bestTrack == 0)
        return false;
    cout << "Move car " << c << " from input track to holding track " << bestTrack << endl;
    track[bestTrack].push(c);
    if(c < smallestCar)
    {
        smallestCar = c;
        itsTrack = bestTrack;
    }
    return true;
}

int main()
{
    int inputOrder[] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
    int len = sizeof(inputOrder)/sizeof(inputOrder[0]);
    if(!railRoad(inputOrder, len-1, 4))
        cout << "there is no enough holding track to solve railRoad problem\n";
    else
        for(int i = 0; i < len-1; i++)
        {
            cout << outputTrack.front() << " ";
            outputTrack.pop();
        }
}

/*
Move car 3 from input track to holding track 1
Move car 6 from input track to holding track 1
Move car 9 from input track to holding track 1
Move car 2 from input track to holding track 2
Move car 4 from input track to holding track 2
Move car 7 from input track to holding track 2
Move car 1 from input track to output track 4
Move car 2 from holding track 2 to output track 4
Move car 3 from holding track 1 to output track 4
Move car 4 from holding track 2 to output track 4
Move car 8 from input track to holding track 2
Move car 5 from input track to output track 4
Move car 6 from holding track 1 to output track 4
Move car 7 from holding track 2 to output track 4
Move car 8 from holding track 2 to output track 4
Move car 9 from holding track 1 to output track 4
*/