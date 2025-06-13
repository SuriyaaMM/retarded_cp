#include <cstddef>
#include <iostream>
#include <set>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    while (t--) {

        size_t n = 0UL;
        std::cin >> n;

        std::vector<size_t> a(n);
        std::set<size_t> net, seen;

        for (size_t i = 0; i < n; ++i) {
            std::cin >> a[i];
        }

        size_t cool_partitions = 0UL;
        for (size_t i = 0; i < n; ++i) {
            net.insert((a[i]));
            seen.insert((a[i]));

            if (net.size() == seen.size()) {
                seen.clear();
                ++cool_partitions;
            }
        }

        std::cout << cool_partitions << std::endl;
    }

    return 0;
}