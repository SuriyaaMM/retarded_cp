// https://atcoder.jp/contests/abc386/tasks/abc386_f

#include <cstddef>
#include <iostream>
#include <string>

void solve() {
    size_t k = 0UL, moves = 0UL;
    std::string s = "", t = "";

    std::cin >> k >> s >> t;

    size_t sp = 0UL, tp = 0UL, sn = s.size(), tn = t.size();

    while (sp < sn && tp < tn) {
        if (s[sp] != t[tp]) {
            s[sp] = t[tp];
            ++moves;
        }

        if (moves > k) {
            std::cout << "No" << "\n";
            return;
        }

        ++sp;
        ++tp;
    }

    if (tp < tn) {
        ++moves;
        if (moves > k) {
            std::cout << "No" << std::endl;
            return;
        }
    }

    if (sp < sn) {
        ++sp;
        ++moves;
        if (moves > k) {
            std::cout << "No" << "\n";
            return;
        }
    }

    std::cout << "Yes" << "\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}