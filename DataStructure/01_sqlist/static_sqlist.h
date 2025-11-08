#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H
#include <iterator>
#include <initializer_list>

template<typename T, int MAX_SIZE>

class StaticSqlist
{
public:
    // 构造函数
    StaticSqlist() = default;
    StaticSqlist(std::initializer_list<T> init)
    {
        for (const auto& item : init)
        {
            if (!push_back(item)) break;
        }
    }

    // 尾插 O(1)
    bool push_back(T x)
    { 
        if (n >= MAX_SIZE) return false;
        data[n++] = std::move(x);
        return true;
    }
    // 头插 O(N)
    bool push_front(T x)
    {
        if (n >= MAX_SIZE) return false;
        for(int i = n; i > 0; i--) data[i] = std::move(data[i - 1]);
        data[0] = std::move(x); 
        n++;
        return true;
    }
    // 任意位置插入 O(N)
    bool insert(int pos, T x)
    {
        if (n >= MAX_SIZE || pos < 0 || pos > n) return false;
        for(int i = n; i > pos; i--) data[i] = std::move(data[i - 1]);
        data[pos] = std::move(x); n++;
        return true;
    }
    // 尾删O(1)
    bool pop_back()
    {
        if (n == 0) return false;
        n--;
        return true;
    }
    // 头删 O(N)
    bool pop_front()
    {
        if (n == 0) return false;
        for(int i = 1; i < n; i++)
        {
            data[i - 1] = std::move(data[i]);
        }
        n--;
        return true;
    }
    // 任意位置删除 O(N)
    bool erase(int pos)
    {
        if (pos < 0 || pos >= n) return false;
        for(int i = pos + 1; i < n; i++)
        {
            data[i - 1] = std::move(data[i]);
        }
        n--;
        return true;
    }

    // 访问元素
    T& back() { return n ? data[n - 1] : T(); }
    const T& back() const { return n ? data[n - 1] : T(); }
    T& front() { return n ? data[0] : T(); }
    const T& front() const { return n ? data[0] : T(); }

    // 按值查找
    int find(T x)
    {
        for(int i = 0; i < n; i++)
        {
            if (data[i] == x) return i;
        }
        return -1;
    }

    // 按位查找
    T& at(int index)
    {
        if (index < 0 || index >= n) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    const T& at(int index) const
    {
        if (index < 0 || index >= n) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    // 判断元素是否存在
    bool contains(T x)
    {
        return find(x) != -1;
    }

    // 某元素个数
    int count(T x)
    {
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (data[i] == x) cnt++;
        }
        return cnt;
    }

    // 按位修改
    bool set(int index, T x)
    {
        if (index < 0 || index >= n) return false;
        data[index] = x;
        return true;
    }

    // 批量插入
    template<typename InputIterator>
    bool insert_range(int pos, InputIterator first, InputIterator last)
    {
        int len = std::distance(first, last);
        if (n + len > MAX_SIZE || pos < 0 || pos > n) return false;
        for (int i = n - 1; i >= pos; i--)
        {
            data[i + len] = std::move(data[i]);
        }
        std::copy(first, last, data + pos);
        n += len;
        return true;
    }
    bool insert_range(int pos, std::initializer_list<T> init) { return insert_range(pos, init.begin(), init.end()); }
    bool insert_range(int pos, const StaticSqlist& other) { return insert_range(pos, other.begin(), other.end()); }
    bool insert_range(int pos, const T* arr, int len) { return insert_range(pos, arr, arr + len); }
    // 批量添加
    template<typename InputIterator>
    bool append(InputIterator first, InputIterator last)
    {
        for (auto it = first; it != last; ++it)
        {
            if (!push_back(*it)) return false;
        }
        return true;
    }
    bool append(std::initializer_list<T> init) { return append(init.begin(), init.end()); }
    bool append(const StaticSqlist& other) { return append(other.begin(), other.end()); }
    bool append(const T* arr, int len) { return append(arr, arr + len); }
    // 批量删除
    bool erase_range(int pos, int len)
    {
        if (pos < 0 || len <= 0 || pos + len > n) return false;
        for (int i = pos + len; i < n; i++)
        {
            data[i - len] = std::move(data[i]);
        }
        n -= len;
        return true;
    }

    // 清空操作
    void clear() { n = 0; }

    // 容量相关
    int size() const noexcept { return n; }
    bool empty() const noexcept { return n == 0; }
    int capacity() const noexcept { return MAX_SIZE; }

    // 交换容器
    void swap(StaticSqlist& other)
    {
        int min_size = n < other.n ? n : other.n;
        for (int i = 0; i < min_size; i++)
        {
            std::swap(data[i], other.data[i]);
        }
        if (n > other.n)
        {
            for (int i = min_size; i < n; i++)
            {
                other.data[i] = std::move(data[i]);
            }
        }
        else if (n < other.n)
        {
            for (int i = min_size; i < other.n; i++)
            {
                data[i] = std::move(other.data[i]);
            }
        }
        std::swap(n, other.n);
    }

    // 迭代器
    T* begin() { return data; }
    T* end() { return data + n; }
    const T* begin() const { return data; }
    const T* end() const { return data + n; }
    const T* cbegin() const { return data; }
    const T* cend() const { return data + n; }

    // 反向迭代器
    using reverse_iterator = std::reverse_iterator<T*>;
    using const_reverse_iterator = std::reverse_iterator<const T*>;
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    // 运算符重载
    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }

    // 拷贝和移动相关
    StaticSqlist(const StaticSqlist& other)
    {
        n = other.n;
        std::copy(other.begin(), other.end(), begin());
    }

    StaticSqlist& operator=(const StaticSqlist& other)
    {
        if (this != &other)
        {
            n = other.n;
            std::copy(other.begin(), other.end(), begin());
        }
        return *this;
    }

    StaticSqlist(StaticSqlist&& other) noexcept
    {
        n = other.n;
        std::move(other.begin(), other.end(), begin());
        other.n = 0;
    }

    StaticSqlist& operator=(StaticSqlist&& other) noexcept
    {
        if (this != &other)
        {
            n = other.n;
            std::move(other.begin(), other.end(), begin());
            other.n = 0;
        }
        return *this;
    }

private:
    T data[MAX_SIZE]; // 静态数组存储空间
    int n = 0; // 标记有效元素个数
};


#endif // STATIC_ARRAY_H