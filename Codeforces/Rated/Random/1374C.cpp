#include <algorithm>
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

int main(int, char**){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0ULL;
    std::cin >> t;

    std::vector<std::string> sequences(t);

    for(size_t i = 0; i < t; ++i){

        size_t n = 0ULL;
        std::cin >> n;

        std::string sequence;
        std::cin >> sequence;

        sequences[i] = sequence;
    }

    // solution
    for(std::string& sequence : sequences){

        int64_t prefixBalance = 0, minBalance = 0;

        for(size_t i = 0; i < sequence.size(); ++i){

            if(sequence[i] == '(') ++prefixBalance;
            else --prefixBalance;

            minBalance = std::min(prefixBalance, minBalance);
        }
        
        std::cout << -minBalance << std::endl;
    }
}