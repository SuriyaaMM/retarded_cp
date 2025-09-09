#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

void solve() {
    int64_t n = 0LL, k = 0LL;
    std::cin >> n;
    std::cin >> k;

    std::vector<int64_t> a(n, 0);
    for (int64_t i = 0; i < n; ++i)
        std::cin >> a[i];

    if (k == 1) {
        std::cout << "Yes" << std::endl;
        return;
    }

    std::vector<int64_t> b = a;
    std::sort(b.begin(), b.end());

    int64_t cutoff = b[k - 2];

    std::vector<int64_t> c;

    for (auto& ai : a) {
        if (ai <= cutoff)
            c.push_back(ai);
    }

    int64_t spare = c.size() - k + 1;
    int64_t L = 0, R = c.size() - 1;
    bool bad = false;

    while (L < R) {
        if (c[L] != c[R]) {
            if (spare == 0) {
                bad = true;
                break;
            }
            if (c[L] == cutoff) {
                L++;
                spare--;
            } else if (c[R] == cutoff) {
                R--;
                spare--;
            } else {
                bad = true;
                break;
            }
            continue;
        }
        L++;
        R--;
    }
    if (bad) {
        std::cout << "NO" << std::endl;
    } else {
        std::cout << "YES" << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int64_t t = 1;

    std::cin >> t;

    while (t--)
        solve();
    return 0;
}