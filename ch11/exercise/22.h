//使用后序遍历处理数组树
//對一顆使用數組描述的二叉樹編寫后序遍歷程序
//假設這顆樹的根用1號位置存儲
#ifndef ARRAYTREEPOSTORDER_H
#define ARRAYTREEPOSTORDER_H

#include<iostream>
using namespace std;

template<class T>
void visit(pair<bool, T>* tree, int count)
{//打印element
    cout << tree[count].second << ' ';
}

//LRM
template<class T>
void postOrder(pair<bool, T>* theTree, int count, int numOfNode)//O(numberOfNode)
{//使用后序遍历，遍历数组树
    if(count > numOfNode) return;
    postOrder(theTree, count*2, numOfNode);
    postOrder(theTree, count*2 + 1, numOfNode);
    visit(theTree, count);
}

#endif // ARRAYTREEPOSTORDER_H