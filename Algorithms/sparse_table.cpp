#include <bits/stdc++.h>

template <typename _T, class _BinaryOp> struct sparse_table_t {
    std::vector<std::vector<_T>> st;
    std::vector<std::size_t> log2;
    _BinaryOp op;

    sparse_table_t(std::vector<_T> &__restrict__ array) {
        std::size_t n = array.size();

        log2.resize(n + 1);
        log2[1] = 0;
        for (std::size_t i = 2; i <= n; ++i) { log2[i] = log2[i / 2] + 1; }

        std::size_t k = log2[n] + 1;
        st.assign(k, std::vector<_T>(n));

        for (std::size_t i = 0; i < n; ++i) { st[0][i] = array[i]; }

        for (std::size_t i = 1; i < k; ++i) {
            for (std::size_t j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    _T query(std::size_t l, std::size_t r) {
        std::size_t k = log2[r - l + 1];
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

template <typename _T> struct __max {
    _T operator()(const _T a, const _T b) { return std::max(a, b); }
};
template <typename _T> struct __min {
    _T operator()(const _T a, const _T b) { return std::min(a, b); }
};
