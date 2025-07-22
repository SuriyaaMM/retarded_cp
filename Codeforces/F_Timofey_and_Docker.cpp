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
ljglsjfkdieufj length = 14
5
1 5 // min 1 docker max 5 docker
3 3 // min 3 docker max 5 docker
2 4 // min 2 docker max 4 docker
3 7 // min 3 docker max 7 docker
2 9 // min 2 docker max 9 docker

so we can use either 3 dockers or 2 dockers but 3 dockers is not possible 
only 2 is possible
min docker in O(n) time 
max docker in O(n) time 
with string lengths 

we want to find the window with least number of matching characters
this is O(n) because window length is 6

but no we want to find the length of all windows and sort them in descending order 
then we will add them such that until x dockers are there, i.e accumulate upto n-k
which will be our answer
*/
void solve() {
    std::string s;
    std::cin >> s;
    int64_t n;
    std::cin >> n;

    std::vector<pair_t> attendees(n);
    read_vecp(0, n, attendees);

    int64_t L = s.size();
    std::string target = "docker";
    std::vector<int64_t> costs;

    for (int64_t i = 0; i + 5 < L; ++i) {
        int64_t cost = 0;
        for (int j = 0; j < 6; ++j) {
            if (s[i + j] != target[j])
                cost++;
        }
        costs.push_back(cost);
    }

    std::sort(costs.begin(), costs.end());

    std::vector<int64_t> freq(7,
                              0);  // max cost is 6 (for "docker" of length 6)
    for (const auto& [l, r] : attendees) {
        for (int x = std::max(0L, l); x <= std::min(6L, r); ++x) {
            freq[x]++;
        }
    }

    std::vector<int64_t> prefix_satisfied(costs.size() + 1, 0);
    std::vector<int64_t> satisfied_upto(7, 0);
    for (int x = 0; x <= 6; ++x) {
        satisfied_upto[x] = freq[x] + (x > 0 ? satisfied_upto[x - 1] : 0);
    }

    int64_t best_people = 0, min_cost = INT64_MAX;
    int64_t curr_cost = 0;
    for (int x = 0; x <= (int64_t)costs.size(); ++x) {
        if (x > 0)
            curr_cost += costs[x - 1];

        int64_t cost_thresh = x == 0 ? -1 : costs[x - 1];
        if (cost_thresh > 6)
            break;

        int64_t people = satisfied_upto[cost_thresh];
        if (people > best_people ||
            (people == best_people && curr_cost < min_cost)) {
            best_people = people;
            min_cost = curr_cost;
        }
    }

    std::cout << min_cost << "\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t tt = 0;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
