#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

// 知识点总结：
// 1. 复制构造函数：创建对象的副本
// 2. 深拷贝：复制动态分配的资源，而不是只复制指针
// 3. const 重载：const 和非-const 版本的同名方法可以重载


class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // 修改思路：分配 capacity 个 size_t，初始化 cached=2
    // DynFibonacci(int capacity): cache(new ?), cached(?) {}  // 原始代码
    DynFibonacci(int capacity): cache(new size_t[capacity]{0, 1}), cached(2) {}

    // TODO: 实现复制构造器
    // 修改思路：实现深拷贝，复制缓存数组中的数据
    // DynFibonacci(DynFibonacci const &) = delete;  // 原始代码
    DynFibonacci(DynFibonacci const &other) : cache(new size_t[other.cached]), cached(other.cached) {
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

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

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
