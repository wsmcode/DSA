#include <iostream>
#include "static_sqlist.h"
#include "dynamic_sqlist.h"
#include <array>
#include <vector>

const int N = 1e6 + 10;
StaticSqlist<int, N> array;
DynamicSqlist<int> dynamicArray;


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

void printDynamicArray()
{
    for (auto it = dynamicArray.begin(); it != dynamicArray.end(); it++)
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

    // 按值查找
    for (int i = 0; i <= 10; i++)
    {
        std::cout << "查找" << i << ": " << array.find(i) << std::endl;
    }
    // 按位置查找
    for (int i = 0; i < array.size(); i++)
    {
        std::cout << "查找位置" << i << ": " << array.at(i) << std::endl;
    }

    std::cout << "查找首位元素: " << array.front() << std::endl;
    std::cout << "查找尾位元素: " << array.back() << std::endl;
}

void test_dynamic_array()
{
    std::cout << "容量: "  << dynamicArray.capacity() << ", 大小: " << dynamicArray.size() << std::endl;
    // 测试尾插
    std::cout << "尾插" << std::endl;
    dynamicArray.push_back(2);
    printDynamicArray();
    dynamicArray.push_back(5);
    printDynamicArray();
    dynamicArray.push_back(1);
    printDynamicArray();
    dynamicArray.push_back(3);
    printDynamicArray();
    std::cout << "容量: "  << dynamicArray.capacity() << ", 大小: " << dynamicArray.size() << std::endl;

    // 测试头插
    std::cout << "头插" << std::endl;
    dynamicArray.push_front(10);
    printDynamicArray();

    // 测试任意位置插入
    std::cout << "任意位置插入" << std::endl;
    dynamicArray.insert(2, 20);
    printDynamicArray();
    std::cout << "容量: "  << dynamicArray.capacity() << ", 大小: " << dynamicArray.size() << std::endl;

    // 测试批量插入
    std::cout << "批量插入" << std::endl;
    dynamicArray.insert_range(1, {30, 40, 50});
    printDynamicArray();

    // 测试批量添加
    std::cout << "批量添加" << std::endl;
    dynamicArray.append({60, 70, 80});
    printDynamicArray();

    // // 测试批量删除
    // std::cout << "批量删除" << std::endl;
    // dynamicArray.erase_range(1, 3);
    // printDynamicArray();

    // 测试尾删
    // std::cout << "尾删" << std::endl;
    // dynamicArray.pop_back();
    // printDynamicArray();
    // dynamicArray.pop_back();
    // printDynamicArray();

    // // 测试头删
    // std::cout << "头删" << std::endl;
    // dynamicArray.pop_front();
    // dynamicArray.pop_front();
    // printDynamicArray();

    // 测试任意位置删除
    // std::cout << "任意位置删除" << std::endl;
    // dynamicArray.erase(2);
    // printDynamicArray();
    // dynamicArray.remove(1);
    // printDynamicArray();
    // dynamicArray.remove(3);
    // printDynamicArray();

    // // 按值查找
    // for (int i = 0; i <= 10; i++)
    // {
    //     std::cout << "查找" << i << ": " << dynamicArray.find(i) << std::endl;
    // }
    // // 按位置查找
    // for (int i = 0; i < dynamicArray.size(); i++)
    // {
    //     std::cout << "查找位置" << i << ": " << dynamicArray.at(i) << std::endl;
    // }

    // std::cout << "查找首位元素: " << dynamicArray.front() << std::endl;
    // std::cout << "查找尾位元素: " << dynamicArray.back() << std::endl;

}

int main()
{
    // test_static_array();
    test_dynamic_array();
	return 0;
}
