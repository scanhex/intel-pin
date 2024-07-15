// busy_loop.cpp
#include <iostream>

int main() {
    volatile int sum = 0;
    for (int i = 0; i < 100000000; ++i) {
        sum += i;
    }
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}