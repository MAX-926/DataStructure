//工厂仿真
#include"9-2.cpp"//arrayQueue
#include<iostream>
#include"../../Tool.h"

int timeNow;//每个工序完成时进行更新
int numMachines;//机器数量
int numJobs;//任务数量
eventList* eList;//事件表
machine* mArray;//机器数组
int largeTime = 10000;//在这个时间之前，所有机器已完成工序，是一个假定的极大值

using namespace std;

void inputData();
void startShop();
void simulate();
void outputStatistics();

//抽象出的对象：工序、任务、机器

struct task
{//任务结构：（machine， time）
    int machine;
    int time;
    task(int theMachine = 0, int theTime = 0):machine(theMachine), time(theTime){}
};

struct job
{//描述一个任务的结构
    arrayQueue<task> taskQ;//任务序列
    int length;//任务中工序的数量
    int arrivalTime;//任务到达的时刻
    int id;//任务标志符
    job(int theId = 0)
    {
        id = theId;
        length = 0;
        arrivalTime = 0;
    }
    void addTask(int theMachine, int theTime)
    {//向任务中加入工序
        // taskQ.push(task(theMachine, theTime));
        task theTask = task(theMachine, theTime);
        taskQ.push(theTask);
    }

    int removeNextTask()
    {//删除任务的下一道工序，返回它的时间
    //更新长度
        int theTime = taskQ.front().time;
        taskQ.pop();
        length += theTime;
        return theTime;
    }
};

struct machine
{//机器结构
    arrayQueue<job*> jobQ;

    int changeTime;//本机转换时间
    int totalWait;//本机器的总体延时
    int numTasks;//本机器处理的工序数量
    job* activeJob;//本机器当前正在处理的任务

    machine()
    {
        totalWait = 0;
        numTasks = 0;
        activeJob = nullptr;
    }
};

class eventList
{
    public:
        eventList(int theNumMachines, int theLargeTime)
        {//为m台机器初始化其完成时间
            if(theNumMachines < 1)
                throw illegalParameter("number of machines must be >= 1");
            theNumMachines = theNumMachines;
            finishTime = new int [numMachines + 1];
            //所有机器都空闲，用大的完成时间初始化
            for(int i = 1; i <= numMachines; i++)
                finishTime[i] = theLargeTime;
        }

        int nextEventMachine()
        {//返回值是处理下一项工序的机器

            //寻找完成时间最早的机器
            int p = 1;
            int t = finishTime[1];
            for(int i = 2; i <= numMachines; i++)
                if(finishTime[i] < t)
                {//机器完成时间更早
                    p = i;
                    t = finishTime[i];
                }
            return p;
        }

        int nextEventTime(int theMachine){return finishTime[theMachine];}

        void setFinishTime(int theMachine, int theTime){finishTime[theMachine] = theTime;}
    private:
        int* finishTime;
        int numMachines;
};

void inputData()
{//输入工厂数据
    cout << "Enter number of machines and jobs" << endl;
    cin >> numMachines >> numJobs;
    //对输入的合法性进行检查
    if(numMachines < 1 || numJobs < 1)
        throw illegalParameter("number of machines and jobs must be >= 1");
    //生成事件和机器队列
    eList = new eventList(numMachines, largeTime);
    mArray = new machine[numMachines + 1];//mArray[0]弃用

    //输入机器的转换时间
    cout << "Enter change-over times for machines" << endl;
    int ct;
    for(int i = 1; i <= numMachines; i++)
    {
        cin >> ct;
        if(ct < 0)
            throw illegalParameter("change-over time must be >= 0");
        mArray[i].changeTime = ct;
    }

    //输入任务
    job* theJob;
    int numTasks, firstMachine, theMachine, theTaskTime;
    for(int i = 1; i <= numJobs; i++)
    {
        cout << "Enter number of tasks for job " << i << endl;
        cin >> numTasks;
        firstMachine = 0;
        if(numTasks < 1)
            throw illegalParameter("each job must have > 1 task");

    //生成任务
    theJob = new job(i);
    cout << "Enter the tasks (machine, time)" << " in process order" << endl;
    for(int j = 1; j <= numTasks; j++)
    {//读取任务i的工序
        cin >> theMachine >> theTaskTime;
        if(theMachine < 1 || theMachine > numMachines || theTaskTime < 1)
            throw illegalParameter("bad machine number or task time");
        if(j == 1)
            firstMachine = theMachine;
        theJob->addTask(theMachine, theTaskTime);
    }
    mArray[firstMachine].jobQ.push(theJob);
    }
}

void startShop()
{//在每台机器上装载其第一个任务
    // for(int i = 1; i <= numMachines; i++)
        // changeState(p);
}

int main()
{
    //获取机器和任务的数据
    inputData();
    //装入初始任务
    startShop();
    //执行所有任务
    simulate();
    //输出各个机器的等待时间
    outputStatistics();
}