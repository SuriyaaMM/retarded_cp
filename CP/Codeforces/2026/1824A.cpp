
#include <bits/stdc++.h>


void solve() {
    int32_t n = 0, m = 0;
    std::cin >> n >> m;

    int32_t count_l = 0, count_r = 0;
    std::vector<bool> seated(m + 1, 0);
    for (int32_t i = 0; i < n; ++i) {
        int32_t ai = 0;
        std::cin >> ai;

        if (ai == -1)
            count_l++;
        else if (ai == -2)
            count_r++;
        else
            seated[ai] = 1;
    }

    int32_t avail_r = 0, avail_l = 0, filled = 0;
    for (int32_t i = 1; i <= m; ++i)
        if (seated[i] != 1)
            avail_r++;
        else
            filled++;

    int32_t answer = std::max(count_r, count_l) + filled;

    for (int32_t i = 1; i <= m; ++i) {
        if (seated[i] == 1) {
            int32_t potential_answer = std::min(avail_l, count_l) +
                                       std::min(avail_r, count_r) + filled;
            answer = std::max(answer, potential_answer);
        } else {
            avail_l++;
            avail_r--;
        }
    }
    std::cout << std::min(answer, m) << "\n";
}

int main(int, char **) {
    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}
