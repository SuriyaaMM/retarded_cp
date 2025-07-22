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

int64_t N, Q;
std::string S;

struct Node {
    int64_t ans, pref_len, suff_len, len;
};

Node tree[4 * 500005];

Node merge(const Node& left, const Node& right, int64_t mid) {
    if (left.len == 0)
        return right;
    if (right.len == 0)
        return left;

    Node res;
    res.len = left.len + right.len;

    res.ans = std::max(left.ans, right.ans);
    if (S[mid] == S[mid + 1]) {
        res.ans = std::max(res.ans, left.suff_len + right.pref_len);
    }

    res.pref_len = left.pref_len;
    if (left.pref_len == left.len && S[mid] == S[mid + 1]) {
        res.pref_len = left.len + right.pref_len;
    }

    res.suff_len = right.suff_len;
    if (right.suff_len == right.len && S[mid] == S[mid + 1]) {
        res.suff_len = right.len + left.suff_len;
    }

    return res;
}

void build(int64_t v, int64_t tl, int64_t tr) {
    if (tl == tr) {
        tree[v] = {1, 1, 1, 1};
    } else {
        int64_t tm = tl + (tr - tl) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1], tm);
    }
}

void update(int64_t v, int64_t tl, int64_t tr, int64_t pos, char new_val) {
    if (tl == tr) {
        S[pos] = new_val;
    } else {
        int64_t tm = tl + (tr - tl) / 2;
        if (pos <= tm) {
            update(v * 2, tl, tm, pos, new_val);
        } else {
            update(v * 2 + 1, tm + 1, tr, pos, new_val);
        }
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1], tm);
    }
}

Node query(int64_t v, int64_t tl, int64_t tr, int64_t l, int64_t r) {
    if (l > r) {
        return {0, 0, 0, 0};
    }
    if (l == tl && r == tr) {
        return tree[v];
    }
    int64_t tm = tl + (tr - tl) / 2;
    Node left_res = query(v * 2, tl, tm, l, std::min(r, tm));
    Node right_res = query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
    return merge(left_res, right_res, tm);
}

void solve() {
    std::cin >> N >> Q;
    std::cin >> S;

    if (N > 0) {
        build(1, 0, N - 1);
    }

    for (int64_t q_idx = 0; q_idx < Q; ++q_idx) {
        int64_t type;
        std::cin >> type;
        if (type == 1) {
            int64_t i;
            char x;
            std::cin >> i >> x;
            update(1, 0, N - 1, i - 1, x);
        } else {
            int64_t l, r;
            std::cin >> l >> r;
            Node result = query(1, 0, N - 1, l - 1, r - 1);
            std::cout << result.ans << "\n";
        }
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}