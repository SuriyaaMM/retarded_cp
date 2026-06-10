#include <bits/stdc++.h>

bool f(const int64_t &median, const int32_t &k, const int32_t &n,
       const std::vector<int64_t> &a) {

    std::vector<int32_t> cache(n, 0), mask(n, 0);
    constexpr const int32_t int32_t_min = std::numeric_limits<int32_t>::min();

    for (int32_t i = 0; i < n; ++i) {
        if (a[i] >= median)
            mask[i] = 1;
        else
            mask[i] = -1;
    }

    cache[0] = mask[0];
    for (int32_t i = 1; i < n; ++i) {
        if (i % k == 0) {
            cache[i] = std::max(cache[i - k], mask[i]);
        } else {
            int32_t path_1 = (i > k) ? cache[i - k] : int32_t_min;
            int32_t path_2 = cache[i - 1] + mask[i];

            cache[i] = std::max(path_1, path_2);
        }
    }

    return cache[n - 1] > 0;
}

void solve() {
    int32_t n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<int64_t> a(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];

    int64_t l = 0, h = *std::max_element(a.begin(), a.end()) + 1, answer = 0;

    while (l <= h) {
        int64_t mid = l + (h - l) / 2;
        if (f(mid, k, n, a)) {
            answer = mid;
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }

    std::cout << answer << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}