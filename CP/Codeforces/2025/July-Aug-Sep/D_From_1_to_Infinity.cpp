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
123456789   1011121314151617181920.........99   100101102.....999   10001001......9999
9           179                                 1790                17999

k = 10^15 is the max
given a k, i need to figure out what is the range it falls?
say k = 150, how do i know what number is that?
179 - 150 = 29 which means 14 numbers from 99
which means 99 - 14 = 85
so my answer is (84 * 83)/2 + 8;
*/

int64_t calculate_sum_up_to(int64_t n, std::vector<int64_t>& p10) {
    if (n < 0)
        return 0;
    if (n < 10) {
        return n * (n + 1) / 2;
    }

    std::string s = std::to_string(n);
    int64_t len = s.length();
    int64_t msd = s[0] - '0';

    int64_t result = 0;

    if (len > 1) {
        result += 45 * (len - 1) * p10[len - 2];
    }

    if (msd > 1) {
        result += ((int64_t)(msd - 1) * msd / 2) * p10[len - 1];
        result += (int64_t)(msd - 1) * 45 * (len - 1) * p10[len - 2];
    }

    int64_t remainder = n % p10[len - 1];
    result += msd * (remainder + 1);
    result += calculate_sum_up_to(remainder, p10);

    return result;
}

void solve(std::vector<int64_t>& p10) {
    int64_t k;
    std::cin >> k;

    int64_t total_sum = 0;
    int64_t start_num = 1;

    for (int len = 1; len <= 18; ++len) {
        int64_t num_count = 9 * p10[len - 1];
        int64_t digits_in_block = num_count * len;

        if (k > digits_in_block) {
            int64_t end_num = start_num + num_count - 1;
            total_sum += calculate_sum_up_to(end_num, p10) -
                         calculate_sum_up_to(start_num - 1, p10);
            k -= digits_in_block;
            start_num += num_count;
        } else {

            int64_t full_numbers_count = (k - 1) / len;
            if (full_numbers_count > 0) {
                int64_t end_num = start_num + full_numbers_count - 1;
                total_sum += calculate_sum_up_to(end_num, p10) -
                             calculate_sum_up_to(start_num - 1, p10);
            }
            int64_t final_num = start_num + full_numbers_count;
            int64_t remaining_digits = (k - 1) % len + 1;

            std::string s = std::to_string(final_num);
            for (int i = 0; i < remaining_digits; ++i) {
                total_sum += s[i] - '0';
            }

            break;
        }
    }

    std::cout << total_sum << "\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

#define MT
#ifdef MT
    int64_t tt = 0L;
    std::cin >> tt;

    std::vector<int64_t> p10;
    p10.assign(19, 1);
    for (int i = 1; i < 19; ++i) {
        p10[i] = p10[i - 1] * 10;
    }

    while (tt--) {
        solve(p10);
    }
#else
    solve();
#endif

    return 0;
}