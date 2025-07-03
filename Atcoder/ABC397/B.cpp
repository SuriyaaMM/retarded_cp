#include <cstddef>
#include <iostream>
#include <string>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string s = "";
    std::cin >> s;

    size_t max_insertion_count = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if ((i + max_insertion_count) % 2 == 0 && s[i] != 'i') {
            ++max_insertion_count;
        } else if ((i + max_insertion_count) % 2 == 1 && s[i] != 'o') {
            ++max_insertion_count;
        }
    }

    if ((s.size() + max_insertion_count) % 2 != 0) {
        ++max_insertion_count;
    }

    std::cout << max_insertion_count << std::endl;

    return 0;
}