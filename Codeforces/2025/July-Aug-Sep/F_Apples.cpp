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
8 4 3
1 1 
3 4
6 4
5 2
4 2
4 3
5 5
7 3

first we will sort
1 1 
4 2
5 2
4 3
7 3
3 4
6 4
5 5

what we can choose? s & l
what is already given? d & w
what is our goal?
maximimize number of apples that are falling in the range 
    [l-0.5, l+2.5] in the time [s-0.5, s+3.5]
    l+2.5 - (l-0.5) = 3 is the maximum window size
    s+3.5 - (s-0.5) = 4 is the maximum time window

    say s = 1, we can start at 0.5 and 4.5
        within this time window
        1 apple from 1
        2 apples from 4
        1 apple from 5
        1 from 6
        1 from 7
    

*/
void solve() {

    int64_t n = 0L, d = 0L, w = 0L, ti = 0L, xi = 0L;
    std::cin >> n >> d >> w;

    std::vector<pair_t> a(n, {0, 0});
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> xi >> ti;
        a[i] = {ti, xi};
    }

    std::sort(a.begin(), a.end());

    int64_t max_apples = 0;
    int64_t left = 0;

    std::multiset<int64_t> active_xs;

    for (int64_t right = 0; right < n; ++right) {

        active_xs.insert(a[right].second);

        while (a[right].first - a[left].first >= d) {
            active_xs.erase(active_xs.find(a[left].second));
            ++left;
        }

        std::vector<int64_t> xs(active_xs.begin(), active_xs.end());
        int64_t l = 0;
        for (int64_t r = 0; r < xs.size(); ++r) {
            while (xs[r] - xs[l] >= w)
                ++l;
            max_apples = std::max(max_apples, r - l + 1);
        }
    }

    std::cout << max_apples << '\n';
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}