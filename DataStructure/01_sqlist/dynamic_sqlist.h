#ifndef DYNAMIC_SQLIST_H
#define DYNAMIC_SQLIST_H
#include <iterator>
#include <initializer_list>

template <typename T>
class DynamicSqlist
{
public:
    // 构造函数
    DynamicSqlist() = default;
    DynamicSqlist(int capacity) : capacity_(capacity), size_(0), data_(new T[capacity]) {}
    DynamicSqlist(std::initializer_list<T> init)
    {
        for (const auto & item : init)
        {
            push_back(item);
        }
    }
    // 增
    // 尾插 O(1)
    template<typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    void push_back(U&& x)
    {
        if (size_ >= capacity_) resize();
        data_[size_++] = std::forward<U>(x);
    }
    // 头插 O(N)
    template<typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    void push_front(U&& x)
    {
        if (size_ >= capacity_) resize();
        for(int i = size_; i > 0; i--) data_[i] = std::move(data_[i - 1]);
        data_[0] = std::forward<U>(x);
        size_++;
    }
    // 任意位置插入
    template<typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    void insert(int index, U&& x)
    {
        if (index < 0 || index > size_) return;
        if (size_ >= capacity_) resize();
        for(int i = size_; i > index; i--) data_[i] = std::move(data_[i - 1]);
        data_[index] = std::forward<U>(x);
        size_++;
    }

    // 删
    // 尾删 O(1)
    void pop_back()
    {
        if (size_ <= 0) return;
        size_--;
    }
    // 头删 O(N)
    void pop_front()
    {
        if (size_ <= 0) return;
        for (int i = 1; i < size_; i++) data_[i - 1] = std::move(data_[i]);
        size_--;
    }
    // 任意位置删除 O(N)
    void erase(int index)
    {
        if (size_ <= 0 || index < 0 || index >= size_) return;
        for (int i = index + 1; i < size_; i++) data_[i - 1] = std::move(data_[i]);
        size_--;
    }
    void remove(int index) { erase(index); }

    // 改 O(1)
    template<typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    void set(int index, U&& x)
    {
        if (index < 0 || index >= size_) return;
        data_[index] = std::forward<U>(x);
    }

    // 查
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
    // 首尾元素 O(1)
    T& front() { return size_ ? data_[0] : throw std::out_of_range("List is empty"); }
    const T& front() const { return size_ ? data_[0] : throw std::out_of_range("List is empty"); }
    T& back() { return size_ ? data_[size_ - 1] : throw std::out_of_range("List is empty"); }
    const T& back() const { return size_ ? data_[size_ - 1] : throw std::out_of_range("List is empty"); }

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

    // 批量操作
    // 批量插入
    template<typename InputIt>
    bool insert_range(int index, InputIt first, InputIt last)
    {
        if (index < 0 || index > size_) return false;
        int len = std::distance(first, last);
        if (len <= 0) return false;
        while(capacity_ < size_ + len) resize();
        // for (int i = size_ - 1; i >= index; i--) data_[i + len] = std::move(data_[i]);
        if (index < size_) std::copy_backward(data_ + index, data_ + size_, data_ + size_ + len);
        std::copy(first, last, data_ + index);
        size_ += len;
        return true;
    }
    bool insert_range(int index, std::initializer_list<T> init) { return insert_range(index, init.begin(), init.end()); }
    bool insert_range(int index, const DynamicSqlist& other) { return insert_range(index, other.begin(), other.end()); }
    bool insert_range(int index, const T* arr, int len) { return insert_range(index, arr, arr + len); }
    // 批量添加
    template<typename InputIt>
    void append(InputIt first, InputIt last)
    {
        for (auto it = first; it != last; ++it) push_back(*it);
    }
    void append(std::initializer_list<T> init) { append(init.begin(), init.end()); }
    void append(const DynamicSqlist& other) { append(other.begin(), other.end()); }
    void append(const T* arr, int len) { append(arr, arr + len); }
    // 批量删除
    bool erase_range(int index, int len = -1)
    {
        if (len == -1) len = size_ - index;
        if (index < 0 || index >= size_ || len <= 0 || index + len > size_) return false;
        for (int i = index + len; i < size_; i++) data_[i - len] = std::move(data_[i]);
        size_ -= len;
        return true;
    }
    bool remove_range(int index, int len) { return erase_range(index, len); }

    // 清空操作
    void clear()
    {
        size_ = 0;
        capacity_ = 0;
        delete[] data_;
        data_ = nullptr;
    }

    // 容量相关
    int capacity() const noexcept { return capacity_; }
    int size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    // 交换容器
    void swap(DynamicSqlist& other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
    }
    friend void swap(DynamicSqlist& a, DynamicSqlist& b) noexcept { a.swap(b); }

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
    DynamicSqlist(const DynamicSqlist& other) : capacity_(other.capacity_), size_(other.size_), data_(new T[capacity_])
    {
        std::copy(other.data_, other.data_ + size_, data_);
    }
    DynamicSqlist& operator=(const DynamicSqlist& other)
    {
        if (this != &other)
        {
            DynamicSqlist temp(other);
            swap(temp);
        }
        return *this;
    }
    DynamicSqlist(DynamicSqlist&& other) noexcept
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    DynamicSqlist& operator=(DynamicSqlist&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            data_ = other.data_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

private:
    // 动态扩容
    void resize()
    {
        if (capacity_ == 0)
        {
            capacity_ = 1;
            data_ = new T[capacity_];
            return;
        }
        capacity_ *= 2;
        T *newData = new T[capacity_];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
    }

    T* data_ = nullptr; // 接收 new 出来的数组地址
    int capacity_ = 0; // 标记当前数组的实际大小
    int size_ = 0; // 标记有效元素个数
};


#endif // DYNAMIC_SQLIST_H