#include <bits/stdc++.h>

void solve() {
    std::int32_t n = 0;
    std::cin >> n;

    std::multiset<std::int32_t> a;

    std::string s = "";
    std::cin >> s;
    for (std::int32_t i = 0; i < n; ++i) { a.emplace(s[i] - '0'); }

    std::int32_t answer = 0;
    for (;;) {
        bool m1 = false;

        auto it0 = a.find(0);
        if (it0 == a.end()) {
            // no zeros, try finding a 1
            auto it1 = a.find(1);
            if (it1 != a.end()) {
                a.erase(it1);
                auto it2 = a.find(1);
                if (it2 == a.end()) { goto here1; }
                // we have 11
                m1 = true;
                a.erase(it2);
                goto here1;
            }
            // no 11 exists
        } else {
            a.erase(it0);
            // we have a zero, try finding something > 5
            auto itg5 = a.upper_bound(5);
            if (itg5 == a.end()) {
                // we dont have anything > 5 try finding something
                // <= 5
                for (std::int32_t j = 5; j >= 0; --j) {
                    auto itle5 = a.lower_bound(j);
                    if (itle5 != a.end()) {
                        // we found something <= 5
                        a.erase(itle5);
                        m1 = true;
                        goto here1;
                    }
                }
            } else {
                // we found found something > 5 pairable with zero
                a.erase(itg5);
                m1 = true;
                goto here1;
            }
        }

    here1:
        if (m1 == false) { break; }

        bool m2 = false;

        // try finding something <= 5
        for (std::int32_t i = 5; i >= 0 && m2 == false; --i) {
            auto itle5 = a.find(i);
            if (itle5 != a.end()) {
                a.erase(itle5);
                // we have something <= 5
                // now try finding something > 5
                auto itg5 = a.upper_bound(i);
                if (itg5 == a.end()) {
                    // we don't have something > 5
                    // try finding something <= 5
                    for (std::int32_t j = 5; j >= 0; --j) {
                        auto itle52 = a.find(j);
                        if (itle52 != a.end()) {
                            // we have something <= 5 as first digit
                            // and something <= 5 as second digit
                            m2 = true;
                            a.erase(itle52);
                            goto here;
                        }
                    }
                    // we dont have something <= 5 break
                } else {
                    // we have something > 5 &&
                    // something <= 5
                    m2 = true;
                    a.erase(itg5);
                    goto here;
                }
            }
        }

    here:
        if (m2 == false) break;

        answer++;
    }

    std::cout << answer << "\n";
}

int main(int, char **) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    std::cin >> t;
    while (t--) { solve(); }
    return 0;
}
