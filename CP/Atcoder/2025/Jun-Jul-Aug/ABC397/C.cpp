#include <cstddef>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void solve() {
    size_t n = 0UL;
    std::cin >> n;

    std::vector<size_t> a(n, 0);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<size_t> right_unique(n, 1), left_unique(n, 1);
    std::unordered_map<size_t, size_t> seen;
    size_t distinct_count = 0;

    for (size_t i = 0; i < n; ++i) {
        if (!seen.count(a[i])) {
            ++distinct_count;
            ++seen[a[i]];
        }
        left_unique[i] = distinct_count;
    }
    distinct_count = 0;
    seen.clear();
    for (int64_t i = n - 1; i >= 0; --i) {
        if (!seen.count(a[i])) {
            ++distinct_count;
            ++seen[a[i]];
        }
        right_unique[i] = distinct_count;
    }

    size_t max_unique_elements = 0UL;
    for (size_t i = 0; i < n - 1; ++i) {
        max_unique_elements =
            std::max(max_unique_elements, left_unique[i] + right_unique[i + 1]);
    }

    std::cout << max_unique_elements << "\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}