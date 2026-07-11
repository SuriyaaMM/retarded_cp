#include <bits/stdc++.h>

using tn = std::tuple<std::int32_t, std::int32_t, std::int32_t>;

std::int32_t
dfs(std::int32_t node, std::int32_t parent,
    const std::vector<std::vector<std::int32_t>> &__restrict__ tree,
    std::vector<tn> &__restrict__ stat) {

    std::int32_t max1 = 0, max2 = 0, childi = -1;

    for (const auto &child : tree[node]) {
        if (child == parent) continue;
        std::int32_t height = dfs(child, node, tree, stat) + 1;
        if (height > max1) {
            max2 = max1;
            max1 = height;
            childi = child;
        } else if (height > max2) {
            max2 = height;
        }
    }
    stat[node] = {max1, max2, childi};
    return max1;
}

void redfs(std::int32_t node, std::int32_t parent,
           const std::vector<std::vector<std::int32_t>> &__restrict__ tree,
           std::vector<std::int32_t> &__restrict__ out,
           std::vector<tn> &__restrict__ stat) {

    for (const auto &child : tree[node]) {
        if (child == parent) continue;

        if (child == std::get<2>(stat[node])) {
            out[child] = 1 + std::max(out[node], std::get<1>(stat[node]));
        } else {
            out[child] = 1 + std::max(out[node], std::get<0>(stat[node]));
        }
        redfs(child, node, tree, out, stat);
    }
}


void solve() {
    std::int32_t n1 = 0;
    std::cin >> n1;

    std::vector<std::vector<std::int32_t>> tree1(n1);
    for (std::int32_t i = 0; i < n1 - 1; ++i) {
        std::int32_t u = 0, v = 0;
        std::cin >> u >> v;
        --u, --v;

        tree1[u].emplace_back(v);
        tree1[v].emplace_back(u);
    }

    std::int32_t n2 = 0;
    std::cin >> n2;

    std::vector<std::vector<std::int32_t>> tree2(n2);
    for (std::int32_t i = 0; i < n2 - 1; ++i) {
        std::int32_t u = 0, v = 0;
        std::cin >> u >> v;
        --u, --v;

        tree2[u].emplace_back(v);
        tree2[v].emplace_back(u);
    }

    std::vector<tn> stat1(n1, {1, 0, -1}), stat2(n2, {1, 0, -1});
    std::vector<std::int32_t> out1(n1, 0), out2(n2, 0);

    dfs(0, -1, tree1, stat1);
    redfs(0, -1, tree1, out1, stat1);

    dfs(0, -1, tree2, stat2);
    redfs(0, -1, tree2, out2, stat2);

    std::vector<std::int32_t> d1(n1, 0), d2(n2, 0);

    for (std::int32_t i = 0; i < n1; ++i) {
        d1[i] = std::max(std::get<0>(stat1[i]), out1[i]);
    }
    for (std::int32_t i = 0; i < n2; ++i) {
        d2[i] = std::max(std::get<0>(stat2[i]), out2[i]);
    }

    std::sort(d1.begin(), d1.end());
    std::sort(d2.begin(), d2.end());

    std::int32_t dia1 = *std::max_element(d1.begin(), d1.end()),
                 dia2 = *std::max_element(d2.begin(), d2.end());

    std::vector<std::int64_t> suffix(n2 + 1, 0);
    suffix[n2] = 0;
    for (std::int32_t i = n2 - 1; i >= 0; --i) {
        suffix[i] = suffix[i + 1] + d2[i];
    }

    std::int64_t answer = 0, dm = std::max(dia1, dia2);
    for (std::int32_t i = 0; i < n1; ++i) {
        std::int64_t q = std::max(dia1 - d1[i] - 1, dia2 - d1[i] - 1);
        auto it = std::upper_bound(d2.begin(), d2.end(), q);

        if (it == d2.end()) {
            answer += ((std::int64_t)n2 * dm);
        } else {
            std::int64_t d = std::distance(d2.begin(), it);
            answer += (((std::int64_t)n2 - d) * d1[i] + suffix[d] + (n2 - d)) +
                      d * dm;
        }
    }
    std::cout << answer << "\n";
}

int main(int, char **) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    // std::cin >> t;
    while (t--) { solve(); }
    return 0;
}
