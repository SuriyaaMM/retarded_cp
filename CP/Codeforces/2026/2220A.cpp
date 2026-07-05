#include <bits/stdc++.h>

void solve() {
    std::int32_t n = 0;
    std::cin >> n;

    std::vector<std::int32_t> a(n, 0);
    for (auto &ai : a) std::cin >> ai;

    std::vector<std::int32_t> c(*std::ranges::max_element(a) + 1, 0);
    for (auto &ai : a) c[ai]++;

    for (auto &ci : c) {
        if (ci > 1) {
            std::cout << "-1\n";
            return;
        }
    }

    std::ranges::sort(a, std::greater<>());

    for (const auto &ai : a) std::cout << ai << " ";
    std::cout << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}