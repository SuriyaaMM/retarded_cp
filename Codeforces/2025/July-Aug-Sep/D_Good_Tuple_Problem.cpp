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

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

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
// unweighted graph
using graph_t = std::vector<std::vector<int64_t>>;
// weighted graph
using wgraph_t = std::vector<std::vector<pair_t>>;

// disjoint set union by  & path compression
struct dsur_t {

    std::vector<int64_t> parent, rank;

    dsur_t(int64_t n) {
        // O(n)
        parent.resize(n + 1);
        // O(n)
        rank.resize(n + 1, 0);

        for (int64_t i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    // O(1)
    int64_t find_parent(int64_t x) {
        if (parent[x] != x)
            parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);

        if (v == u)
            return;

        if (rank[u] < rank[v])
            std::swap(u, v);

        parent[v] = u;
        if (rank[u] == rank[v])
            ++rank[u];
    }
};

/*
3 3
1 2 3
2 3 1

possible pairs
(1,2) (2,3) (3,1)

X must be of length 3.
lemma1: if there are common numbers between pairs itself then it should not be possible right?
but take a look at first test case

3 2
1 2
2 3

possible pairs
(1,2) (2,3)
X -> (0, 1, 0) which means 1 and 2 are diff and 2 and 3 are diff which suffices the condition
so lemma1 is false, we need a sophisticated way

what makes (1,2) (2,3) (3,1) impossible? 
X -> (0, 1, 0) which means satisfies 1st and 2nd condition but not 3rd. 
lets see a graph
1 -> 2 - > 3 -> 1 there is a cycle. which means this cannot be possible. 

linked list? 

7 8
1 6 2 7 5 4 2 2
3 2 7 2 1 2 3 3

5 -> 1 -> 3
6 -> 2 -> 7 -> 2
4 -> 2 -> 3
*/

bool dfs(int64_t current, int64_t color, graph_t& graph,
         std::vector<int64_t>& colour) {

    colour[current] = color;

    for (const auto& neighbour : graph[current]) {
        if (colour[neighbour] == -1) {
            if (!dfs(neighbour, 1 - color, graph, colour))
                return false;
        } else if (colour[neighbour] == colour[current]) {
            return false;
        }
    }

    return true;
}

void solve() {

    int64_t n = 0L, m = 0L;
    std::cin >> n >> m;

    graph_t graph(n);
    std::vector<int64_t> a(m, 0), b(m, 0);
    read_vec(0, m, a);
    read_vec(0, m, b);

    for (int64_t i = 0; i < m; ++i) {
        --a[i];
        --b[i];
        graph[a[i]].emplace_back(b[i]);
        graph[b[i]].emplace_back(a[i]);
    }

    std::vector<int64_t> colour(n, -1);
    for (int64_t i = 0; i < n; ++i) {
        if (colour[i] == -1) {
            if (!dfs(i, 0, graph, colour)) {
                std::cout << "No\n";
                return;
            }
        }
    }

    std::cout << "Yes\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}