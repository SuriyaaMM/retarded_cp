#include <bits/stdc++.h>

void solve() {
    std::int32_t n = 0, q = 0;
    std::cin >> n >> q;

    std::vector<std::uint64_t> a(n, 0);
    for (auto &ai : a) std::cin >> ai;

    std::vector<std::uint64_t> prefix(n, 0);
    prefix[0] = a[0];
    for (std::uint32_t i = 1; i < n; ++i) prefix[i] = prefix[i - 1] + a[i];

    // std::cout << "prefix = ";
    // for (const auto &prefixi : prefix) std::cout << prefixi << " ";
    // std::cout << std::endl;

    std::uint64_t rem = 0;
    for (std::uint32_t i = 0; i < q; ++i) {
        std::uint64_t k = 0;
        std::cin >> k;

        std::uint64_t to_search = k + rem;
        auto it = std::lower_bound(prefix.begin(), prefix.end(), to_search);

        // std::cout << "k = " << k << std::endl;
        // std::cout << "to_search = " << to_search << std::endl;

        if (it == prefix.end()) {
            // std::cout << "is end iterator" << std::endl;
            rem = 0;
            std::cout << n << "\n";

        } else if (it == std::prev(prefix.end())) {

            std::uint64_t v = *it;
            std::size_t n_alive = std::distance(it, prefix.end());
            // std::cout << "is before end" << std::endl;
            // std::cout << "v = " << v << std::endl;

            if (v == to_search) {
                std::cout << n << "\n";
                rem = 0;
            } else {
                std::cout << n_alive << "\n";
                rem += k;
            }

        } else {
            std::uint64_t v = *it;
            std::size_t n_alive = std::distance(it, prefix.end());

            // std::cout << "is other" << std::endl;
            // std::cout << "v = " << v << std::endl;
            // std::cout << "n_alive = " << n_alive << std::endl;

            if (v == to_search) {
                std::cout << n_alive - 1 << "\n";
            } else {
                std::cout << n_alive << "\n";
            }
            rem += k;
        }
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    // std::cin >> t;

    while (t--) { solve(); }
}