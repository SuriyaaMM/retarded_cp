// https://codeforces.com/contest/727/problem/A

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using adj_list_t = std::vector<std::pair<size_t, std::pair<size_t, size_t>>>;

bool dfs_for_b(size_t a, size_t& b, std::vector<size_t>& path) {

    if (a == b) {
        path.emplace_back(a);
        return true;
    }

    if (a > b) {
        return false;
    }

    size_t transform_1 = 2 * a;
    if (dfs_for_b(transform_1, b, path)) {
        path.emplace_back(a);
        return true;
    }

    size_t transform_2 = 10 * a + 1;
    if (dfs_for_b(transform_2, b, path)) {
        path.emplace_back(a);
        return true;
    }

    return false;
}

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t a = 0UL, b = 0UL;

    std::cin >> a >> b;

    adj_list_t adj_list;

    std::vector<size_t> transformations;

    if (dfs_for_b(a, b, transformations)) {

        std::cout << "YES" << "\n" << transformations.size() << "\n";

        for (auto it = transformations.rbegin(); it != transformations.rend();
             ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}