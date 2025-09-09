#include <cstddef>
#include <cstdint>
#include <iostream>
#include <unordered_set>
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
        std::vector<size_t> a(n), b(n);
        for (size_t i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        for (size_t i = 0; i < n; ++i) {
            std::cin >> b[i];
        }

        int64_t ni = static_cast<int64_t>(n);
        int64_t i = ni - 1;
        std::unordered_set<size_t> zigzag1, zigzag2;
        for (; i >= 0; --i) {

            if (a[i] == b[i])
                break;

            if (i % 2 == 0) {

                if (zigzag1.count(a[i]))
                    break;
                if (zigzag2.count(b[i]))
                    break;

                if (i + 1 < n)
                    zigzag1.insert(b[i + 1]);
                if (i + 1 < n)
                    zigzag2.insert(a[i + 1]);

                if (zigzag1.count(b[i]))
                    break;
                if (zigzag2.count(a[i]))
                    break;
            } else {
                if (zigzag2.count(a[i]))
                    break;
                if (zigzag1.count(b[i]))
                    break;

                if (i + 1 < n)
                    zigzag2.insert(b[i + 1]);
                if (i + 1 < n)
                    zigzag1.insert(a[i + 1]);

                if (zigzag2.count(b[i]))
                    break;
                if (zigzag1.count(a[i]))
                    break;
            }
        }

        std::cout << i + 1 << std::endl;
    }

    return 0;
}