#include <bits/stdc++.h>

namespace treap {
struct node_t {
    std::int32_t p;
    std::int64_t v;
    std::size_t size;

    bool reverse;
    node_t *left, *right;

    node_t() :
        p(std::rand()), v(0), size(0), reverse(false), left(nullptr),
        right(nullptr) {}
    node_t(const std::int32_t &__restrict__ p,
           const std::int64_t &__restrict__ v) :
        p(p), v(v), size(1), reverse(false), left(nullptr), right(nullptr) {}
    node_t(const std::int64_t &__restrict__ v) :
        p(std::rand()), v(v), size(1), reverse(false), left(nullptr),
        right(nullptr) {}
};

[[nodiscard]]
inline std::size_t get_size(node_t *&t) noexcept {
    return (t != nullptr) ? t->size : (std::size_t)0;
}

inline void update_size(node_t *&t) noexcept {
    if (t != nullptr) t->size = get_size(t->left) + get_size(t->right) + 1;
}


inline void push(node_t *&t) noexcept {
    if (t == nullptr) return;
    if (t->reverse) {
        t->reverse = false;
        std::swap(t->left, t->right);
        if (t->left) t->left->reverse = !t->left->reverse;
        if (t->right) t->right->reverse = !t->right->reverse;
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
    update_size(t);
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
    update_size(t);
}

inline void reverse(node_t *&t, std::size_t l, std::size_t r) {
    node_t *t1, *t2, *t3;
    split(t, t1, t2, l, 0);
    split(t2, t2, t3, r - l + 1, 0);
    t2->reverse = !t2->reverse;
    merge(t, t1, t2);
    merge(t, t, t3);
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