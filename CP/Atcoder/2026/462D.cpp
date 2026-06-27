#include <bits/stdc++.h>

void solve() {
    std::int32_t n = 0, d = 0;
    std::cin >> n >> d;

    using t2 = std::tuple<std::int32_t, std::int32_t>;
    std::vector<t2> p(n, {0, 0});

    std::int32_t minimum = std::numeric_limits<std::int32_t>::max(),
                 maximum = std::numeric_limits<std::int32_t>::min();

    for (auto &[si, ti] : p) {
        std::cin >> si >> ti;
        minimum = std::min({minimum, si, ti});
        maximum = std::max({maximum, si, ti});
    }

    std::map<std::int32_t, std::int64_t> sub;
    std::map<std::int32_t, std::int64_t> add;

    for (const auto &[si, ti] : p) {
        if (ti - si >= d) {
            add[si]++;
            sub[si + (ti - si - d + 1)]++;
        }
    }

    std::vector<std::int64_t> timeline(maximum + 1, 0);

    std::int64_t current = 0;
    for (std::int32_t i = minimum; i <= maximum; ++i) {
        auto it_add = add.find(i);
        auto it_sub = sub.find(i);

        if (it_add != add.end()) current += it_add->second;
        if (it_sub != sub.end()) current -= it_sub->second;

        timeline[i] = current;
    }

    std::int64_t answer = 0;
    for (std::int32_t i = minimum; i <= maximum; ++i) {
        if (timeline[i] >= 2) {
            answer += (timeline[i] * (timeline[i] - 1) / 2);
        }
    }

    std::cout << answer << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    // std::cin >> t;

    while (t--) { solve(); }
}