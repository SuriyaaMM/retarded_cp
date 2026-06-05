#include <bits/stdc++.h>

void solve() {
    int32_t n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<int64_t> a(n, 0), b(m, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];
    for (int32_t i = 0; i < m; ++i) std::cin >> b[i];

    std::sort(a.begin(), a.end());
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>>
        pq(b.begin(), b.end());

    int32_t answer = 0;
    for (int32_t right = 0; right < n; ++right) {

        if (pq.empty()) break;
        while ((right < n) && (pq.top() > (a[right] * 2))) { ++right; }
        if (right >= n) { break; }

        answer++;
        pq.pop();
    }

    std::cout << answer << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    //std::cin >> t;

    while (t--) { solve(); }
}