#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如何实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

// 知识点总结：
// 1. 移动语义：转移资源所有权而非复制，提高性能
// 2. 右值引用：&& 用于绑定临时对象
// 3. std::move：将左值转换为右值，允许移动
// 4. 移动后对象状态：应设置为有效但未指定状态（如 nullptr）
// 5. 自移动检查：移动赋值必须检查 this != &other

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // TODO: 实现动态设置容量的构造器
    // ✅ 已实现：分配 capacity 个 size_t，初始化 cache[0]=0, cache[1]=1, cached=2
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2), capacity(capacity) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现移动构造器
    // ✅ 已实现：转移 other 的资源，并将 other 设置为 nullptr 状态
    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr;
        other.cached = 0;
        other.capacity = 0;
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    // ✅ 已实现：1. 检查自移动；2. 释放旧资源；3. 转移新资源；4. 清空 other
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) {
            delete[] cache;
            cache = other.cache;
            cached = other.cached;
            capacity = other.capacity;
            other.cache = nullptr;
            other.cached = 0;
            other.capacity = 0;
        }
        return *this;
    }  

    // TODO: 实现析构器，释放缓存空间
    // ✅ 已实现：使用 delete[] 释放动态数组
    ~DynFibonacci(){
        delete[] cache;
    };

    // TODO: 实现正确的缓存优化斯波那契计算
    // ✅ 已实现：使用 while 循环从 cached 计算到 i，重载 operator[] 运算符
    size_t operator[](int i) {
        if (i >= capacity) {
            throw std::out_of_range("Index out of range");
        }
        while (cached <= i) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
            ++cached;
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
