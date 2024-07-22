//checkBox
#include"../case/8-4.cpp"

bool checkBox(int n, int relationsMap[])
{//管脚数n
    arrayStack<int> s;
    for(int i = 0; i < n; i++)
    {
        if(!s.empty())
        {
            if(relationsMap[s.top()] == relationsMap[i])
            {
                s.showStack(); 
                s.pop();
            }
            else
            {
                s.showStack(); 
                s.push(i);
            }
        }
        else
        {
            s.push(i);
            s.showStack(); 
        }
    }
    if(s.empty())
    {
        cout << "box is routable\n";
        return true;
    }
    else
    {
        cout << "box is not routable\n";
        return false;
    }
}

int main()
{
    int n = 8;
    int relationsMap[] = {1, 2, 3, 3, 2, 1, 4, 5, 5, 4, 6, 7, 7, 6};
    checkBox(n, relationsMap);

}