// https://codeforces.com/gym/105937/problem/A

#include <iostream>
#include <string>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {

        std::string S = "", output = "";
        std::cin >> S;

        for (size_t j = 0; j < S.size(); ++j) {

            if (S[j] != 'i' && S[j] != '1' && S[j] != 'l' && S[j] != 'I') {
                output.push_back(S[j]);
            }
        }

        std::cout << output << std::endl;
    }

    return 0;
}