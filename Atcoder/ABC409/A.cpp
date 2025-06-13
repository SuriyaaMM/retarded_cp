#include <cstddef>
#include <iostream>
#include <string>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    std::string t = "", s = "";
    std::cin >> t >> s;

    bool found = false;

    for (size_t i = 0; i < n; ++i) {
        // if they both need this item then return yes and break
        if (t[i] == 'o' && s[i] == 'o') {
            std::cout << "Yes" << std::endl;
            found = true;
            break;
        }
    }

    // if that common item is not found then print no
    if (!found) {
        std::cout << "No" << std::endl;
    }

    return 0;
}