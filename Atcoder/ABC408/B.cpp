// https://atcoder.jp/contests/abc408/tasks/abc408_b

#include <cstddef>
#include <iostream>
#include <set>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    std::set<size_t> a = {};

    for (size_t i = 0; i < n; ++i) {

        size_t ai = 0UL;
        std::cin >> ai;
        a.insert(ai);
    }

    std::cout << a.size() << std::endl;
    for (auto it = a.begin(); it != a.end(); ++it) {

        std::cout << *it << " ";
    }
    std::cout << std::endl;
}