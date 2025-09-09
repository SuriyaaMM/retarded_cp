// https://cses.fi/problemset/task/1637

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>

int64_t dp(int64_t n, std::unordered_map<int64_t, int64_t>& memo) {

    if (n <= 0) {
        return 0;
    }

    if (memo.count(n))
        return memo[n];

    // convert the number to string x
    std::string x = std::to_string(n);
    memo[n] = INT64_MAX;

    // for each digit in x
    for (char& digit : x) {
        // convert the character to numeric digit
        int64_t numeric_digit = static_cast<int64_t>(digit - '0');
        // find the minimum
        memo[n] = std::min(memo[n], dp(n - numeric_digit, memo) + 1);
    }

    return memo[n];
}

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t n = 0UL;
    std::cin >> n;

    std::unordered_map<int64_t, int64_t> memo;

    std::cout << dp(n, memo) << std::endl;

    return 0;
}