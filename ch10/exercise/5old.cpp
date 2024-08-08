//用数组定义C++类sortedArrayList， 它与sortedChain具有相同的成员方法。编写和测试所有的函数代码
// #include<utility>
#include"../case/10-1.h"
#include"../../Tool.h"
#include<sstream>
using namespace std;

//circularArraySortedList
template<class K, class E>
class sortedArrayList:public dictionary<K, E>
{
    public:
        sortedArrayList(int initialCapacity = 10);
        sortedArrayList(const sortedArrayList<K, E>&);
        ~sortedArrayList(){if(dict) delete[] dict;}
        bool empty()const{ return first == last;}
        int size()const{ return dSize;}
        pair<const K, E>* find(const K&)const{cout << "unimplentation\n";}
        pair<const K, E>* find(const K&, int k, int m)const;
        void insert(const pair<const K, E>&);
        void erase(const K&);
    protected:
        pair<const K, E>* dict;
        int first;//表示首节点
        int last;//表示尾节点
        int arrayLength;//描述字典数组的容量
        int dSize;//描述字典中元素的个数
};

template<class K, class E>
sortedArrayList<K, E>::sortedArrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream os;
        os << "initialCapacity = " << initialCapacity << " must be > 0";
        throw illegalParameter(os.str());
    }
    dict = new pair<const K, E>[initialCapacity];
    first = 0;
    last = 0;
    arrayLength = initialCapacity;
    dSize = 0;
}

template<class K, class E>
sortedArrayList<K, E>::sortedArrayList(const sortedArrayList<K, E>& theSal)
{
    arrayLength = theSal.arrayLength;
    dict = new pair<const K, E>[arrayLength];
    dSize = theSal.dSize;
    int index = 1;
    int iter;
    for(iter = theSal.first; iter != theSal.last; iter = (iter + 1) % theSal.arrayLength)
        dict[index++] = theSal.dict[iter];
    //复制最后一个元素
    dict[index] = theSal.dict[iter];
    first = 1;
    last = index;
    return;
}

//k代表左端，m代表右端
template<class K, class E>
pair<const K, E>*  sortedArrayList<K, E>::find(const K& theKey, int l, int r)const
{//折半查找
    int k = (first + l) % arrayLength;
    int m = (first + r) % arrayLength;
    int targetIndex;
    int distance = (m - k + arrayLength) % arrayLength;
    targetIndex = (targetIndex + distance / 2) % arrayLength;
    //查找失败
    if(m == k && dict[k].first != theKey) return nullptr;
    if(dict[targetIndex].first == theKey)
    //查找成功
        return &dict[targetIndex];
    //向右端查询
    else if(dict[targetIndex].first < theKey)
        find(theKey, (targetIndex + 1) % arrayLength, m);
    //向左端查询
    else //(dict[targetIndex].first > theKey)
        find(theKey, k, (targetIndex - 1 + arrayLength) % arrayLength);
}

template<class K, class E>
void sortedArrayList<K, E>::insert(const pair<const K, E>& thePair)
{//插入到一个合适的位置
    //如果数组中已有键值thePair.first，则更新键值对应的值
    pair<const K, E>* target = find(thePair.first, first, last);
    if(target != nullptr)
    {
        target->second = thePair.second;
        return;
    }
    //若没有则插入数对
    else
    {//移动数组中的元素
    //判断数组是否有足够的空间
        if(dSize + 1 == arrayLength)
        {//扩容
            pair<const K, E>* newDict = new pair<const K, E>[arrayLength * 2];
            int index = 1, iter;
            for(iter = (first + 1) % arrayLength; dict[iter].first < target->first; iter = (iter + 1) % arrayLength)
            {
                newDict[index++] = dict[iter];
                // // newDict[index].first = dict[iter].first;
                // // newDict[index].second = dict[iter].second;
                // index++;
            }
            newDict[index++] = thePair;
            // newDict[index].first = dict[iter].first;
            // newDict[index].second = dict[iter].second;
            //复制其余元素
            for(; iter != last; iter = (iter + 1) % arrayLength)
                newDict[index++] = dict[iter];
            newDict[index] = dict[last];
            dSize++;
            first = 0;
            last = index;
            arrayLength *= 2;
            delete[] dict;
            dict = newDict;
            return;
        }
        //移动元素
        int iter;
        for(iter = first; dict[iter].first < thePair.first; iter = (iter + 1) % arrayLength);
        int peak = iter;
        int sizeL = (iter - first + arrayLength) % arrayLength;
        int sizeR = (last - iter + arrayLength) % arrayLength;
        if(sizeL < sizeR)
        {//移动左边的元素
            for(iter = (first+1) % arrayLength; iter != peak; iter = (iter + 1) % arrayLength)
                dict[(iter - 1 + arrayLength) % arrayLength] = dict[iter];
            first = (first - 1 + arrayLength) % arrayLength;
        }
        else
        {
            for(iter = last; iter != peak; iter = (iter - 1 + arrayLength) % arrayLength)
                dict[(iter + 1) % arrayLength] = dict[iter];
            last = (last + 1) % arrayLength;
        }
        dict[peak] = thePair;
        dSize++;
    }    
}

template<class K, class E>
void sortedArrayList<K, E>::erase(const K& theKey)
{//删除键值为theKey的数对
    if(first == last) return;
    pair<const K, E>* target = find(theKey);
    if(target == nullptr)
    //查找失败
        return;
    int iter = (first + 1) % arrayLength, index = 0;
    for(; dict[iter].first < theKey; iter = (iter + 1) % arrayLength, index++);
    if(index < dSize / 2)
    {//移动左边
        for(iter = index; iter != first; iter = (iter - 1 + arrayLength) % arrayLength)
            dict[iter] = dict[(iter-1+arrayLength) % arrayLength];
        //1 2 3
        dict[first].~pair<const K, E>();
        first = (first + 1) % arrayLength;
    }
    else
    {//移到右边
        for(iter = index; iter != last; iter = (iter + 1) % arrayLength)
            dict[iter] = dict[(iter + 1) % arrayLength];
        //1 2 3
        dict[last].~pair<const K, E>();
        last = (last - 1 + arrayLength) % arrayLength;        
    }
    return;
}

int main()
{
    sortedArrayList<char, int> sal;
    int i = 0;
    for(char ch = 'a'; ch < 'A'; ch++, i++)
        sal.insert(pair<const char, int>(ch, i));
    for(int ch = 'a'; ch < 'A'; ch++)
        cout << sal.find(ch, 1, 26)->second << " ";
}

