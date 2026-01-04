#include "../exercise.h"

// TODO: 改正函数实现，实现正确的缓存优化斯波那契计算
// THINk: 这个函数是一个纯函数（pure function）吗？
// 答：不是纯函数，因为它使用了 static 变量来存储状态，有副作用
// READ: 纯函数 <https://zh.wikipedia.org/wiki/%E7%BA%AF%E5%87%BD%E6%95%B0>

// 知识点总结：
// 1. static 局部变量：只在第一次调用时初始化，生命周期为整个程序运行期间
// 2. 数组初始化：省略初始化列表的数组元素会被零初始化
// 3. 缓存逻辑：从 cached 到 i 的值需要计算
static unsigned long long fibonacci(int i) {
    // TODO: 为缓存设置正确的初始值
    static unsigned long long cache[96]={0,1}, cached=2;
    // TODO: 设置正确的循环条件
    for (; cached<=i; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
    }
    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}
