#include <iostream>
#include "static_sqlist.h"
#include <array>

const int N = 1e6 + 10;
StaticSqlist<int, N> array;

void printStaticArray()
{
    // 方式1
    // for (int i = 0; i < array.size(); i++)
    // {
    //     std::cout << array[i] << " ";
    // }

    // 方式2
    // for (auto & a : array)
    // {
    //     std::cout << a << " ";
    // }
    
    // 方式3
    for (auto it = array.begin(); it != array.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void test_static_array()
{
    // 测试尾插
    std::cout << "尾插" << std::endl;
    array.push_back(2);
    printStaticArray();
    array.push_back(5);
    printStaticArray();
    array.push_back(1);
    printStaticArray();
    array.push_back(3);
    printStaticArray();

    // 测试头插
    std::cout << "头插" << std::endl;
    array.push_front(10);
    printStaticArray();

    // 测试任意位置插入
    std::cout << "任意位置插入" << std::endl;
    array.insert(2, 20);
    printStaticArray();

    // 测试批量插入
    std::cout << "批量插入" << std::endl;
    array.insert_range(1, {30, 40, 50});
    printStaticArray();
    
    // 测试批量添加
    std::cout << "批量添加" << std::endl;
    array.append({60, 70, 80});
    printStaticArray();

    // 测试批量删除
    std::cout << "批量删除" << std::endl;
    array.erase_range(1, 3);
    printStaticArray();

    // // 测试尾删
    // std::cout << "尾删" << std::endl;
    // array.pop_back();
    // printStaticArray();
    // array.pop_back();
    // printStaticArray();

    // // 测试头删
    // std::cout << "头删" << std::endl;
    // array.pop_front();
    // array.pop_front();
    // printStaticArray();

    // // 测试任意位置删除
    // std::cout << "任意位置删除" << std::endl;
    // array.erase(2);
    // printStaticArray();
    // array.erase(1);
    // printStaticArray();
    // array.erase(3);
    // printStaticArray();

    // for (int i = 0; i <= 10; i++)
    // {
    //     std::cout << "查找" << i << ": " << array.find(i) << std::endl;
    // }
}

int main()
{
    test_static_array();
	return 0;
}
