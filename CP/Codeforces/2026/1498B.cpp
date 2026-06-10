#include <bits/stdc++.h>

/*
naive simulation using multiset and lower bound on it should
do the work.
track space_left, if we're not able to fit anything, then move to
next level.
*/

void solve() {
    int32_t n = 0;
    int64_t w = 0;

    std::cin >> n >> w;

    std::multiset<int64_t, std::greater<int64_t>> widths_mset;
    for (int32_t i = 0; i < n; ++i) {
        int64_t wi = 0;
        std::cin >> wi;
        widths_mset.emplace(wi);
    }

    int64_t required_height = 1, space_left = w;
    for (; !widths_mset.empty();) {
        auto it = widths_mset.lower_bound(space_left);
        // something is fittable
        if (it != widths_mset.end()) {
            space_left -= *it;
            widths_mset.erase(it);
        }
        // nothing is fittable, move to next level
        else {
            required_height++;
            space_left = w;
        }
    }
    std::cout << required_height << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}