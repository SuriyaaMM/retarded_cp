#include <bits/stdc++.h>


void solve() {

    int32_t n = 0;
    std::cin >> n;

    std::vector<int32_t> removables;
    std::vector<bool> child(n, true);

    for (int32_t i = 0; i < n; ++i) {
        int32_t pi = 0;
        bool ci = true;

        std::cin >> pi >> ci;
        pi--;


        if (pi != -2) child[pi] = child[pi] & ci;
        if (ci == true) removables.emplace_back(i);
    }

    std::sort(removables.begin(), removables.end());

    bool printed_something = false;
    for (const auto &removeable : removables) {
        if (child[removeable] == 1) {
            std::cout << removeable + 1 << " ";
            printed_something = true;
        }
    }

    if (!printed_something) { std::cout << -1 << std::endl; }
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    //std::cin >> t;

    while (t--) { solve(); }
}