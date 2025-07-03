#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

bool dp(size_t number, std::unordered_map<size_t, bool>& memo) {

    if (number == 2020 || number == 2021)
        return true;
    else if (number < 2020)
        return false;

    if (memo.count(number))
        return memo[number];

    return memo[number] = dp(number - 2021, memo) || dp(number - 2020, memo);
}

int main(int, char**) {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    std::unordered_map<size_t, bool> memo;
    std::vector<std::string> results(t);

    for (size_t i = 0; i < t; ++i) {

        size_t n = 0UL;
        std::cin >> n;

        if (dp(n, memo))
            results[i] = "YES";
        else
            results[i] = "NO";
    }

    for (std::string& result : results) {
        std::cout << result << std::endl;
    }

    return 0;
}