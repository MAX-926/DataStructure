//设计两个方法
//方法一：
//将类型为chainNode的节点压入栈中
//方法二：
//将类型为chainNode的节点从队首移出
//我的理解：产生一个管道，队列提供输入，栈重新存储

//需要的数据：一个栈Stack和一个队列Queue

#include"../../ch8/exercise/12.cpp"
#include"../case/linkedQueue.cpp"

//全局栈
linkedStack<int> ls;
//全局队列
linkedQueue<int> lq;

// int main()
// {
//     //初始化全局队列
//     for(int i = 0; i < 10; i++)
//         lq.push(i);
//     //使用popNode()弹出chaonNode,pushNode接收节点
//     for(int i = 0; i < 10; i++)
//         ls.pushNode(&lq.popNode());
//     for(int i = 0; i < 10; i++)
//     {
//         cout << ls.top() << " ";
//         ls.pop();
//     }
// }

int main()
{
    time_t start = clock();
    double clocksPerMillions = CLOCKS_PER_SEC / 1000;
    long loopTimes = 0;

    // do
    // {
        loopTimes++;
        for(int i = 0; i < 1000000; i++)
            lq.push(i);
            // lq.push(i);
        for(int i = 0; i < 1000000; i++)
            lq.pop();
            // lq.pop();
    // }while(clock() - start >= 1000);
    time_t end = clock();
    double timeCost = (double)(end - start);
    timeCost = timeCost/clocksPerMillions/loopTimes;//得到序列的执行时间，以毫秒为单位
    cout << "timeCost = " << timeCost << endl;
}
