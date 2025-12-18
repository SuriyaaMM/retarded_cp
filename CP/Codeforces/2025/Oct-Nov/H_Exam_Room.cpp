#include <immintrin.h>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>

#pragma GCC optimize( \
    "Ofast,unroll-loops,inline,no-stack-protector,prefetch-loop-arrays,tracer")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt,tune=native")

using namespace std;

constexpr int64_t MOD = 998244353;
constexpr int MAXN = 505;

alignas(64) uint64_t adj[MAXN][8];
int n;

// Inline everything for zero call overhead
__attribute__((always_inline)) inline void intersect_avx2(
    uint64_t* __restrict__ dst, const uint64_t* __restrict__ src1,
    const uint64_t* __restrict__ src2) {
    _mm256_store_si256(
        (__m256i*)dst,
        _mm256_and_si256(_mm256_load_si256((const __m256i*)src1),
                         _mm256_load_si256((const __m256i*)src2)));
    _mm256_store_si256(
        (__m256i*)(dst + 4),
        _mm256_and_si256(_mm256_load_si256((const __m256i*)(src1 + 4)),
                         _mm256_load_si256((const __m256i*)(src2 + 4))));
}

__attribute__((always_inline)) inline void filter_prefix(uint64_t* arr,
                                                         int idx) {
    int b = idx >> 6;
    int r = idx & 63;

    // Manual unroll for speed
    if (b > 0) arr[0] = 0;
    if (b > 1) arr[1] = 0;
    if (b > 2) arr[2] = 0;
    if (b > 3) arr[3] = 0;
    if (b > 4) arr[4] = 0;
    if (b > 5) arr[5] = 0;
    if (b > 6) arr[6] = 0;

    if (r < 63)
        arr[b] &= (~0ULL << (r + 1));
    else
        arr[b] = 0;
}

__attribute__((always_inline)) inline int popcount(const uint64_t* arr) {
    // Parallel popcount for better ILP
    int c0 = __builtin_popcountll(arr[0]);
    int c1 = __builtin_popcountll(arr[1]);
    int c2 = __builtin_popcountll(arr[2]);
    int c3 = __builtin_popcountll(arr[3]);
    int c4 = __builtin_popcountll(arr[4]);
    int c5 = __builtin_popcountll(arr[5]);
    int c6 = __builtin_popcountll(arr[6]);
    int c7 = __builtin_popcountll(arr[7]);
    return (c0 + c1) + (c2 + c3) + (c4 + c5) + (c6 + c7);
}

void solve() {
    if (!(cin >> n)) return;

    static int64_t X[MAXN], Y[MAXN];
    for (int i = 0; i < n; ++i) {
        cin >> X[i] >> Y[i];
    }

    memset(adj, 0, sizeof(adj));

    // Optimized graph construction
    for (int i = 0; i < n; ++i) {
        int64_t di = X[i] * X[i] + Y[i] * Y[i];
        for (int j = i + 1; j < n; ++j) {
            int64_t dx = X[j] - X[i];
            int64_t dy = Y[j] - Y[i];
            int64_t dij = dx * dx + dy * dy;
            int64_t dj = X[j] * X[j] + Y[j] * Y[j];

            if (dij > ((di > dj) ? di : dj)) {
                adj[i][j >> 6] |= (1ULL << (j & 63));
                adj[j][i >> 6] |= (1ULL << (i & 63));
            }
        }
    }

    uint64_t ss = n;

    alignas(64) uint64_t m2[8], m3[8], m4[8];

    // Process vertices in reverse order for better cache behavior on second
    // access
    for (int i = 0; i < n; ++i) {
        int sb1 = i >> 6;
        int sr1 = i & 63;

        for (int b1 = sb1; b1 < 8; ++b1) {
            uint64_t mask1 = adj[i][b1];
            if (b1 == sb1) {
                if (sr1 >= 63) continue;
                mask1 &= (~0ULL << (sr1 + 1));
            }

            if (!mask1) continue;

            while (mask1) {
                int j = (b1 << 6) | __builtin_ctzll(mask1);
                mask1 &= (mask1 - 1);

                ss++;

                // Level 2
                intersect_avx2(m2, adj[i], adj[j]);
                filter_prefix(m2, j);

                int cnt2 = popcount(m2);
                if (!cnt2) continue;
                ss += cnt2;

                // Early check for level 3 viability
                if (cnt2 == 1) {
                    // Only one vertex k - directly count size-4 cliques
                    int b2 = 0;
                    while (!m2[b2]) b2++;
                    int k = (b2 << 6) | __builtin_ctzll(m2[b2]);

                    intersect_avx2(m3, m2, adj[k]);
                    filter_prefix(m3, k);
                    int cnt3 = popcount(m3);
                    if (cnt3) {
                        ss += cnt3;

                        // Level 4 - direct computation
                        for (int b3 = k >> 6; b3 < 8; ++b3) {
                            uint64_t mask3 = m3[b3];
                            while (mask3) {
                                int l = (b3 << 6) | __builtin_ctzll(mask3);
                                mask3 &= (mask3 - 1);

                                intersect_avx2(m4, m3, adj[l]);
                                filter_prefix(m4, l);
                                ss += popcount(m4);
                            }
                        }
                    }
                    continue;
                }

                // General case for level 3
                for (int b2 = j >> 6; b2 < 8; ++b2) {
                    uint64_t mask2 = m2[b2];

                    while (mask2) {
                        int k = (b2 << 6) | __builtin_ctzll(mask2);
                        mask2 &= (mask2 - 1);

                        // Level 3
                        intersect_avx2(m3, m2, adj[k]);
                        filter_prefix(m3, k);

                        int cnt3 = popcount(m3);
                        if (!cnt3) continue;
                        ss += cnt3;

                        // Level 4
                        for (int b3 = k >> 6; b3 < 8; ++b3) {
                            uint64_t mask3 = m3[b3];

                            while (mask3) {
                                int l = (b3 << 6) | __builtin_ctzll(mask3);
                                mask3 &= (mask3 - 1);

                                intersect_avx2(m4, m3, adj[l]);
                                filter_prefix(m4, l);
                                ss += popcount(m4);
                            }
                        }
                    }
                }
            }
        }
    }

    cout << ss % MOD << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}