#include <bits/stdc++.h>

int main(int, char **) {

    std::cout << "enter n and target\n";
    int32_t n = 0, target = 0;
    std::cin >> n >> target;

    std::vector<int32_t> a(n, 0);
    std::cout << "enter the array\n";
    for (int32_t i = 0; i < n; ++i) { std::cin >> a[i]; }

    int32_t left = 0, right = n - 1;

    while (left <= right) {
        int32_t mid = left + (right - left) / 2;

        bool left_sorted = (a[mid] >= a[0]);

        if (target == a[mid]) {
            std::cout << "target is at " << mid << "\n";
            break;
        } else {
            if (target > a[mid]) {
                left = mid + 1;
            } else {
                if (left_sorted) {
                    if (a[0] <= target) {
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                } else {
                    if (a[n - 1] <= target) {
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
            }
        }
    }
}
