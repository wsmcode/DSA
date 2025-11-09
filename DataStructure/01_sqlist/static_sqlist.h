#ifndef STATIC_SQLIST_H
#define STATIC_SQLIST_H
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
    template<typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    bool push_back(U&& x)
    {
        if (size_ >= MAX_SIZE) return false;
        data_[size_++] = std::forward<U>(x);
        return true;
    }
    // 头插 O(N)
    template<typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    bool push_front(U&& x)
    {
        if (size_ >= MAX_SIZE) return false;
        for(int i = size_; i > 0; i--) data_[i] = std::move(data_[i - 1]);
        data_[0] = std::forward<U>(x);
        size_++;
        return true;
    }
    // 任意位置插入 O(N)
    template<typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    bool insert(int pos, U&& x)
    {
        if (size_ >= MAX_SIZE || pos < 0 || pos > size_) return false;
        for(int i = size_; i > pos; i--) data_[i] = std::move(data_[i - 1]);
        data_[pos] = std::forward<U>(x); size_++;
        return true;
    }
    // 尾删O(1)
    bool pop_back()
    {
        if (size_ == 0) return false;
        size_--;
        return true;
    }
    // 头删 O(N)
    bool pop_front()
    {
        if (size_ == 0) return false;
        for(int i = 1; i < size_; i++) data_[i - 1] = std::move(data_[i]);
        size_--;
        return true;
    }
    // 任意位置删除 O(N)
    bool erase(int index)
    {
        if (index < 0 || index >= size_) return false;
        for(int i = index + 1; i < size_; i++)
        {
            data_[i - 1] = std::move(data_[i]);
        }
        size_--;
        return true;
    }
    bool remove(int index) { return erase(index); }

    // 访问元素 O(1)
    T& front() { return size_ ? data_[0] : throw std::out_of_range("List is empty"); }
    const T& front() const { return size_ ? data_[0] : throw std::out_of_range("List is empty"); }
    T& back() { return size_ ? data_[size_ - 1] : throw std::out_of_range("List is empty"); }
    const T& back() const { return size_ ? data_[size_ - 1] : throw std::out_of_range("List is empty"); }

    // 按值查找 O(N)
    int find(T x)
    {
        for(int i = 0; i < size_; i++)
        {
            if (data_[i] == x) return i;
        }
        return -1;
    }

    // 按位查找 O(1)
    T& at(int index)
    {
        if (index < 0 || index >= size_) throw std::out_of_range("Index out of bounds");
        return data_[index];
    }
    const T& at(int index) const
    {
        if (index < 0 || index >= size_) throw std::out_of_range("Index out of bounds");
        return data_[index];
    }

    // 判断元素是否存在 O(N)
    bool contains(T x) { return find(x) != -1; }

    // 某元素个数 O(N)
    int count(T x)
    {
        int cnt = 0;
        for (int i = 0; i < size_; i++)
        {
            if (data_[i] == x) cnt++;
        }
        return cnt;
    }

    // 按位修改 O(1)
    template<typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    bool set(int index, U&& x)
    {
        if (index < 0 || index >= size_) return false;
        data_[index] = std::forward<U>(x);
        return true;
    }

    // 批量插入 O(N)
    template<typename InputIt>
    bool insert_range(int index, InputIt first, InputIt last)
    {
        int len = std::distance(first, last);
        if (size_ + len > MAX_SIZE || index < 0 || index > size_) return false;
        for (int i = size_ - 1; i >= index; i--) data_[i + len] = std::move(data_[i]);
        std::copy(first, last, data_ + index);
        size_ += len;
        return true;
    }
    bool insert_range(int index, std::initializer_list<T> init) { return insert_range(index, init.begin(), init.end()); }
    bool insert_range(int index, const StaticSqlist& other) { return insert_range(index, other.begin(), other.end()); }
    bool insert_range(int index, const T* arr, int len) { return insert_range(index, arr, arr + len); }
    // 批量添加 O(N)
    template<typename InputIt>
    bool append(InputIt first, InputIt last)
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
    // 批量删除 O(N)
    bool erase_range(int index, int len = -1)
    {
        if (len == -1) len = size_ - index;
        if (index < 0 || index >= size_ || len <= 0 || index + len > size_) return false;
        for (int i = index + len; i < size_; i++) data_[i - len] = std::move(data_[i]);
        size_ -= len;
        return true;
    }
    bool remove_range(int index, int len) { return erase_range(index, len); }

    // 清空操作 O(1)
    void clear() { size_ = 0; }

    // 容量相关 O(1)
    int size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    int capacity() const noexcept { return MAX_SIZE; }

    // 交换容器 O(N)
    void swap(StaticSqlist& other)
    {
        int min_size = std::min(size_, other.size_);
        for (int i = 0; i < min_size; i++) std::swap(data_[i], other.data_[i]);
        if (size_ > other.size_)
        {
            for (int i = min_size; i < size_; i++) other.data_[i] = std::move(data_[i]);
        }
        else if (size_ < other.size_)
        {
            for (int i = min_size; i < other.size_; i++) data_[i] = std::move(other.data_[i]);
        }
        std::swap(size_, other.size_);
    }
    friend void swap(StaticSqlist& a, StaticSqlist& b) noexcept { a.swap(b); }

    // 迭代器
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }
    const T* cbegin() const { return data_; }
    const T* cend() const { return data_ + size_; }

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
    T& operator[](int index) { return data_[index]; }
    const T& operator[](int index) const { return data_[index]; }

    // 拷贝和移动相关
    StaticSqlist(const StaticSqlist& other)
    {
        size_ = other.size_;
        std::copy(other.begin(), other.end(), begin());
    }

    StaticSqlist& operator=(const StaticSqlist& other)
    {
        if (this != &other)
        {
            size_ = other.size_;
            std::copy(other.begin(), other.end(), begin());
        }
        return *this;
    }

    StaticSqlist(StaticSqlist&& other) noexcept
    {
        size_ = other.size_;
        std::move(other.begin(), other.end(), begin());
        other.size_ = 0;
    }

    StaticSqlist& operator=(StaticSqlist&& other) noexcept
    {
        if (this != &other)
        {
            size_ = other.size_;
            std::move(other.begin(), other.end(), begin());
            other.size_ = 0;
        }
        return *this;
    }

private:
    T data_[MAX_SIZE]; // 静态数组存储空间
    int size_ = 0; // 标记有效元素个数
};


#endif // STATIC_SQLIST_H