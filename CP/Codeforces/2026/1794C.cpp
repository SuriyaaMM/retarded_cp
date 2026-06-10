#include <bits/stdc++.h>

/*
core idea is simple once we see the mathematical essence of the problem.
since the elements are sorted, the maximum possible sum we're
ever going to get is going to be xk/1 * xk-1/2 * xk-2/3 ..... xk-d/d
until xk-d/d < 1 in that case we're not going to have any advantage at all
including it in our subsequence because it is only going to decrease
the maximum value of the subsequence. 
however, since the array is also sorted, if x[leftmost] > window_length, 
then this condition holds true, thus we're just left with maintainig the window
& solving this in O(n) time.
*/

void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::vector<int32_t> a(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];

    int32_t left = 0, right = 0;
    for (; right < n; right++) {
        while ((left <= right) && (a[left] < (right - left + 1))) { left++; }
        std::cout << right - left + 1 << " ";
    }
    std::cout << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}