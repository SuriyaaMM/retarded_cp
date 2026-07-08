#include <bits/stdc++.h>

constexpr std::int64_t __mod = 1e9 + 7;
constexpr std::int32_t __n = 2e5 + 1;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const std::int64_t __base =
    std::uniform_int_distribution<std::int64_t>(300, 1000)(rng);

std::array<std::int64_t, __n> btop, phash, rhash;

void __precompute() {
    btop[0] = 1;
    for (std::int32_t i = 1; i < __n; ++i)
        btop[i] = (btop[i - 1] * __base) % __mod;
}

inline void solve() {
    std::int32_t n = 0, k = 0;
    std::cin >> n >> k;

    std::string s = "";
    std::cin >> s;

    std::string sr = s;
    std::reverse(sr.begin(), sr.end());

    phash[0] = (std::int64_t)s[0];
    for (std::int32_t i = 1; i < n; ++i)
        phash[i] = (phash[i - 1] * __base + s[i]) % __mod;

    rhash[0] = (std::int64_t)sr[0];
    for (std::int32_t i = 1; i < n; ++i)
        rhash[i] = (rhash[i - 1] * __base + sr[i]) % __mod;

    auto get_phash = [&](std::int32_t l, std::int32_t r) {
        std::int64_t p =
            (l == 0) ? 0 : (phash[l - 1] * btop[r - l + 1]) % __mod;
        std::int64_t h = (phash[r] - p + __mod) % __mod;
        return h;
    };
    auto get_rhash = [&](std::int32_t l, std::int32_t r) {
        std::int64_t p =
            (l == 0) ? 0 : (rhash[l - 1] * btop[r - l + 1]) % __mod;
        std::int64_t h = (rhash[r] - p + __mod) % __mod;
        return h;
    };

    auto concat = [&](std::int64_t ha, std::int64_t hb, std::int32_t l) {
        return (((ha * btop[l]) % __mod) + hb) % __mod;
    };

    std::string k1 = "", k2 = "";
    k1.reserve(n);
    k2.reserve(n);

    for (std::int32_t i = 0; i < n; ++i) {
        if ((i / k) % 2 == 0) {
            k1 += '0';
            k2 += '1';
        } else {
            k1 += '1';
            k2 += '0';
        }
    }

    std::int64_t hk1 = 0, hk2 = 0;
    for (std::int32_t i = 0; i < n; ++i) {
        hk1 = (hk1 * __base + k1[i]) % __mod;
        hk2 = (hk2 * __base + k2[i]) % __mod;
    }

    for (std::int32_t i = 1; i <= n; ++i) {
        std::int64_t si = get_phash(i, n - 1);
        std::int64_t ri = get_rhash(n - i, n - 1);
        std::int64_t wi = concat(si, ri, i);

        if (wi == hk1 || wi == hk2) {
            std::cout << i << "\n";
            return;
        }
    }

    std::cout << "-1\n";
}

int main(int, char **) {
    __precompute();
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    std::cin >> t;
    while (t--) { solve(); }
    return 0;
}