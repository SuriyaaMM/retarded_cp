// https://codeforces.com/gym/105937/problem/A

#include <iostream>
#include <ostream>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t a = 0UL, b = 0UL, c = 0UL;

    std::cin >> a >> b >> c;

    if (a == b && b == c) {

        std::cout << (a + b + c) + 100 << std::endl;
    } else {
        std::cout << (a + b + c) << std::endl;
    }

    return 0;
}