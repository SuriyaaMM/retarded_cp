#include <bits/stdc++.h>

bool f(int64_t x, std::vector<int64_t> &a, std::vector<int64_t> &b) {

    int64_t petya = 0;
    for (int32_t i = 0; i < (a.size()); ++i) {
        if (a[i] > x) { petya += b[i]; }
    }

    return (petya <= x);
}

void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::vector<int64_t> a(n, 0), b(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];
    for (int32_t i = 0; i < n; ++i) std::cin >> b[i];

    int64_t l = 0, h = 1e15, answer = 0;

    while (l <= h) {
        int64_t mid = l + (h - l) / 2;

        if (f(mid, a, b)) {
            answer = mid;
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    std::cout << answer << "\n";
}

int main(int, char **) {
    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}
