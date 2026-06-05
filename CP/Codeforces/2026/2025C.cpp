#include <bits/stdc++.h>

void solve() {
    int32_t n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<int32_t> a(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];

    std::sort(a.begin(), a.end());

    int32_t left = 0, answer = 1;
    std::set<int32_t> in_this_window;

    for (int32_t right = 0; right < n; ++right) {

        if (right > 0 && a[right] - a[right - 1] >= 2) {
            left = right;
            in_this_window.clear();
        }

        in_this_window.emplace(a[right]);

        while (in_this_window.size() > k) {
            const auto to_remove = a[left];
            in_this_window.erase(a[left]);

            while (left <= right && a[left] == to_remove) { ++left; }
        }

        answer = std::max(answer, right - left + 1);
    }
    std::cout << answer << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}