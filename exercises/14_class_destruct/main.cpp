#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

// 知识点总结：
// 1. 动态内存分配：使用 new/delete 或 new[]/delete[] 管理堆内存
// 2. 析构函数：在对象销毁时释放资源
// 3. RAII 机制：资源获取即初始化，通过析构自动释放资源

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // 修改思路：分配 capacity 个 size_t，初始化 cached=2
    // DynFibonacci(int capacity): cache(new ?), cached(?) {}  // 原始代码
    DynFibonacci(int capacity): cache(new size_t[capacity]{0, 1}), cached(2) {}

    // TODO: 实现析构器，释放缓存空间
    // 修改思路：使用 delete[] 释放动态数组
    // ~DynFibonacci();  // 原始代码
    ~DynFibonacci() {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斯波那契计算
    size_t get(int i) {
        // 修改思路：修复循环条件，从 cached 计算到 i
        // for (; false; ++cached) {  // 原始代码
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
