#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n = 0UL;
    double s = 0.0;
    std::cin >> n >> s;

    std::vector<double> t(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> t[i];
    }

    bool elder_remains_awake = true;

    if (t[0] >= (s + 0.5)) {
        elder_remains_awake = false;
    }

    if (elder_remains_awake) {
        for (size_t i = 0; i < n - 1; ++i) {
            if (t[i + 1] - t[i] >= (s + 0.5)) {
                elder_remains_awake = false;
                break;
            }
        }
    }

    if (elder_remains_awake) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}