//开发一个基于线性探测的散列表类，要求用neverUsed的思想进行删除。
//当60%的空桶的neverUsed域的值为false时，重新组织散列表，重新组织后，每个空桶neverUsed的值为true

#include"../case/dictionary.h"
#include"../../Tool.h"

template<class K, class E>
class hashTable:dictionary<K, E>
{
    public:
        hashTable(int theDivisor = 11)
        {
            divisor = theDivisor;
            dSize = 0;
            numOfNeverUsedWithFalse = 0;
            numOfBlank = divisor;
            table = new pair<const K, E>*[divisor];
            neverUsed = new bool[divisor];
            for(int i = 0; i < divisor; i++)
            {
                table[i] = nullptr;
                neverUsed[i] = true;
            }
        }
        ~hashTable() { delete[] table; delete[] neverUsed;}//pair的析构过程类似内部类型？
        bool empty()const { return dSize == 0;}
        int size()const { return dSize;}
        pair<const K, E>* find(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
    protected:
        //重新组织散列表
        void reorganize();
        //search
        int search(const K&)const;
        pair<const K, E>** table;
        int dSize;
        int divisor;
        hash<K> hash;
        bool* neverUsed;
        int numOfNeverUsedWithFalse;
        int numOfBlank;
};

template<class K, class E>
int hashTable<K, E>::search(const K& theKey)const
{//返回theKey所在bucket
    int b = hash(theKey) % divisor;
    int j = b;
    do
    {
        if(table[j] == nullptr || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    }while(j != b);
    return j;//说明散列表满
}

template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey)const
{
    // int b = search(theKey);
    // if(table[b] == nullptr || table[b]->first != theKey)
    //     return nullptr;//不关心散列表是否满
    // return table[b];
    
}

template<class K, class E>
void hashTable<K ,E>::insert(const pair<const K, E>& thePair)
{
    if(numOfNeverUsedWithFalse / numOfBlank >= 0.6)
        reorganize();
    int b = search(thePair.first);
    if(table[b] != nullptr && table[b]->first == thePair.first)
    {
        table[b]->second = thePair.second;
        return;
    }
    if(table[b] == nullptr)
    {
        if(neverUsed[b] == true)
        {
            numOfNeverUsedWithFalse++;
            neverUsed[b] = false;
        }
        numOfBlank--;
        table[b] = new pair<const K, E>(thePair);
        dSize++;
        return;
    }
}

template<class K, class E>
void hashTable<K, E>::erase(const K& theKey)
{
    //删除操作
    int b = search(theKey);
    if(table[b] != nullptr && table[b]->first == theKey)
    {
        delete table[b];
        numOfBlank++;
        dSize--;
        return;
    }
    //判断是否需要重整散列表
    //删除操作会改变numOfBlank，使其增大，进而使得比值变小（我认为不需要进行是否大于等于0.6的检验）
    //tips：可以与insert进行联动设计
    // if(numOfNeverUsedWithFalse / numOfBlank >= 0.6)
    //     reorganize();
}

template<class K, class E>
void hashTable<K, E>::reorganize()
{//重整散列表
    int newDivisor = divisor*2 + 1;//避免divisor为偶数的可能
    pair<const K, E>** newTable = new pair<const K, E>*[newDivisor];
    bool newNeverUsed* = new bool[newDivisor];
    for(int i = 0; i < newDivisor; i++)
    {
        newTable[i] = nullptr;
        newNeverUsed[i] = true;
    }
    int newNumOfNeverUsedWithFalse = 0;
    int newNumOfBlank = newDivisor;
    //移动数据
    for(int i = 0; i < divisor; i++)
    {//遍历散列表。将存在的元素映射到新表中
        if(table[i] != nullptr)
        {
            pair<const K, E>* targetPair = table[i];
            //插入新散列表
            K& theKey = targetPair->first;
            int b = hash(theKey) % newDivisor;
            //寻找合适的桶
            int j = b;
            do
            {
                if(newTable[j] == nullptr || newTable[j]->first == theKey)
                    break;
                j = (j + 1) % newDivisor;
            }while(j != b);
            if(j == b)
        }
    }
}