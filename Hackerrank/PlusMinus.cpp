#include <iomanip>
#include <iostream>
#include <vector>

int main(int, char**) {

    size_t n = 0UL;
    std::cin >> n;

    std::vector<int64_t> nums(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    size_t positives = 0UL, negatives = 0UL, zeroes = 0UL;

    for (size_t i = 0; i < n; ++i) {

        if (nums[i] > 0)
            ++positives;
        else if (nums[i] < 0)
            ++negatives;
        else
            ++zeroes;
    }

    double positives_ratio = 0.0, negatives_ratio = 0.0, zeroes_ratio = 0.0;

    positives_ratio = static_cast<double>(positives) / static_cast<double>(n);
    negatives_ratio = static_cast<double>(negatives) / static_cast<double>(n);
    zeroes_ratio = static_cast<double>(zeroes) / static_cast<double>(n);

    std::cout << std::setprecision(7) << positives_ratio << std::endl
              << negatives_ratio << std::endl
              << zeroes_ratio << std::endl;
}