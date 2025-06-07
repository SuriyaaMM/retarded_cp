#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, answer = 0UL;
    std::cin >> n;

    std::vector<size_t> exp_2;

    size_t current_product_2 = 2UL;

    while (current_product_2 <= n) {
        exp_2.emplace_back(current_product_2);
        current_product_2 *= 2;
    }
    // FOREACH value in the exp_2 calculate
    // upper bound of b which is sqrt(n/exp_2[i])
    // lower bound of b which is 1
    // now we need to find odd positive integers such that in this range they are less then upper bound
    // which is right, we will do a binary search
    for (size_t i = 0; i < exp_2.size(); ++i) {

        size_t left = 1;
        size_t right = std::sqrt(n / exp_2[i]) + 1;

        while (right > left) {
            size_t mid = (left + right) / 2;
            // mid is the b we need to find
            // IF mid * mid which is b * b * exp_2 <= n then mid could be the answer or any larger value than mid
            // ELSE the value less than mid is the answer
            if (mid * mid * exp_2[i] <= n) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        answer += ((--left) + 1) / 2;
    }

    std::cout << answer << std::endl;

    return 0;
}