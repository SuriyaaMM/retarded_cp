#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s = "";
    std::cin >> s;

    size_t m = 0UL;

    std::cin >> m;

    std::vector<size_t> prefix_answer(s.size());

    // calculate the prefix sum under this condition
    // so we can fetch the answer for each query in O(1) time
    for (size_t i = 0; i < s.size() - 1; ++i) {

        if (s[i + 1] == s[i])
            prefix_answer[i + 1] = prefix_answer[i] + 1;
        else
            prefix_answer[i + 1] = prefix_answer[i];
    }

    for (size_t i = 0; i < m; ++i) {

        size_t li = 0UL, ri = 0UL;
        std::cin >> li >> ri;
        // adjusted for zero based indexing
        std::cout << prefix_answer[ri - 1] - prefix_answer[li - 1] << std::endl;
    }

    return 0;
}