#include <cstddef>
#include <iostream>
#include <queue>
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

        std::vector<size_t> p(n), q(n);

        for (size_t i = 0; i < n; ++i) {
            std::cin >> p[i];
        }
        for (size_t i = 0; i < n; ++i) {
            std::cin >> q[i];
        }

        std::priority_queue<std::pair<size_t, size_t>> hp, hq;
        std::vector<size_t> r(n);
        for (size_t i = 0; i < n; ++i) {
            hp.emplace(std::pair(p[i], i));
            hq.emplace(std::pair(q[i], i));

            auto& [pi, jp] = hp.top();
            auto& [qi, jq] = hq.top();
            size_t opt1 = (2UL >> pi) + (2UL >> q[jp - i]);
            size_t opt2 = (2UL >> qi) + (2UL >> p[jq - i]);

            r[i] = std::max(opt1, opt2);
        }

        for (size_t i = 0; i < n; ++i) {
            std::cout << r[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}