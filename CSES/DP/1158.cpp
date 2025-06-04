#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

size_t dp(int64_t budget, size_t index, std::vector<int64_t>& cost,
          std::vector<int64_t>& pages,
          std::vector<std::vector<int64_t>>& memo) {

    if (index == cost.size()) {
        return 0;
    }
    if (budget < 0) {

        return INT64_MIN;
    }
    // IF number of pages for this budget & index has already been calculated, return it
    if (memo[index][budget] != -1) {
        return memo[index][budget];
    }
    // now for the dp, we can either choose this book and reduce our budget
    // or we can just move on to the next book
    if (memo[index][budget] != -1) {
        return memo[index][budget];
    }

    int64_t pages_if_taken =
        dp(budget - cost[index], index + 1, cost, pages, memo) + pages[index];
    int64_t pages_if_skipped = dp(budget, index + 1, cost, pages, memo);

    return memo[index][budget] = std::max(pages_if_taken, pages_if_skipped);
}

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, x = 0UL;
    std::cin >> n >> x;

    std::vector<int64_t> h(n, 0), s(n, 0);
    // read costs
    for (size_t i = 0; i < n; ++i) {
        std::cin >> h[i];
    }
    // read pages
    for (size_t i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    std::vector<std::vector<int64_t>> memo(n + 1,
                                           std::vector<int64_t>(x + 1, -1));

    int64_t result = dp(static_cast<int64_t>(x), 0, h, s, memo);

    std::cout << std::max(0L, result) << std::endl;

    return 0;
}