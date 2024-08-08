
#include"../../Tool.h"
#include"dictionary.h"
//数组散列
template<class K, class E>
class hashTable:public dictionary<K, E>
{
    public:
        hashTable(int theDivisor = 11)
        {
            divisor = theDivisor;
            table = new pair<const K, E>*[divisor];
            for(int i = 0; i < divisor; i++)
                table[i] = nullptr;
            dSize = 0;
        }
        ~hashTable();
        //ADT Methods:
        bool empty()const { return dSize == 0;}
        int size()const { return dSize;}
        pair<const K, E>* find(const K&)const;
        int search(const K&)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
        void output(ostream&)const;
        int getHashResult(const int key)const {return hash(key) % divisor;}
    protected:
        pair<const K, E>** table;//散列表
        hash<K> hash;//将关键字转换为整数
        int divisor;//除法函数的除数
        int dSize;//散列表元素个数
        // int arrayLength;//数组容量
};

template<class K, class E>
hashTable<K, E>::~hashTable()
{
    // for(int i = 0; i < dSize; i++)
    // {
    //     if(table[i] != nullptr)
    //         delete table[i];
    // }
    delete[] table;
}

template<class K, class E>
int hashTable<K, E>::search(const K& theKey)const
{
    int i = hash(theKey) % divisor;//关键字theKey对应初始桶
    int j = i;
    do
    {
        if(table[j] == nullptr || table[j]->first == theKey)//线性探查，返回关键字对应数对在散列表中的索引
            return j;
        j = (j+1) % divisor;
    }while(j != i);
    return j;//表满
}

template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey)const
{//找到关键字theKey对应的数对
    int b = search(theKey);
    if(table[b] == nullptr || table[b]->first != theKey)
        return nullptr;
    return table[b];
}

template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
    int b = search(thePair.first);
    if(table[b] == nullptr)
    {
        table[b] = new pair<const K, E>(thePair);
        dSize++;
        return;
    }
    else
    {//检查是否有重复关键字数对是否表满
        if(table[b]->first == thePair.first)
        {
            table[b]->second = thePair.second;
        }
        else
            throw hashTableFull();
    }
}

// template<class K, class E>
// void hashTable<K, E>::erase(const K& theKey)
// {//将关键字对应数对从hashTable中删除
//     int b = search(theKey);
//     if(table[b] != nullptr && table[b]->first == theKey)//如果有找到，则删除数对，之后对需要移动的元素进行移动
//     {
//         delete table[b];//删除
//         dSize--;
//         table[b] = nullptr;
//         //检查之后有没有元素需要移动
//         int iter = (b + 1) % divisor;
//         while(table[iter] != nullptr)//如果之后有元素，则检查它的初始桶是否为空。若空则置入，否则线性探查，选择合适的桶。
//         {
//             int address = hash(table[iter]->first) % divisor;
//             if(address < iter)//满足移动的条件
//             {
//                 while(table[address] != nullptr && address < iter)
//                 {
//                     address = (address + 1) % divisor;
//                 }
//                 if(address == iter) break;
//                 else
//                 {
//                     table[address] = table[iter];
//                     table[iter] = nullptr;
//                     iter = (iter + 1) % divisor;
//                 }
//             }
//             else break;
//         }
//         // //检查在删除位置之前的元素需不需要移动
//         // int checkIndex = (iter + 1) % divisor;
//         // for(; checkIndex != b; checkIndex = (checkIndex + 1) % divisor)
//         // {
//         //     if(table[checkIndex] != nullptr)
//         //     {
//         //         int initialBucket = hash(table[checkIndex]->first) % divisor;
//         //         if(table[initialBucket] == nullptr)
//         //         {
//         //             table[initialBucket] = table[checkIndex];
//         //             table[checkIndex] = nullptr;
//         //         }
//         //     }
//         // }
//     }
// }

// template<class K, class E>
// void hashTable<K, E>::erase(const K& theKey)
// {//将关键字对应数对从hashTable中删除
//     int deleteIndex = search(theKey);
//     if(table[deleteIndex] != nullptr && table[deleteIndex]->first == theKey)
//     {//若找到数对则删除
//         delete table[deleteIndex];
//         dSize--;
//         table[deleteIndex] = nullptr;
//         //检查是否有需要移动的元素
//         int iter = (deleteIndex + 1) % divisor;//當前考察的元素
//         while(iter < deleteIndex || iter > deleteIndex)//對散列表進行檢查
//         {//检查散列表中所有元素的情况
//             int initialBucket = hash(table[iter]->first) % divisor;//当前处理元素的初始桶
//             int currentBucket = initialBucket;
//             if(iter > initialBucket || iter < initialBucket)
//             {//线性探查选择一个合适的桶
//                 while(table[currentBucket] != nullptr)
//                     currentBucket = (currentBucket + 1) % divisor;
//                 if(currentBucket == initialBucket)
//                 {
//                     iter = (iter + 1) % divisor;
//                     continue;
//                 }
//                 table[currentBucket] = table[iter];
//                 table[iter] = nullptr;
//                 iter = (iter + 1) % divisor;
//                 continue;
//             }
//             else
//             {
//                 iter = (iter + 1) % divisor;
//                 continue;
//             }
//         }
//     }
// }

template<class K, class E>
void hashTable<K, E>::output(ostream& out)const
{
    for(int i = 0; i < divisor; i++)
    {
        if(table[i] != nullptr)
            out << endl << table[i]->first << " : " << table[i]->second << endl;
        else
            out << endl << "NULL\n";
    }
}

template<class K, class E>
ostream& operator<<(ostream& out, const hashTable<K, E>& ht)
{
    ht.output(out);
    return out;
}