// // https://codeforces.com/problemset/problem/1873/E

// #include <algorithm>
// #include <cstddef>
// #include <iostream>
// #include <vector>

// void solve() {

//     size_t n = 0UL, x = 0UL;
//     std::cin >> n >> x;

//     std::vector<size_t> a(n);
//     for (size_t i = 0; i < n; ++i) {
//         std::cin >> a[i];
//     }

//     size_t max_a = *std::max_element(a.begin(), a.end());
//     std::vector<size_t> diff_a(n);
//     for (size_t i = 0; i < n; ++i) {
//         diff_a[i] = max_a - a[i];
//     }

//     // reverse sort
//     std::sort(diff_a.begin(), diff_a.end(), std::greater<>());

//     size_t used_water_count = 0UL, factor = 1UL, height = 1UL;

//     for (size_t right = 1; right < n; ++right) {

//         if (used_water_count >= x) {
//             std::cout << height << std::endl;
//             return;
//         }
//         if (diff_a[right] != diff_a[right - 1]) {
//             used_water_count += factor * (diff_a[right - 1] - diff_a[right]);
//             ++factor;
//             ++height;
//         } else {
//             ++factor;
//         }
//     }

//     std::cout << used_water_count << std::endl;
//     return;
// }

// int main(int, char**) {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     std::cout.tie(nullptr);

//     size_t t = 0UL;
//     std::cin >> t;

//     while (t--) {
//         solve();
//     }

//     return 0;
// }