#include <cstddef>
#include <iostream>

void solve() {
    size_t n = 0UL;

    std::cin >> n;

    size_t ai = 0UL, bi = 0UL, answer = 0UL;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> ai >> bi;

        if (bi > ai) {
            ++answer;
        }
    }

    std::cout << answer << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}