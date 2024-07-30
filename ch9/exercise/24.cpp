// //车厢重排问题（LIFO）
// #include<iostream>
// #include"../../Tool.h"

// using namespace std;

// int* topCar;
// int* whichTrack;
// int numOfCars;
// int numOfTracks;
// int smallestCar;

// bool railRoad(int cars[], int theNumOfCars, int theNumOfTracks)
// {//程序返回true，当且仅当有办法利用铁道重排车厢
//     if(theNumOfCars < 1)
//         throw illegalParameter("number of cars must be > 0");
//     if(theNumOfTracks < 1)
//         throw illegalParameter("number of tracks must be > 0");
//     int nextCarToOutput = 1;
//     numOfCars = theNumOfCars;
//     numOfTracks = theNumOfTracks;
//     topCar = new int[numOfTracks + 1];
//     fill(topCar, topCar + numOfTracks+1, 0);
//     whichTrack = new int[numOfCars + 1];
//     fill(whichTrack, whichTrack + numOfCars + 1, 0);//代表所有车厢均在输入轨道中
//     smallestCar = numOfCars + 2;
//     //扫描车厢，进行重排
//     for(int c = 1; c <= numOfCars; c++)
//     {//若车厢是当前期望输出的车厢，立即输出
//         if(nextCarToOutput == cars[c])
//         {
//             cout << "Move car " << cars[c] << " from input track to output track directly\n";
//             nextCarToOutput++;
//             //查看缓冲轨道内是否还有可以输出的轨道
//             while(smallestCar == nextCarToOutput && whichTrack[smallestCar] != 0)
//             {
//                     cout << "Move car " << smallestCar << " from holding track " << whichTrack[smallestCar] << " to output track\n";
//                     topCar[smallestCar] = 0;
//                     whichTrack[smallestCar] = 0;
//                     nextCarToOutput++;
//                     for(int j = 1; j <= numOfCars; j++)
//                     {
//                         if(whichTrack[j] != 0)
//                         {
//                             smallestCar = j;
//                             break;
//                         }
//                     }
//             }
//         }
//         else
//         {//否则将车厢加入缓冲轨道
//             int bestTrack = 0;
//             smallestCar = numOfCars + 2;
//             for(int i = 1; i <= numOfTracks; i++)
//             {
//                 if(cars[c] < topCar[i] && topCar[i] < smallestCar)
//                 {
//                     smallestCar = topCar[i];
//                     bestTrack = i;
//                 }
//                 else if(bestTrack == 0 && topCar[i] == 0)
//                     bestTrack = i;
//             }
//             if(bestTrack == 0)
//                 return false;
//             topCar[bestTrack] = cars[c];
//             whichTrack[cars[c]] = bestTrack;
//             cout << "Move car " << cars[c] << " from input track to holding track " << bestTrack << endl;
//             for(int i = 1; i <= numOfTracks; i++)
//                 if(topCar[i] <= smallestCar)
//                     smallestCar = topCar[i];
//         }
//     }
//     return true;
// }

// int main()
// {
//     int car[] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
//     int len = sizeof(car) / sizeof(car[0]);
//     if(!railRoad(car, len-1, 3))
//         cout << "There is no enough holding track to solve railRoad problem\n";
// }

#include<iostream>
using namespace std;

int smallestCar;
int numOfCars;
int numOfTracks;
int* whichTrack;
int* topCar;

bool railRoad(int inputOrder[], int theNumOfCars, int theNumOfTracks)
{//返回true，当且仅当找到一条安排方式
    int nextCarToOutput = 1;
    smallestCar = theNumOfCars + 2;
    numOfCars = theNumOfCars;
    numOfTracks = theNumOfTracks;

    whichTrack = new int[numOfCars + 1];
    topCar = new int[numOfTracks + 1];
    fill(whichTrack + 1, whichTrack + numOfCars + 1, 0);
    fill(topCar + 1, topCar + numOfTracks + 1, 0);

    for(int inputIter = 1; inputIter <= numOfCars; inputIter++)
    {
        //如果当前车厢是需要输出的
        if(inputOrder[inputIter] == nextCarToOutput)
        {
            cout << "Move car " << inputOrder[inputIter] << " from input track to output track\n";
            nextCarToOutput++;
            //若缓冲轨道有需要输出的车厢
            bool up;
            while(smallestCar == nextCarToOutput)
            {//输出缓冲轨道的车厢
                cout << "Move car " << smallestCar << " from holding track to output track\n";
                nextCarToOutput++;
                up = false;
                //将smallestCar所在的轨道的下一个元素拉上来
                for(int iter = 1; iter <= numOfCars; iter++)
                {
                    if(whichTrack[iter] == whichTrack[smallestCar] && iter != smallestCar)
                    {
                        topCar[whichTrack[iter]] = iter;
                        up = true;
                        break;
                    }
                }
                if(!up) topCar[whichTrack[smallestCar]] = 0;
                whichTrack[smallestCar] = 0;//表示脱离缓冲轨道
                //寻找下一个最小车厢
                int tmp = numOfCars + 2;
                for(int carIter = 1; carIter <= numOfCars; carIter++)
                {
                    if(whichTrack[carIter] != 0 && carIter < tmp)
                    {
                        tmp = carIter;
                        smallestCar = carIter;
                        break;
                    }
                }
            }
        }
        else
        {//将车厢移入缓冲轨道
            int bestTrack = 0;
            int tmp = numOfCars + 2;
            for(int trackIter = 1; trackIter <= numOfTracks; trackIter++)
            {
                if(inputOrder[inputIter] < topCar[trackIter] && topCar[trackIter] < tmp)
                {
                    bestTrack = trackIter;
                    tmp = topCar[trackIter];
                }
                else
                    if(bestTrack == 0 && topCar[trackIter] == 0)
                        bestTrack = trackIter;
            }
            if(bestTrack == 0) return false;
            cout << "Move car " << inputOrder[inputIter] << " from input track to holding track " << bestTrack << endl;
            whichTrack[inputOrder[inputIter]] = bestTrack;
            topCar[bestTrack] = inputOrder[inputIter];
            //检查是否更新最小车辆
            if(inputOrder[inputIter] < smallestCar)
                smallestCar = inputOrder[inputIter];
        }
    }
    return true;
}

int main()
{
    // int car[] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
    // int len = sizeof(car) / sizeof(car[0]);
    // if(!railRoad(car, len-1, 3))
    //     cout << "There is no enough holding track to solve railRoad problem\n";
    int cars[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
    int len = sizeof(cars)/sizeof(cars[0])-1;
    railRoad(cars, len, 3);
}

/*
Move car 3 from input track to holding track 1
Move car 6 from input track to holding track 1
Move car 9 from input track to holding track 1
Move car 2 from input track to holding track 1
Move car 4 from input track to holding track 1
Move car 7 from input track to holding track 1
Move car 1 from input track to output track
Move car 2 from holding track to output track
Move car 3 from holding track to output track
Move car 4 from holding track to output track
Move car 8 from input track to holding track 1
Move car 5 from input track to output track
Move car 6 from holding track to output track
Move car 7 from holding track to output track
Move car 8 from holding track to output track
Move car 9 from holding track to output track
*/