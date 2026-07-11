#include <bits/stdc++.h>

constexpr std::int64_t mod = 998244353;

namespace treap {
struct node_t {
    std::int32_t p;
    std::int64_t v, lazy, sum;
    std::size_t size;

    node_t *left, *right;

    node_t() :
        p(std::rand()), v(0), lazy(-1), sum(0), size(0), left(nullptr),
        right(nullptr) {}

    node_t(const std::int64_t &__restrict__ v) :
        p(std::rand()), v(v), lazy(-1), sum(v), size(1), left(nullptr),
        right(nullptr) {}
};

[[nodiscard]]
inline std::size_t get_size(node_t *&t) noexcept {
    return (t != nullptr) ? t->size : (std::size_t)0;
}
[[nodiscard]]
inline std::int64_t get_sum(node_t *&t) noexcept {
    return (t != nullptr) ? t->sum : (std::int64_t)0;
}

inline void update(node_t *&t) noexcept {
    if (t != nullptr) {
        t->size = get_size(t->left) + get_size(t->right) + 1;
        t->sum = (get_sum(t->left) + t->v + get_sum(t->right)) % mod;
    }
}
inline void make_lazy(node_t *&t, std::int64_t v) {
    if (t == nullptr) return;

    t->v = v;
    t->lazy = v;
    t->sum = (v * t->size) % mod;
}
inline void push(node_t *&t) {
    if (t == nullptr) return;
    if (t->lazy != -1) {
        make_lazy(t->left, t->lazy);
        make_lazy(t->right, t->lazy);
        t->lazy = -1;
    }
}
inline void merge(node_t *&t, node_t *left, node_t *right) noexcept {
    push(left), push(right);
    if (left == nullptr || right == nullptr) {
        t = (left != nullptr) ? left : right;
    } else if (left->p > right->p) {
        merge(left->right, left->right, right);
        t = left;
    } else {
        merge(right->left, left, right->left);
        t = right;
    }
    update(t);
}
inline void split(node_t *t, node_t *&left, node_t *&right, std::int64_t size,
                  std::size_t add) noexcept {
    if (!t) return void(left = right = 0);
    push(t);
    std::size_t current_size = add + get_size(t->left);

    if (size <= current_size) {
        split(t->left, left, t->left, size, add);
        right = t;
    } else {
        split(t->right, t->right, right, size, add + 1 + get_size(t->left));
        left = t;
    }
    update(t);
}

[[nodiscard]]
inline std::int64_t range_sum(node_t *&t, std::size_t l, std::size_t r) {
    node_t *left, *mid, *right;

    split(t, left, mid, l, 0);
    split(mid, mid, right, r - l + 1, 0);

    std::int64_t rsum = get_sum(mid);

    merge(mid, mid, right);
    merge(t, left, mid);

    return rsum;
}

inline void range_assign(node_t *&t, std::size_t l, std::size_t r,
                         std::int64_t v) {
    node_t *left, *mid, *right;

    split(t, left, mid, l, 0);
    split(mid, mid, right, r - l + 1, 0);

    make_lazy(mid, v);

    merge(mid, mid, right);
    merge(t, left, mid);
}

inline void __print_inorder(node_t *t) {
    if (t == nullptr) return;
    push(t);
    __print_inorder(t->left);
    std::cout << t->v << " ";
    __print_inorder(t->right);
}

inline void print_inorder(node_t *t) noexcept {
    __print_inorder(t);
    std::cout << "\n";
}

inline void make(node_t *&t, std::vector<std::int64_t> &__restrict__ a) {
    for (const auto &ai : a) {
        node_t *v = new node_t(ai);
        merge(t, t, v);
    }
}
} // namespace treap