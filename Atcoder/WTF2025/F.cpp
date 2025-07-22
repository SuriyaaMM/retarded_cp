#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
const int MOD = 998244353;
const int MAXN = 1 << 19;  // 2^19 = 524 288 > 2·(N + K)

namespace NTT {
const int G = 3, IG = 332748118;

int rev[MAXN], lim;
void preRev(int n) {
    lim = 1;
    while (lim < n)
        lim <<= 1;
    for (int i = 0; i < lim; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
}
i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    for (; b; b >>= 1, a = a * a % MOD)
        if (b & 1)
            res = res * a % MOD;
    return res;
}
void ntt(i64* a, int op) {
    for (int i = 0; i < lim; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int l = 2; l <= lim; l <<= 1) {
        i64 wn = qpow(op == 1 ? G : IG, (MOD - 1) / l);
        for (int j = 0; j < lim; j += l) {
            i64 w = 1;
            for (int k = 0; k < l / 2; ++k) {
                i64 x = a[j + k], y = w * a[j + k + l / 2] % MOD;
                a[j + k] = (x + y) % MOD;
                a[j + k + l / 2] = (x - y + MOD) % MOD;
                w = w * wn % MOD;
            }
        }
    }
    if (op == -1) {
        i64 inv = qpow(lim, MOD - 2);
        for (int i = 0; i < lim; ++i)
            a[i] = a[i] * inv % MOD;
    }
}
}  // namespace NTT

i64 fact[MAXN], ifact[MAXN];
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    ifact[n] = NTT::qpow(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i)
        ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}

inline i64 binom(int n, int k) {
    if (k < 0 || k > n)
        return 0;
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

long long N, C, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> N >> C >> K))
        return 0;

    init(N);

    /* ------------------------------------------------------------------
       1. Build the polynomial A(x,y) = Σ_{m≥1} a_m(y) x^m/m!
          where a_m(y) = Σ_{j=0}^{m-1} #comps(m,j) y^j
          #comps(m,j) = C(m,j) j^{j-1} (m-j)^{m-j-1}
    ------------------------------------------------------------------ */
    int deg = N + K;
    vector<i64> P(deg + 1), Q(deg + 1);

    for (int m = 1; m <= N; ++m) {
        for (int j = 0; j < m; ++j) {
            i64 cnt = binom(m, j) * (j == 0 ? 1 : NTT::qpow(j, j - 1)) % MOD *
                      (j == m ? 1 : NTT::qpow(m - j, m - j - 1)) % MOD;
            P[j] = (P[j] + cnt * ifact[m]) % MOD;
        }
    }

    /* ------------------------------------------------------------------
       2. Raise A^C by convolution in the y–variable
          We need [x^N y^K] (A(x,y))^C
          Because the x–part is already encoded in the coefficient,
          we only have to convolve the y–part.
    ------------------------------------------------------------------ */
    NTT::preRev(K + 1);
    static i64 a[MAXN], b[MAXN];

    /* copy P to a */
    fill(a, a + NTT::lim, 0);
    for (int i = 0; i <= K; ++i)
        a[i] = P[i];

    NTT::ntt(a, 1);

    /* raise to the C-th power point-wise */
    for (int i = 0; i < NTT::lim; ++i)
        a[i] = NTT::qpow(a[i], C);

    NTT::ntt(a, -1);

    /* ------------------------------------------------------------------
       3. Answer = N!/C! · [y^K] a[y]
    ------------------------------------------------------------------ */
    i64 ans = a[K] * fact[N] % MOD * ifact[C] % MOD;

    cout << ans << '\n';
    return 0;
}