#include <bits/stdc++.h>

int main(int, char **) {

    std::cout << "enter n and target\n";
    int32_t n = 0, target = 0;
    std::cin >> n >> target;

    std::vector<int32_t> a(n, 0);
    std::cout << "enter the array\n";
    for (int32_t i = 0; i < n; ++i) { std::cin >> a[i]; }

    int32_t left = 0, right = n;
    while (left < right) {
        int32_t mid = left + (right - left) / 2;
        // is my target at least as good as a[mid]?
        // if yes, then this might be an answer
        // let me keep this inside my bound (right = mid)
        if (a[mid] >= target) {
            right = mid;
        }
        // i'm sure that a[mid] < target
        // we need to eliminate the left half completely
        // including mid
        else {
            left = mid + 1;
        }
    }

    if (left < n) {
        std::cout << "value = " << a[left] << "\n";
    } else {
        std::cout << "value is at end of the array\n";
    }
}
