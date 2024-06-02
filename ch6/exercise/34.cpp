//編寫circularList<T>::merge(), 且函數執行完畢后輸入的鏈表a，b變為空， 即使用a, b的節點空間完成（或需要把a，b鏈條清除）
#include"29.cpp"

int main()
{
    circularList<int> a, b, c;
    for(int i = 0; i < 10; i++)
    {
        a.insert(i, i+1);
        b.insert(i, i+1);
    }
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl;
    c.merge(a, b);
    std::cout << "a:" << a << std::endl << "b:" << b << std::endl;
    std::cout << "after merge:\n";
    std::cout << "c:" << c << std::endl;
    std::cout << "a.listSize:" << a.size() << std::endl;
    std::cout << "b.listSize:" << b.size() << std::endl;
    std::cout << "c.listSize:" << c.size() << std::endl;

    std::cout << "some test on c:\n";
    std::cout << c.get(19) << std::endl;
    // std::cout << "indexOf(3):" << c.indexOf(3);
    // c.push_back(26);
    // std::cout << "erase index 0:\n";
    // c.erase(0);
    // std::cout << "c:" << c << std::endl;
    // std::cout << "erase last element:\n";
    // c.erase(c.size()-1);
    // std::cout << "c:" << c << std::endl;
    // std::cout << "push_back operation:\n";
    // c.push_back(26);
    // std::cout << "c:" << c << std::endl;
    // std::cout << "insert at index 0:\n";
    // c.insert(0, 26);
    // std::cout << "c:" << c << std::endl;
    // std::cout << "**insert at last place:\n";
    // c.insert(c.size(), 88);
    // std::cout << "c:" << c << std::endl;
    // std::cout << "clear operation:\n";
    // c.clear();
    // std::cout << "c:" << c << std::endl;
    // std::cout << "push_back after clear operation:\n";
    // c.push_back(26);
    // std::cout << "c:" << c << std::endl;
    // std::cout << "insert at index 0 after clear operation:\n";
    // c.insert(0, -1);
    // std::cout << "c:" << c << std::endl;
    // std::cout << "insert at last place after clear operation:\n";
    // c.insert(c.size(), 100);
    // std::cout << "c:" << c << std::endl;

    // std::cout << "c.listSize:" << c.size() << std::endl;
    // std::cout << "indexOf(10):" << c.indexOf(10); 
}