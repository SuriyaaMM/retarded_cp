#include <bits/stdc++.h>

void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::vector<int32_t> a(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];

    int32_t max_a = *std::max_element(a.begin(), a.end());

    using t3 = std::tuple<int32_t, int32_t, int32_t>;
    using t2 = std::tuple<int32_t, int32_t>;


    std::vector<t3> tuples(n - 2, {0, 0, 0});
    for (int32_t i = 2; i < n; ++i) {
        tuples[i - 2] = std::make_tuple(a[i - 2], a[i - 1], a[i]);
    }

    // std::vector will give an tle :(
    std::unordered_map<int32_t, std::map<t2, int32_t>> d1, d2, d3;
    for (const auto &ai : a) { d1[ai] = {}; }

    std::map<t2, int64_t> c1, c2, c3;

    for (const auto &[a1, a2, a3] : tuples) {
        const auto &p1 = std::make_tuple(a2, a3);
        const auto &p2 = std::make_tuple(a1, a3);
        const auto &p3 = std::make_tuple(a1, a2);

        if (d1[a1].count(p1))
            d1[a1][p1]++;
        else
            d1[a1][p1] = 1;

        if (d2[a2].count(p2))
            d2[a2][p2]++;
        else
            d2[a2][p2] = 1;

        if (d3[a3].count(p3))
            d3[a3][p3]++;
        else
            d3[a3][p3] = 1;

        if (c1.count(p1))
            c1[p1]++;
        else
            c1[p1] = 1;

        if (c2.count(p2))
            c2[p2]++;
        else
            c2[p2] = 1;

        if (c3.count(p3))
            c3[p3]++;
        else
            c3[p3] = 1;
    }

    int64_t answer = 0;
    for (const auto &[a1, a2, a3] : tuples) {
        const auto &p1 = std::make_tuple(a2, a3);
        const auto &p2 = std::make_tuple(a1, a3);
        const auto &p3 = std::make_tuple(a1, a2);
        answer += (c1[p1] - d1[a1][p1]);
        answer += (c2[p2] - d2[a2][p2]);
        answer += (c3[p3] - d3[a3][p3]);
    }

    answer /= 2;

    std::cout << answer << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}