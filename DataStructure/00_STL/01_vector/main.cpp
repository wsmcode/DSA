#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using VectorInt = std::vector<int>;

void printVector(const VectorInt& vec, std::string msg = "", std::string empty = "<empty>")
{
    std::string prefix = !msg.empty() ? msg + ": " : "";

    std::cout << prefix << "{ ";
    if (vec.empty()) std::cout << empty << " ";
    else for(int val : vec) std::cout << val << " ";
    std::cout << "}" << std::endl;
}

// vector 初始化构造
void constructorDemo()
{
    // 1. 创建 vector
    VectorInt vec1;                             // 默认构造 - 空 vector
    VectorInt vec2(10);                         // 指定大小 - 10 个元素，默认初始化为 0
    VectorInt vec3(10, 5);                      // 指定大小和初始值 - 10 个元素，初始值为 5
    VectorInt vec4 = {1, 2, 3, 4, 5};           // 从初始化列表构造 - 5 个元素，初始值为 1, 2, 3, 4, 5
    VectorInt vec5({6, 7, 8, 9, 10});           // 从初始化列表构造 - 5 个元素，初始值为 6, 7, 8, 9, 10
    VectorInt vec6(vec4.begin(), vec4.end());   // 从迭代器范围构造 - 5 个元素，初始值为 1, 2, 3, 4, 5
    VectorInt vec7(vec4);                       // 拷贝构造 - 5 个元素，初始值为 1, 2, 3, 4, 5
    VectorInt vec8(std::move(vec4));            // 移动构造 - 5 个元素，初始值为 1, 2, 3, 4, 5

    VectorInt vec9[5];                          // 默认构造 - 5 个空 vector
    std::vector<VectorInt> vec10(5);            // 默认构造 - 5 个空 vector 同上

    // !注意：vec4 在移动后变为一个空的 vector
    std::cout << "vec4 size: " << vec4.size() << std::endl; // 输出 vec4 的大小

    printVector(vec2, "[ vec2(10)                       ]");
    printVector(vec3, "[ vec3(10, 5)                    ]");
    printVector(vec4, "[ vec4 = {1, 2, 3, 4, 5}         ]", "<移动后为空的 vector>");
    printVector(vec5, "[ vec5({6, 7, 8, 9, 10})         ]");
    printVector(vec6, "[ vec6(vec4.begin(), vec4.end()) ]");
    printVector(vec7, "[ vec7(vec4)                     ]");
    printVector(vec8, "[ vec8(std::move(vec4))          ]");
}
// vector 容量管理
void capacityDemo()
{
    VectorInt vec;
    std::cout << "初始状态: " << std::endl;
    std::cout << "大小: " << vec.size() << ", 容量: " << vec.capacity() << ", empty: " << (vec.empty() ? "true" : "false") << std::endl;
    // 添加元素
    std::cout << "默认resize策略下添加元素: " << std::endl;
    for (int i = 0; i < 9; ++i)
    {
        vec.push_back(i);
        std::cout << "添加元素 " << i << ": 大小: " << vec.size() << ", 容量: " << vec.capacity() << std::endl;
    }
    // 预留空间
    vec.reserve(20);
    std::cout << "reserve(20)预留空间后: " << std::endl;
    std::cout << "大小: " << vec.size() << ", 容量: " << vec.capacity() << ", empty: " << (vec.empty() ? "true" : "false") << " [";
    for (const auto& val : vec) std::cout << val << " ";
    std::cout << "]" << std::endl;
    // 调整大小
    vec.resize(15); // 调整大小为 15, 新增元素初始化为 0
    std::cout << "resize(15)调整大小后: " << std::endl;
    std::cout << "大小: " << vec.size() << ", 容量: " << vec.capacity() << ", empty: " << (vec.empty() ? "true" : "false") << " [";
    for (const auto& val : vec) std::cout << val << " ";
    std::cout << "]" << std::endl;

    vec.resize(20, 100); // 新增元素初始化为 100
    std::cout << "resize(20, 100)调整大小后: " << std::endl;
    std::cout << "大小: " << vec.size() << ", 容量: " << vec.capacity() << ", empty: " << (vec.empty() ? "true" : "false") << " [";
    for (const auto& val : vec) std::cout << val << " ";
    std::cout << "]" << std::endl;

    while (vec.size() > 10) vec.pop_back();
    std::cout << "pop_back()后: " << std::endl;
    std::cout << "大小: " << vec.size() << ", 容量: " << vec.capacity() << ", empty: " << (vec.empty() ? "true" : "false") << std::endl;
    // 收缩到合适大小
    vec.shrink_to_fit();
    std::cout << "收缩到合适大小后: " << std::endl;
    std::cout << "大小: " << vec.size() << ", 容量: " << vec.capacity() << ", empty: " << (vec.empty() ? "true" : "false") << " [";
    for (const auto& val : vec) std::cout << val << " ";
    std::cout << "]" << std::endl;

    // 最大可能大小
    std::cout << "最大可能大小: " << vec.max_size() << std::endl;

}
// vector 迭代器
void iteratorDemo()
{
    VectorInt vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "正向迭代:     [ ";
    for (auto it = vec.begin(); it != vec.end(); ++it) std::cout << *it << " ";
    std::cout << "]" << std::endl;
    std::cout << "常量正向迭代: [ ";
    for (auto cit = vec.cbegin(); cit != vec.cend(); ++cit) std::cout << *cit << " ";
    std::cout << "]" << std::endl;

    std::cout << "反向迭代:     [ ";
    for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) std::cout << *rit << " ";
    std::cout << "]" << std::endl;
    std::cout << "常量反向迭代: [ ";
    for (auto crit = vec.crbegin(); crit != vec.crend(); ++crit) std::cout << *crit << " ";
    std::cout << "]" << std::endl;

    std::cout << "----------------- 分隔线 -----------------------" << std::endl;

    const VectorInt constVec = vec;
    std::cout << "常量迭代:     [ ";
    for (auto it = constVec.begin(); it != constVec.end(); ++it) std::cout << *it << " ";
    std::cout << "]" << std::endl;

    std::cout << "常量反向迭代: [ ";
    for (auto crit = constVec.crbegin(); crit != constVec.crend(); ++crit) std::cout << *crit << " ";
    std::cout << "]" << std::endl;

    std::cout << "----------------- 分隔线 -----------------------" << std::endl;

    std::cout << "范围基 for 循环迭代: [ ";
    for (const auto& val : vec) std::cout << val << " ";
    std::cout << "]" << std::endl;

    std::cout << "----------------- 分隔线 -----------------------" << std::endl;
    std::cout << "使用迭代器进行算法操作: " << std::endl;
    std::cout << "查找算法: ";
    auto found = std::find(vec.begin(), vec.end(), 5);
    if (found != vec.end()) std::cout << "找到元素: " << *found << std::endl;
    else std::cout << "未找到元素" << std::endl;
    std::cout << "元素个数: " << std::count(vec.begin(), vec.end(), 5) << std::endl;
    std::cout << "最大元素: " << *std::max_element(vec.begin(), vec.end()) << std::endl;
    std::cout << "最小元素: " << *std::min_element(vec.begin(), vec.end()) << std::endl;
    std::cout << "倒序排序后: ";
    std::sort(vec.rbegin(), vec.rend());
    for (const auto& val : vec) std::cout << val << " ";
    std::cout << std::endl;

}

int main()
{
    // constructorDemo();
    capacityDemo();
    // iteratorDemo();
    return 0;
}