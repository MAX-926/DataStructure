//對一顆使用數組描述的二叉樹編寫层次遍歷程序
//假設這顆樹的根用1號位置存儲
#ifndef ARRAYTREELEVELORDER_H
#define ARRAYTREELEVELORDER_H

#include<iostream>
using namespace std;

template<class T>
void visit(pair<bool, T>* tree, int count)
{//打印element
    cout << tree[count].second << ' ';
}

//level
template<class T>
void levelOrder(pair<bool, T>* theTree, int numOfNode)//O(numberOfNode as tree is full)
{//使用层次遍历，遍历数组树
    for(int i = 1; i <= numOfNode; i++)
    {
        if(theTree[i].first == false)
            continue;
        else
            visit(theTree, i);        
    }
}

#endif // ARRAYTREELEVELORDER_H