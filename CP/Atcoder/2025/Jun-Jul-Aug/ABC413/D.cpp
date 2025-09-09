#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

__int128_t gcd(__int128_t a, __int128_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool check(long long start_val, __int128_t p, __int128_t q, int n,
           std::map<long long, int> counts) {

    __int128_t current_val = start_val;

    for (int i = 0; i < n; ++i) {
        long long cv_ll = (long long)current_val;
        if (counts.find(cv_ll) == counts.end() || counts[cv_ll] == 0) {
            return false;
        }
        counts[cv_ll]--;

        if (i < n - 1) {
            __int128_t next_num = current_val * p;
            if (q == 0)
                return false;
            if (next_num % q != 0) {
                return false;
            }
            current_val = next_num / q;
        }
    }

    return true;
}

void solve() {
    int n;
    std::cin >> n;
    std::map<long long, int> initial_counts;
    std::vector<long long> a(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        initial_counts[a[i]]++;
    }

    if (n <= 2) {
        std::cout << "Yes\n";
        return;
    }

    std::vector<long long> abs_a(n);
    for (int i = 0; i < n; ++i) {
        abs_a[i] = std::abs(a[i]);
    }
    std::sort(abs_a.begin(), abs_a.end());

    __int128_t p_abs, q_abs;

    if (abs_a[0] == abs_a[n - 1]) {
        p_abs = 1;
        q_abs = 1;
    } else {
        p_abs = abs_a[1];
        q_abs = abs_a[0];

        if (q_abs == 0) {
            std::cout << "No\n";
            return;
        }

        __int128_t common_divisor = gcd(p_abs, q_abs);
        p_abs /= common_divisor;
        q_abs /= common_divisor;

        for (int i = 1; i < n - 1; ++i) {
            if ((__int128_t)abs_a[i + 1] * q_abs !=
                (__int128_t)abs_a[i] * p_abs) {
                std::cout << "No\n";
                return;
            }
        }
    }

    std::set<long long> start_candidates;
    if (initial_counts.count(abs_a[0]))
        start_candidates.insert(abs_a[0]);
    if (initial_counts.count(-abs_a[0]))
        start_candidates.insert(-abs_a[0]);
    if (initial_counts.count(abs_a[n - 1]))
        start_candidates.insert(abs_a[n - 1]);
    if (initial_counts.count(-abs_a[n - 1]))
        start_candidates.insert(-abs_a[n - 1]);

    for (long long start_val : start_candidates) {
        if (check(start_val, p_abs, q_abs, n, initial_counts)) {
            std::cout << "Yes\n";
            return;
        }
        if (check(start_val, -p_abs, q_abs, n, initial_counts)) {
            std::cout << "Yes\n";
            return;
        }
    }

    std::cout << "No\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}