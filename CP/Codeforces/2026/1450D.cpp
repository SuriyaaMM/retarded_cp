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

template <typename _T> struct __min {
    _T operator()(const _T a, const _T b) { return std::min(a, b); }
};

void solve() {
    std::int32_t n = 0;
    std::cin >> n;

    std::vector<std::int32_t> a(n, 0);
    for (auto &ai : a) std::cin >> ai;

    sparse_table_t<std::int32_t, __min<std::int32_t>> st(a);

    std::vector<std::int32_t> c(n + 1, 0);

    for (std::int32_t i = 0; i < n; ++i) {

        std::int32_t rr = 0, ll = 0;

        std::int32_t l = 0, h = n - 1;
        while (l <= h) {
            std::int32_t m = l + (h - l) / 2;

            std::int32_t smin = -1;
            if (i + m < n) { smin = st.query(i, i + m); }

            if (smin == a[i]) {
                l = m + 1;
                rr = std::max(rr, m);
            } else {
                h = m - 1;
            }
        }

        l = 0, h = n - 1;
        while (l <= h) {
            std::int32_t m = l + (h - l) / 2;

            std::int32_t pmin = -1;
            if (i - m >= 0) { pmin = st.query(i - m, i); }

            if (pmin == a[i]) {
                l = m + 1;
                ll = std::max(ll, m);
            } else {
                h = m - 1;
            }
        }

        c[a[i]] = std::max(c[a[i]], rr + ll + 1);
    }

    std::vector<std::int32_t> s(n + 1, 0);
    s[1] = c[1];
    for (std::int32_t i = 2; i <= n; ++i) s[i] = std::min(s[i - 1], c[i]);

    for (std::int32_t k = 1; k <= n; ++k) {
        const std::int32_t m = n - k + 1;
        if (s[m] >= k) {
            std::cout << '1';
        } else {
            std::cout << '0';
        }
    }

    std::cout << std::endl;
}

int main(int, char **) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    std::cin >> t;
    while (t--) { solve(); }
    return 0;
}


/*
----------------------------------------------------------------

Solution - 2 

----------------------------------------------------------------

#include <algorithm>
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

template <typename _T> struct __min {
    _T operator()(const _T a, const _T b) { return std::min(a, b); }
};

static constexpr const std::int32_t _n = 3e5 + 1;
std::array<std::int32_t, _n> answer, ref, a, count_a, count_b;

template <typename _T1, typename _T2>
bool _is_permutation(_T1 &__restrict__ a, _T2 &__restrict__ b, std::int32_t n) {

    for (std::int32_t i = 0; i < n; ++i) count_a[i + 1] = 0, count_b[i + 1] = 0;
    for (std::int32_t i = 0; i < n; ++i) count_a[a[i]]++, count_b[b[i]]++;

    for (std::int32_t i = 0; i < n; ++i) {
        if (count_a[i + 1] != 1) return false;
        if (count_b[i + 1] != 1) return false;
    }

    return true;
}

void solve() {
    std::int32_t n = 0;
    std::cin >> n;

    std::vector<std::int32_t> a(n, 0);
    for (auto &ai : a) std::cin >> ai;

    sparse_table_t<std::int32_t, __min<std::int32_t>> st(a);

    std::int32_t l = 1, h = n - 1, b = n + 1, tail = 0;

    while (l <= h) {
        tail = 0;
        std::int32_t m = l + (h - l) / 2;

        std::int32_t ll = 0;
        for (std::int32_t rr = m; rr < n; ++rr, ++ll, ++tail) {
            answer[tail] = st.query(ll, rr);
        }

        if (_is_permutation(answer, ref, tail)) {
            h = m - 1;
            b = m + 1;
        } else {
            l = m + 1;
        }
    }

    if (_is_permutation(a, ref, n)) {
        std::cout << '1';
    } else {
        std::cout << '0';
    }

    for (std::int32_t k = 2; k <= n; ++k) {
        if (k >= b) {
            std::cout << '1';
        } else {
            std::cout << '0';
        }
    }

    std::cout << std::endl;
}

int main(int, char **) {
    std::iota(ref.begin(), ref.begin() + _n, 1);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    std::cin >> t;
    while (t--) { solve(); }
    return 0;
}

*/
