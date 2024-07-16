//开关盒布线
//程序假设管脚数已知
//输入管脚的关联关系以及管脚个数，程序返回布尔值，判定开关盒是否可以布线
//net数组为描述管脚之间关系的数组，n为管脚个数

#include"8-4.cpp"
bool checkBox(int net[], int  n)
{
    arrayStack<int>* s = new arrayStack<int>(n);
    for(int i = 0; i < n; i++)
        if(!s->empty())
        //检查栈顶管脚与当前管脚是否有布线关联
            if(net[i] == net[s->top()])
                s->pop();
            else s->push(i);
        else s->push(i);
    if(s->empty())
    {//没有剩余的管脚
        cout << "Switch box is routable" << endl;
        return true;
    }
    cout << "Switch box is not routable" << endl;
    return false;
}


int main()
{
    //(0, 3), (1, 2), (4, 5), (6, 7)
    //0, 1, 2, 3, 4, 5, 6, 7
    // int net[] = {1, 2, 2, 1, 3, 3, 4, 4};
    // checkBox(net, 8);
}