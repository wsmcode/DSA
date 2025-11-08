#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <typename T>
class DynamicSqlist
{
public:


private:
    T* data; // 接收 new 出来的数组地址
    int capacity; // 标记当前数组的实际大小
    int n = 0; // 标记有效元素个数
};


#endif // DYNAMIC_ARRAY_H