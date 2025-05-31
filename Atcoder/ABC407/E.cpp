#include <cstddef>
#include <iostream>
#include <queue>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    for (size_t j = 0; j < t; ++j) {
        size_t n = 0UL;
        std::cin >> n;

        std::priority_queue<size_t> pq = {};
        size_t answer = 0UL;

        for (size_t i = 1; i <= 2 * n; ++i) {

            size_t x = 0UL;
            std::cin >> x;
            pq.emplace(x);

            if (i % 2)
                answer += pq.top(), pq.pop();
        }

        std::cout << answer << std::endl;
    }
    return 0;
}