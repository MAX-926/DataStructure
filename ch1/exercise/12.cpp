template<class T>
void make2dArray_wideUse(T ** &x, int numberOfRows, int rowSize[])
{
    x = new T*[numberOfRows];
    for(int i = 0; i < numberOfRows; i++)
        x[i] = new T[rowSize[i]];
    return;
}