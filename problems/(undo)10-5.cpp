//跳表：是一种支持二分查找的有序链表，形式上是一个带有前向指针的分级链表
#include<utility>
#include<math.h>
using namespace std;
//skipNode
template<class K, class E>
struct skipNode
{
    typedef pair<const K, E> pairType;
    //data
    pairType element;//数对
    //pointer
   skipNode<K, E>* next;//前向指针
    //size为链表级数上限
   skipNode(const pairType& thePair, int size):element(thePair){next = new skipNode<K, E>[size];}//通过这个节点，我可以找到的节点信息存在next数组中 
};

template<class K, class E>
class skipList
{
    public:
        skipList(K largeKey, int maxPairs, float prob);

    protected:
        float cutOff;//用来确定层数
        int levels;//当前最大的非空链表
        int dSize;//字典的数对个数
        int maxLevel;//允许的最大链表层数
        K tailKey;//最大关键字
        skipNode<K, E>* headerNode;//头节点指针
        skipNode<K, E>* tailNode;//尾节点指针
        skipNode<K, E>** last;//last[i]表示i层的最后节点
};

template<class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{//构造函数，关键字小于largeKey 且数对个数size最多为maxpairs。0 < prob < 1
    cutOff = prob * RAND_MAX;
    maxLevel = (int) celi(logf((float) maxPairs) / logf(1 / prob)) - 1;
}