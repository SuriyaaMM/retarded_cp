#include <bits/stdc++.h>

namespace treap {

template <typename _T_Key, typename _T_Priority = std::int64_t,
          class _Rng = std::mt19937_64>
struct static_treap_node_t {
    _Rng _rng;
    _T_Key _key;
    _T_Key _sum;
    _T_Priority _priority;

    bool _lazy;
    std::size_t _size;
    std::int64_t _left, _right;

    static_treap_node_t() :
        _rng(_Rng()), _key(0), _sum(0), _priority(_rng()), _lazy(false),
        _size(1), _left(-1), _right(-1) {}
    static_treap_node_t(const _T_Key key) :
        _rng(_Rng()), _key(key), _sum(0), _priority(_rng()), _lazy(false),
        _size(1), _left(-1), _right(-1) {}
};

template <typename _T_Key, std::size_t _N, typename _T_Priority = std::int64_t,
          class _Rng = std::mt19937_64>
struct static_treap_t {
    std::array<static_treap_node_t<_T_Key, _T_Priority, _Rng>, _N> _treap;
    std::array<std::int64_t, _N> _next;

    [[nodiscard]]
    inline std::size_t size(const std::int64_t i) noexcept {
        return (i == -1) ? (std::size_t)0 : _treap[i].size;
    }

    [[nodiscard]]
    inline std::size_t sum(const std::int64_t i) noexcept {
        return (i == -1) ? (std::size_t)0 : _treap[i].size;
    }

    inline void __update(const std::int64_t i) noexcept {
        if (i != -1) {
            _treap[i]._size =
                size(_treap[i]._left) + size(_treap[i]._right) + 1;
            _treap[i]._sum =
                sum(_treap[i]._left) + sum(_treap[i]._right) + _treap[i]._key;
        }
    }

    inline void __propagate_lazy(const std::int64_t i, const std::int64_t key) {
        if (i == -1) return;
        _treap[i]._key = key;
        _treap[i]._lazy = true;
        _treap[i]._sum = key * _treap[i]._size;
    }

    inline void __push(const std::int64_t i) {
        if (i == -1) return;
        if (_treap[i]._lazy == true) {
            __propagate_lazy(_treap[i]._left, _treap[i]._sum);
            __propagate_lazy(_treap[i]._right, _treap[i]._sum);
            _treap[i]._lazy = false;
        }
    }

    inline void __merge(std::int64_t i_treap, std::int64_t i_left,
                        std::int64_t i_right) {
        __push(i_left);
        __push(i_right);

        if (i_left == -1 || i_right == -1) {
            i_treap = (i_left != -1) ? i_left : i_right;
        } else if (_treap[i_left]._priority > _treap[i_right]._priority) {
            __merge(_treap[i_left]._right, _treap[i_right]._right, i_right);
            i_treap = i_left;
        } else {
            __merge(_treap[i_right]._right, i_left, _treap[i_right]._left);
            i_treap = i_right;
        }
        __update(i_treap);
    }

    inline void __split(std::int64_t i_treap, std::int64_t i_left,
                        std::int64_t i_right, std::size_t split_index,
                        std::int64_t additional = 0) {
        if (i_treap == -1) { i_left = -1, i_right = -1; }
        __push(i_treap);

        std::size_t current_index = additional + size(_treap[i_treap]._left);

        if (current_index >= split_index) {
            __split(_treap[i_treap]._left, i_left, _treap[i_treap].left,
                    split_index, additional);
            i_right = i_treap;
        } else {
            __split(_treap[i_treap]._right, _treap[i_treap]._right, i_right,
                    split_index, additional + 1 + size(_treap[i_treap]._left));
            i_left = i_treap;
        }

        __update(i_treap);
    }
};


// [[nodiscard]]
// inline std::int64_t range_sum(node_t *&t, std::size_t l, std::size_t r) {
//     node_t *left, *mid, *right;

//     split(t, left, mid, l, 0);
//     split(mid, mid, right, r - l + 1, 0);

//     std::int64_t rsum = get_sum(mid);

//     merge(mid, mid, right);
//     merge(t, left, mid);

//     return rsum;
// }

// inline void range_assign(node_t *&t, std::size_t l, std::size_t r,
//                          std::int64_t v) {
//     node_t *left, *mid, *right;

//     split(t, left, mid, l, 0);
//     split(mid, mid, right, r - l + 1, 0);

//     make_lazy(mid, v);

//     merge(mid, mid, right);
//     merge(t, left, mid);
// }

// inline void __print_inorder(node_t *t) {
//     if (t == nullptr) return;
//     push(t);
//     __print_inorder(t->left);
//     std::cout << t->v << " ";
//     __print_inorder(t->right);
// }

// inline void print_inorder(node_t *t) noexcept {
//     __print_inorder(t);
//     std::cout << "\n";
// }

// inline void make(node_t *&t, std::vector<std::int64_t> &__restrict__ a) {
//     for (const auto &ai : a) {
//         node_t *v = new node_t(ai);
//         merge(t, t, v);
//     }
// }
} // namespace treap