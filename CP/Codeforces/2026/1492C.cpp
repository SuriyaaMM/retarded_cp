#include <bits/stdc++.h>

void solve() {
    int32_t m = 0, n = 0;
    std::cin >> n >> m;

    std::string s = "", t = "";
    std::cin >> s >> t;

    std::vector<int32_t> early(m, 0), far(m, 0);
    int32_t sp = 0;
    for (int32_t i = 0; i < m; ++i) {
        while (sp < n && t[i] != s[sp]) ++sp;
        early[i] = sp++;
    }

    sp = n - 1;
    for (int32_t i = m - 1; i >= 0; --i) {
        while (sp >= 0 && t[i] != s[sp]) --sp;
        far[i] = sp--;
    }

    int32_t answer = 1;
    for (int32_t i = 0; i < m - 1; ++i) {
        answer = std::max(answer, far[i + 1] - early[i]);
    }

    std::cout << answer << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    // std::cin >> t;

    while (t--) { solve(); }
}