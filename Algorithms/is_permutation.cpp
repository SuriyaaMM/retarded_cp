#include <bits/stdc++.h>

static constexpr const std::int32_t _n = 3e5 + 1;
std::array<std::int32_t, _n> count_a, count_b;

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