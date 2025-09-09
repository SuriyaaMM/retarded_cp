#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    std::vector<size_t> a(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // sort the array
    std::sort(a.rbegin(), a.rend());

    // find the maximum non-negative integer x that satisfies
    // for all elements in a, elements greater than or equal to x appear at least x times
    // for example in the array [1 2 2 2 3 6 10] n = 7
    // elements greater than or equal to 10 appear 1 times
    // elements greater than or equal to 7,8,9 appear 1 times
    // elements greater than or equal to 4,5,6 appear 2 times
    // elements greater than or equal to 3 appear 3 times
    // elements greater than or equal to 2 appear 6 times
    // elements greater than or equal to 1 appear 7 times
    // elements greater than or equal to 0 appear 8 times
    // here as we can see the answer is 3, so we will come from reverse
    bool found = false;
    size_t x = 1UL;
    for (int64_t i = n; i >= 0; --i, ++x) {
        // if at least x elements are greater than this value
        if (a[i - 1] >= i) {
            // print out the answer
            std::cout << a[i] << std::endl;
            found = true;
            break;
        }
        // while there are same elements reduce i and add them to count
        while (i - 1 >= 0 && a[i] == a[i - 1]) {
            --i;
            ++x;
        }
    }

    if (!found) {
        std::cout << 0 << std::endl;
    }

    return 0;
}