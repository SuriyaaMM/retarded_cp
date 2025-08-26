#include <algorithm>
#include <cmath>
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
1 10 6 5

say i am updating 1 6 5 
2  10 7  6 will be the resulting array
4  22 9  8 will be the resulting array
8  22 13 12
16 22 21 20
32 22 37 36
now i see the issue, we cannot increase everything as per our wish
in this case we need not even increase 1, because 7 is the pivot and
if we can somehow increase verything to the right of 7 in muinimum time
then we have ourselves the answer

what if 1 7 2 9 6 5, i have to somehow figure out at what point should i stop 2?
can i reach a number between 7 and 9?
using the given set of operations (addition by 2^x-1)

*/
void solve(std::vector<int64_t>& pre_calculation) {
    int64_t n = 0L;
    std::cin >> n;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    int64_t max_time = 0L, this_time = 0L;
    for (int64_t i = 1; i < n; ++i) {
        this_time = 0L;
        // non decreasing
        if (a[i - 1] > a[i]) {
            for (int64_t j = 0; j < (int64_t)pre_calculation.size(); ++j) {
                if (a[i - 1] <= a[i]) {
                    break;
                }
                a[i] += pre_calculation[j];
                ++this_time;
            }
            max_time = std::max(this_time, max_time);
        }
    }

    std::cout << max_time << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

#define MT
#ifdef MT
    int64_t tt = 0L;
    std::cin >> tt;
    const int64_t index = 32;
    std::vector<int64_t> power_of_twos(index + 1, 1);
    for (int64_t i = 0; i <= index; ++i) {
        power_of_twos[i] = 1LL << i;
    }

    //print_vec(0, index, power_of_twos);

    while (tt--) {
        solve(power_of_twos);
    }
#else
    solve();
#endif

    return 0;
}