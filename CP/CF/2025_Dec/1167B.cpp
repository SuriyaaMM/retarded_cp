//https://codeforces.com/contest/1167/problem/B
//https://codeforces.com/contest/1167/submission/354957263

#include <bits/stdc++.h>

void solve() {
    std::array<int64_t, 7> a = {};
    std::array<int64_t, 5> products = {};

    std::map<int64_t, std::pair<int64_t, int64_t>> mp;
    std::array<int64_t, 6> possible = {4, 8, 15, 16, 23, 42};

    for (int64_t i = 0; i < 6; ++i) {
        for (int64_t j = i + 1; j < 6; ++j) {
            mp[possible[i] * possible[j]] = {possible[i], possible[j]};
        }
    }

    int64_t full_product = 1;
    for (int64_t i = 0; i < 6; ++i) full_product *= possible[i];

    for (int64_t i = 1; i <= 4; ++i) {
        std::cout << "? " << i << " " << i + 1 << std::endl;

        int64_t product = 0;
        std::cin >> product;
        products[i] = product;
    }

    auto &[b1, b2] = mp[products[1]];
    auto &[c2, c3] = mp[products[2]];

    int64_t a2 = 1;
    if (b1 == c3 || b1 == c2) {
        a2 = b1;
    } else {
        a2 = b2;
    }

    a[2] = a2;
    a[1] = products[1] / a[2];
    a[3] = products[2] / a[2];
    a[4] = products[3] / a[3];

    int64_t temp1 = (a[2] * a[3] * a[4]);
    int64_t temp2 = (products[1] * products[2] * products[3] * products[4]);

    a[5] = temp2 / (temp1 * temp1 * a[1]);
    a[6] = full_product / (temp1 * a[5] * a[1]);

    std::cout << "! ";
    for (int64_t i = 1; i <= 6; ++i) { std::cout << a[i] << " "; }
    std::cout << std::endl;
}

int main(int, char **) {
    int64_t t = 1;
    //std::cin >> t;

    while (t--) { solve(); }
}
