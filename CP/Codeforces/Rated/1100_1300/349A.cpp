// https://codeforces.com/problemset/problem/349/A

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

void solve() {

    size_t n = 0UL;
    std::cin >> n;

    std::vector<size_t> bills(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> bills[i];
    }

    // flawed one, misunderstood one
    // int64_t money = 0LL;

    // for (size_t i = 0; i < n; ++i) {

    //     money += 25;
    //     if (bills[i] != 25) {
    //         money -= (bills[i] - 25);
    //     }

    //     if (money < 0) {
    //         std::cout << "NO" << std::endl;
    //         return;
    //     }
    // }

    // std::cout << "YES" << std::endl;

    size_t num_25_bills = 0UL, num_50_bills = 0UL, num_100_bills = 0UL;

    for (size_t i = 0; i < n; ++i) {

        if (bills[i] == 25) {

            ++num_25_bills;

        } else if (bills[i] == 50) {

            if (num_25_bills >= 1) {
                ++num_50_bills;
                --num_25_bills;
            } else {
                std::cout << "NO" << std::endl;
                return;
            }

        } else if (bills[i] == 100) {

            if (num_25_bills >= 1 && num_50_bills >= 1) {
                ++num_100_bills;
                --num_25_bills;
                --num_50_bills;
            } else if (num_25_bills >= 3) {
                ++num_100_bills;
                num_25_bills -= 3;
            } else {
                std::cout << "NO" << std::endl;
                return;
            }
        }
    }

    std::cout << "YES" << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}