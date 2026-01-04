#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

// 知识点总结：
// 1. Trivial 类型：可以直接拷贝内存的类型，无自定义构造/析构函数
// 2. 结构体初始化：需要显式初始化所有成员避免未定义行为
// 3. 引用传递：使用 & 避免复制大型结构体

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斯波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 修改思路：修复循环条件和数组访问
    // for (; false; ++cached) {  // 原始代码
    for (; cache.cached <= i; ++cache.cached) {
        // cache[cached] = cache[cached - 1] + cache[cached - 2];  // 原始代码
        cache.cache[cache.cached] = cache.cache[cache.cached - 1] + cache.cache[cache.cached - 2];
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    // 修改思路：初始化 cache[0]=0, cache[1]=1, cached=2
    // FibonacciCache fib;  // 原始代码
    FibonacciCache fib = {{0, 1}, 2};
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
