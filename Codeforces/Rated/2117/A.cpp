// https://codeforces.com/contest/2117/problem/A
#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    while (t--) {

        size_t n = 0UL, x = 0UL;
        std::cin >> n >> x;

        std::vector<size_t> a(n);
        for (size_t i = 0; i < n; ++i) {
            std::cin >> a[i];
        }

        // find starting index
        size_t start_index = 0UL;
        for (size_t i = 0; i < n; ++i) {
            if (a[i] == 1) {
                start_index = i;
                break;
            }
        }

        bool done = false;
        for (size_t i = start_index; i < n; ++i) {
            // if we have time left, then continue opening doors
            if (x > 0) {
                --x;
                continue;
            }
            // if we don't have any time left and it is a closed door, we cannot escape
            if (x == 0 && a[i] == 1) {
                std::cout << "No" << std::endl;
                done = true;
                break;
            }
        }
        // if we didn't print no, then we sure escaped
        if (!done) {
            std::cout << "Yes" << std::endl;
        }
    }

    return 0;
}