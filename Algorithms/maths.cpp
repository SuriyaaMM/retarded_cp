#include <bits/stdc++.h>

template <typename __T, typename __T_Accumulator> [[nodiscard]]
inline __T_Accumulator bexp(__T base, __T exp,
                            __T mod = std::numeric_limits<__T>::max()) {
    __T_Accumulator result = 1;
    for (__T_Accumulator basew = base % mod; exp > 0;
         basew = (basew * basew) % mod, exp >>= 1) {
        if ((exp & 1) == 1) result = (result * basew) % mod;
    }
    return result;
}
template <typename __T, typename __T_Accumulator> [[nodiscard]]
inline __T_Accumulator bexp(__T base, __T exp) {
    __T_Accumulator result = 1;
    for (__T_Accumulator basew = base; exp > 0; basew *= basew, exp >>= 1) {
        if ((exp & 1) == 1) result *= basew;
    }
    return result;
}

template <typename __T, typename __T_Accumulator> [[nodiscard]]
inline __T_Accumulator expectation(__T p, __T q,
                                   __T mod = std::numeric_limits<__T>::max()) {
    __T_Accumulator qinv = bexp<__T, __T_Accumulator>(q, mod - 2, mod);
    return ((p * qinv) % mod);
}

template <typename _T, std::size_t _N, std::int64_t _MOD>
void factorial(std::array<_T, _N> &__restrict__ f) {
    f[0] = 1;
    for (std::size_t i = 1; i < _N; ++i) f[i] = (f[i - 1] * i) % _MOD;
}

template <typename _T, std::size_t _N, std::int64_t _MOD>
void invfactorial(std::array<_T, _N> &__restrict__ inv, _T factorial_nm1) {
    inv[_N - 1] = bexp<_T, _T>(factorial_nm1, _MOD - 2, _MOD) % _MOD;
    for (std::size_t i = _N - 1; i > 0; --i) inv[i - 1] = (inv[i] * i) % _MOD;
}