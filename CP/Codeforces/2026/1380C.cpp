#include <bits/stdc++.h>

void solve() {
    int32_t n = 0, x = 0;
    std::cin >> n >> x;

    std::vector<int32_t> a(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];

    std::sort(a.begin(), a.end());

    int32_t min_skill = std::numeric_limits<int32_t>::max(), team_size = 0,
            answer = 0;
    for (int32_t i = n - 1; i >= 0; --i) {
        team_size++;
        min_skill = std::min(min_skill, a[i]);
        int32_t team_power = team_size * min_skill;

        if (team_power >= x) {
            answer++;
            team_size = 0;
            min_skill = std::numeric_limits<int32_t>::max();
        }
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