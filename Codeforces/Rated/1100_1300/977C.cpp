#include <algorithm>
#include <iostream>
#include <vector>

int main() {

    int n, k;

    std::cin >> n >> k;

    std::vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    sort(a.begin(), a.end());

    int ans;

    if (k == 0) {

        ans = a[0] - 1;
    } else {

        ans = a[k - 1];
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] <= ans) {
            ++cnt;
        }
    }

    if (cnt != k || !(1 <= ans && ans <= (int)10e9)) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << ans << std::endl;
    }

    return 0;
}