#include <bits/stdc++.h>

void solve() {
    std::int64_t h = 0, c = 0, t = 0;
    std::cin >> h >> c >> t;

    if ((h + c) >= 2 * t) {
        std::cout << "2\n";
        return;
    }

    __float128 hh = h, cc = c, tt = t;

    const auto absfp128 = [](__float128 x) {
        if (x > 0)
            return x;
        else
            return -x;
    };

    __float128 n = absfp128((cc - tt) / (hh + cc - (__float128)2 * tt));

    std::int64_t nc = (std::int64_t)std::ceil((double)n);
    std::int64_t nf = (std::int64_t)std::floor((double)n);

    __float128 tbnc = (nc > 0) ? ((nc * hh) + ((nc - (__float128)1) * cc)) /
                                     ((__float128)2 * (nc) - (__float128)1)
                               : std::numeric_limits<double>::min();
    __float128 tbnf = (nf > 0) ? ((nf * hh) + ((nf - (__float128)1) * cc)) /
                                     ((__float128)2 * (nf) - (__float128)1)
                               : std::numeric_limits<double>::min();

    if (absfp128(tbnf - t) > absfp128(tbnc - t)) {
        std::cout << 2 * nc - 1 << "\n";
    } else {
        std::cout << 2 * nf - 1 << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);


    std::int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}