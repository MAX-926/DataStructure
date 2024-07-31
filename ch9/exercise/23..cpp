//使用车厢重排的第二个策略，在每次移到一个车厢时，即显示缓冲轨道的状态

//Queue_way
#include"../case/9-1.h"
#include"../../Tool.h"

//循环队列
template<class T>
class arrayQueue:public queue<T>
{
    public:
        //constructor, copy-constructor and destructor
        arrayQueue(int initialCapacity = 10)
        {
            if(initialCapacity < 1)
                throw illegalParameter("initialCapacity must be > 0");
            arrayLength = initialCapacity;
            queue = new T[arrayLength];
            queueFront = 0;//指代队首，置空
            queueBack = 0;//指代队尾
        }
        // arrayQueue(const arrayQueue<T>&);
        virtual ~arrayQueue() {if(queue) delete[] queue;}
        //ADT methods:
        bool empty()const{ return queueFront == queueBack;}
        int size()const{return (queueBack - queueFront + arrayLength) % arrayLength;}
        T& front();
        T& back();
        void push(const T& theElement);
        void pop();
    protected:
        T* queue;//代表队列
        int queueFront;//队首
        int queueBack;//队尾
        int arrayLength;//队列长度
};

template<class T>
T& arrayQueue<T>::front()
{
    if(queueFront == queueBack)
        throw queueEmpty();
    return queue[(queueFront + 1) % arrayLength];
}

template<class T>
T& arrayQueue<T>::back()
{
    if(queueFront == queueBack)
        throw queueEmpty();
    return queue[queueBack];
}

template<class T>
void arrayQueue<T>::push(const T& theELement)
{
    if((queueBack + 1) % arrayLength == queueFront)
    {//扩容
        T* newQueue = new T[arrayLength*2];
        int index = 1;
        for(int iter = (queueFront+1) % arrayLength; iter != queueBack; iter = (iter + 1) % arrayLength)
            newQueue[index++] = queue[iter];
        //复制queueBack
        newQueue[index] = queue[queueBack];
        arrayLength *= 2;
        queueFront = 0;
        queueBack = index;
        delete[] queue;
        queue = newQueue;
    }
    queueBack = (queueBack + 1) % arrayLength;
    queue[queueBack] = theELement;
}

template<class T>
void arrayQueue<T>::pop()
{
    if(queueFront == queueBack)
        throw queueEmpty();
    queue[(queueFront + 1) % arrayLength].~T();
    queueFront = (queueFront + 1) % arrayLength;
}

// int main()
// {
//     arrayQueue<int> aq;
//     for(int i = 0; i < 10; i++)
//     {
//         aq.push(i);
//     }
    // cout << endl << aq.size() << endl;

    // for(int i = 0; i < 10; i++)
    // {
    //     cout << aq.front() << " ";
    //     aq.pop();
    // }
    // cout << endl << aq.size();
// }

//使用队列实现列车重排

int numOfCars;
int numOfTracks;

int* whichTrack;
int* lastCar;

int largeCar;

void showRailRoad();

bool railRoad(int inputOrder[], int theNumOfCars, int theNumOfTracks)
{//返回true，当且仅当找到一种列车重排的方案
    numOfCars = theNumOfCars;
    numOfTracks = theNumOfTracks;

    whichTrack = new int[numOfCars + 1];
    lastCar = new int[numOfTracks + 1];

    fill(whichTrack + 1, whichTrack + numOfCars + 1, 0);
    fill(lastCar + 1, lastCar + numOfTracks + 1, 0);

    int nextCarToOutput = 1;

    for(int i = 1; i <= numOfCars; i++)
    {
        if(inputOrder[i] == nextCarToOutput)
        {
            cout << "Move car " << inputOrder[i] << " from input track to output track\n";
            nextCarToOutput++;
            //显示缓冲轨道的状态
            showRailRoad();
            for(int j = 1; j <= numOfCars; j++)
            {
                if(whichTrack[j] != 0 && j == nextCarToOutput)
                {
                    cout << "Move car " << j << " from holding track " << whichTrack[j] <<  " to output track\n";
                    whichTrack[j] = 0;//表示脱离缓冲轨道
                    //显示缓冲轨道的状态
                    showRailRoad();
                    nextCarToOutput++;
                }
            }
        }
        else
        {//将车厢压入缓冲轨道
            int bestTrack = 0;
            largeCar = 0;
            for(int k = 1; k <= numOfTracks; k++)
            {
                if(inputOrder[i] > lastCar[k] && lastCar[k] > largeCar)
                {
                    bestTrack = k;
                    largeCar = lastCar[k];
                }
                else
                    if(bestTrack == 0 && lastCar[k] == 0)
                        bestTrack = k;
            }
            if(bestTrack == 0)
                return false;
            cout << "Move car " << inputOrder[i] << " from input track to holding track " << bestTrack << endl;
            whichTrack[inputOrder[i]] = bestTrack;
            lastCar[bestTrack] = inputOrder[i];
            //显示缓冲轨道状态
            showRailRoad();

        }
    }
    return true;
}

void showRailRoad()
{//显示缓冲轨道的状态
    cout << "track state:\n";
    for(int t = 1; t <= numOfTracks; t++)
    {
        cout << "track " << t << " :"; 
        for(int c = numOfCars; c >= 1; c--)
        {
            if(whichTrack[c] == t)
                cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// int main()
// {
//     int car[] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
//     int len = sizeof(car) / sizeof(car[0]);
//     if(!railRoad(car, len-1, 3))
//         cout << "There is no enough holding track to solve railRoad problem\n";
//     // int cars[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
//     // int len = sizeof(cars)/sizeof(cars[0])-1;
//     // railRoad(cars, len, 3);
}

/*
Move car 5 from input track to holding track 1
Move car 8 from input track to holding track 1
Move car 1 from input track to output track
Move car 7 from input track to holding track 2
Move car 4 from input track to holding track 3
Move car 2 from input track to output track
Move car 9 from input track to holding track 1
Move car 6 from input track to holding track 3
Move car 3 from input track to output track
Move car 4 from holding track 3 to output track
Move car 5 from holding track 1 to output track
Move car 6 from holding track 3 to output track
Move car 7 from holding track 2 to output track
Move car 8 from holding track 1 to output track
Move car 9 from holding track 1 to output track

Move car 3 from input track to holding track 1
Move car 6 from input track to holding track 1
Move car 9 from input track to holding track 1
Move car 2 from input track to holding track 2
Move car 4 from input track to holding track 2
Move car 7 from input track to holding track 2
Move car 1 from input track to output track
Move car 2 from holding track 2 to output track
Move car 3 from holding track 1 to output track
Move car 4 from holding track 2 to output track
Move car 8 from input track to holding track 2
Move car 5 from input track to output track
Move car 6 from holding track 1 to output track
Move car 7 from holding track 2 to output track
Move car 8 from holding track 2 to output track
Move car 9 from holding track 1 to output track
*/
