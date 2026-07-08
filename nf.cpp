#include <bits/stdc++.h>

inline void solve() {
    std::int32_t n = 0, k = 0;
    std::cin >> n >> k;

    std::string s = "";
    std::cin >> s;

    std::vector<std::int32_t> prefix_open(n + 1, 0), prefix_clos(n + 1, 0);

    for (std::int32_t i = 0; i < n; ++i) {
        prefix_open[i + 1] = prefix_open[i] + (s[i] == '(');
        prefix_clos[i + 1] = prefix_clos[i] + (s[i] == ')');
    }

    std::int32_t bottleneck = -1;
    std::int32_t balance = 1e9;
    for (std::int32_t i = 0; i <= n; ++i) {
        if (prefix_open[i] - prefix_clos[i] < balance) {
            balance = prefix_open[i] - prefix_clos[i];
            bottleneck = i;
        }
    }

    if (bottleneck == -1) {
        std::cout << std::string(n, '0') << "\n";
        return;
    }

    std::string answer(n, '0');
    for (std::int32_t i = 0; i < bottleneck; ++i) {
        if (k > 0 && s[i] == '(') {
            answer[i] = '1';
            --k;
        }
    }
    for (std::int32_t i = bottleneck; i < n; ++i) {
        if (k > 0 && s[i] == ')') {
            answer[i] = '1';
            --k;
        }
    }

    std::cout << answer << "\n";
}

int main(int, char **) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    std::cin >> t;
    while (t--) { solve(); }
    return 0;
}