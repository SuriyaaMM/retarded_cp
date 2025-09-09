#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// reads the vector
#define read_vec(begin, end, vec)         \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i];

// prints the vector
#define print_vec(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cout << vec[i] << " ";

// infinity
constexpr const int64_t inf = std::numeric_limits<int64_t>::max();
// negative infinity
constexpr const int64_t ninf = std::numeric_limits<int64_t>::min();

// pair
using pair_t = std::pair<int64_t, int64_t>;
// generic pair
template <typename T1, typename T2>
using gpair_t = std::pair<T1, T2>;
// unweighted graph o(logn) removal o(logn) insertion
using graph_t = std::vector<std::set<int64_t>>;
// weighted graph
using wgraph_t = std::vector<std::vector<pair_t>>;

void solve() {
    int64_t n = 0LL, q = 0LL;
    std::cin >> n >> q;

    graph_t graph(n);
    int64_t ui = 0LL, vi = 0LL, vx = 0LL;
    int64_t type = 0LL, unconnected_vertices = n;

    for (int64_t i = 0; i < q; ++i) {
        std::cin >> type;
        if (type == 1) {
            std::cin >> ui >> vi;
            --ui;
            --vi;

            if (graph[ui].size() == 0)
                --unconnected_vertices;
            if (graph[vi].size() == 0)
                --unconnected_vertices;

            graph[ui].insert(vi);
            graph[vi].insert(ui);
        } else {
            std::cin >> vx;
            --vx;
            for (auto it = graph[vx].begin(); it != graph[vx].end(); ++it) {
                graph[*it].erase(vx);
                if (graph[*it].size() == 0)
                    ++unconnected_vertices;
            }
            if (!graph[vx].empty())
                ++unconnected_vertices;
            graph[vx].clear();
        }

        std::cout << unconnected_vertices << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}
