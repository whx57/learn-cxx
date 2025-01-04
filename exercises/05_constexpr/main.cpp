#include "../exercise.h"

constexpr unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

unsigned long long runtime_fibonacci(int i) {
    if (i == 0) return 0;
    if (i == 1) return 1;

    unsigned long long prev = 0, curr = 1;
    for (int j = 2; j <= i; ++j) {
        auto next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // Use runtime calculation for larger Fibonacci numbers
    constexpr int ANS_N = 90;
    auto ANS = runtime_fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
