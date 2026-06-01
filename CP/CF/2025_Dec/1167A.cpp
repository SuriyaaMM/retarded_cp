//https://codeforces.com/contest/1167/problem/A
//https://codeforces.com/contest/1167/submission/354948431

#include <bits/stdc++.h>

void solve() {
    int64_t n = 0;
    std::cin >> n;

    std::string s = "";
    std::cin >> s;

    if (s[0] == '8' && s.size() == 11) {
        std::cout << "YES\n";
        return;
    }

    int64_t first_8 = -1;
    for (int64_t i = 0; i < n; ++i) {
        if (first_8 == -1 && s[i] == '8') first_8 = i;
    }

    if (first_8 == -1) {
        std::cout << "NO\n";
        return;
    }

    int64_t del_dist = first_8;

    if (s.size() - del_dist < 11) {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";
}

int main(int, char **) {
    int64_t t = 0;
    std::cin >> t;

    while (t--) { solve(); }
}
