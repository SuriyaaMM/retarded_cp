//https://codeforces.com/contest/1167/problem/C
//https://codeforces.com/contest/1167/submission/355052078

#include <bits/stdc++.h>

struct connected_comp {
    std::vector<int64_t> parent, size;

    connected_comp(int64_t n) : parent(n), size(n, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int64_t find(int64_t node) {
        if (node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }

    void connect(int64_t node1, int64_t node2) {
        int64_t small_forest = find(node1);
        int64_t large_forest = find(node2);

        if (small_forest == large_forest) return;

        if (size[small_forest] > size[large_forest]) { std::swap(small_forest, large_forest); }
        parent[small_forest] = large_forest;
        size[large_forest] += size[small_forest];
    }

    int64_t num_connected(int64_t node) { return size[find(node)]; }
};

void solve() {
    int64_t n = 0, m = 0;
    std::cin >> n >> m;

    connected_comp cc(n);
    for (int64_t node = 0; node < m; ++node) {
        int64_t ki = 0;
        std::cin >> ki;
        if (ki > 0) {
            int64_t start_node = 0;
            std::cin >> start_node;
            start_node--;
            for (int64_t i = 1; i < ki; ++i) {
                int64_t mi = 0;
                std::cin >> mi;
                mi--;
                cc.connect(start_node, mi);
            }
        }
    }

    for (int64_t node = 0; node < n; ++node) { std::cout << cc.num_connected(node) << " "; }
    std::cout << "\n";
}

int main(int, char **) {
    int64_t t = 1;
    //std::cin >> t;

    while (t--) { solve(); }
}
