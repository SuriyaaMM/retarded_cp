#include <algorithm>
#include <cmath>
#include <cstdint>
#include <format>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// reads the vector
#define read_vec(begin, end, vec) \
    for (int64_t i = begin; i < end; ++i) std::cin >> vec[i];

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

// prints the vector
#define print_vec(begin, end, vec) \
    for (int64_t i = begin; i < end; ++i) std::cout << vec[i] << " ";

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

using node_t = std::array<int, 26>;
node_t operator+(const node_t& a, const node_t& b) {
    node_t res{};
    for (int64_t i = 0; i < 26; ++i) res[i] = a[i] + b[i];
    return res;
}

struct stree_node {
    bool lazy;
    stree_node *left, *right;
    int64_t start;
    node_t freq;

    stree_node()
        : lazy(false), left(nullptr), right(nullptr), start(0), freq() {
        freq.fill(0);
    };
};

struct stree_bu {
    node_t compute_freq(int64_t start, int64_t len, int64_t k) {
        node_t res{};
        if (len <= 0) return res;

        int64_t p = start - 1;
        int64_t first_block = p / k;
        int64_t last_block = (p + len - 1) / k;
        int64_t end_first = std::min((first_block + 1) * k, p + len);
        for (int64_t i = p; i < end_first; ++i) {
            int idx = ((i / k) + (i % k)) % k;
            res[idx]++;
        }
        int64_t full_blocks = last_block - first_block - 1;
        if (full_blocks > 0) {
            for (int i = 0; i < k; ++i) {
                res[i] += full_blocks;
            }
        }
        if (last_block != first_block) {
            int64_t start_last = last_block * k;
            for (int64_t i = start_last; i < p + len; ++i) {
                int idx = ((i / k) + (i % k)) % k;
                res[idx]++;
            }
        }

        return res;
    }

    void push(stree_node* node, int64_t l, int64_t r, int64_t k) {
        if (!node->lazy || l == r) return;

        int64_t mid = (l + r) >> 1;

        if (!node->left) node->left = new stree_node();
        if (!node->right) node->right = new stree_node();

        node->left->lazy = true;
        node->left->start = node->start;
        node->left->freq = compute_freq(node->start, mid - l + 1, k);
        node->right->lazy = true;
        node->right->start = node->start + (mid - l + 1);
        node->right->freq = compute_freq(node->right->start, r - mid, k);
        node->lazy = false;
    }

    void update(stree_node*& node, int64_t l, int64_t r, int64_t ql, int64_t qr,
                int64_t t_start, int64_t k) {
        if (!node) node = new stree_node();

        if (ql <= l && r <= qr) {
            node->lazy = true;
            node->start = t_start + (l - ql);
            node->freq = compute_freq(node->start, r - l + 1, k);
            node->left = nullptr;
            node->right = nullptr;
            return;
        }

        push(node, l, r, k);

        int64_t mid = (l + r) >> 1;
        if (ql <= mid) update(node->left, l, mid, ql, qr, t_start, k);
        if (qr > mid) update(node->right, mid + 1, r, ql, qr, t_start, k);

        node->freq = node_t{};
        if (node->left) node->freq = node->freq + node->left->freq;
        if (node->right) node->freq = node->freq + node->right->freq;
    }

    node_t query(stree_node* node, int64_t l, int64_t r, int64_t ql, int64_t qr,
                 int64_t k) {
        if (!node || qr < l || r < ql) {
            node_t zero{};
            return zero;
        }

        if (ql <= l && r <= qr) return node->freq;

        push(node, l, r, k);

        int64_t mid = (l + r) >> 1;
        return query(node->left, l, mid, ql, qr, k) +
               query(node->right, mid + 1, r, ql, qr, k);
    }
};

void solve() {
    int64_t q = 0LL, n = 0LL, k = 0LL;
    std::cin >> k >> n >> q;

    std::unordered_map<int64_t, char> cmap;

    int64_t ks = k * k;
    std::vector<char> tracks(ks, '0');
    for (int64_t i = 0; i < ks; i += k) {
        for (int64_t j = 0; j < k; ++j) {
            tracks[i + j] = 'A' + j;
        }
    }

    stree_node* root = nullptr;
    stree_bu st;
    for (int64_t i = 0; i < q; ++i) {
        char t = '0';
        std::cin >> t;
        if (t == '+') {
            int64_t len = 0LL, a = 0LL, b = 0LL;
            std::cin >> len >> a >> b;
            st.update(root, 1, n, a, b, len, k);

        } else {
            int64_t a = 0LL, b = 0LL;
            std::cin >> a >> b;
            auto res = st.query(root, 1, n, a, b, k);
            for (int64_t j = 0; j < k; ++j) {
                std::cout << res[j] << (j + 1 == k ? '\n' : ' ');
            }
        }
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#ifdef MT
    int64_t tt = 0L;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
#else
    solve();
#endif

    return 0;
}