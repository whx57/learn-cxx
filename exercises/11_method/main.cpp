#include "../exercise.h"

// 知识点总结：
// 1. 成员函数：在结构体/类内部定义的函数，可以访问成员变量
// 2. this 指针：成员函数隐式有 this 指针指向当前对象
// 3. 结构体初始化：使用 {} 进行聚合初始化

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斯波那契计算
    unsigned long long get(int i) {
        for (; cached<=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        printf("%d\n", cache[i]);
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib={{0,1},2};
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
