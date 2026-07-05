#include <bits/stdc++.h>

struct sparse_table_t {
    std::vector<std::vector<std::int64_t>> st;
    std::vector<std::int32_t> log2_arr;

    sparse_table_t(std::vector<std::int64_t> &__restrict__ array) {
        std::int32_t n = array.size();

        log2_arr.resize(n + 1);
        log2_arr[1] = 0;
        for (std::int32_t i = 2; i <= n; ++i) {
            log2_arr[i] = log2_arr[i / 2] + 1;
        }

        std::int32_t k = log2_arr[n] + 1;
        st.assign(k, std::vector<std::int64_t>(n));

        for (std::int32_t i = 0; i < n; ++i) { st[0][i] = array[i]; }

        for (std::int32_t i = 1; i < k; ++i) {
            for (std::int32_t j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] =
                    std::min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    std::int64_t query(std::int32_t l, std::int32_t r) {
        std::int32_t k = log2_arr[r - l + 1];
        return std::min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
