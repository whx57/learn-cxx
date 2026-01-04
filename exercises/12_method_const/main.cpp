#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

// 知识点总结：
// 1. const 成员函数：不会修改对象的成员变量
// 2. const 对象：只能调用 const 成员函数
// 3. constexpr 对象：编译期常量对象

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    // 修改思路：添加 const 修饰符使其成为 const 成员函数，并返回 numbers[i]
    // int get(int i) {  // 原始代码
    // }  // 原始代码
    int get(int i) const {
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
