#include <cmath>
#include <iostream>
#include <string>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        std::string s;
        std::cin >> s;

        int Y = std::stoi(s);
        int X = static_cast<int>(std::sqrt(Y));

        if (X * X == Y) {

            std::cout << 0 << " " << X << "\n";
        } else {

            std::cout << -1 << "\n";
        }
    }

    return 0;
}