#include <algorithm>
#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

int main(int, char**){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0ULL;

    std::cin >> t;

    std::vector<std::string> solved_problems(t);

    for(size_t i = 0; i < t; ++i){

        size_t n = 0ULL;
        std::cin >> n;

        std::string ai = "";
        std::cin >> ai;
        solved_problems[i] = ai;
    }

    // solution
    /*
        lets put all these characters in a map
        IF the character count is more than 1
        then we add additional count
        ELSE we just add 1
        map may be overkill but lets see
    */

    
    for(std::string& str : solved_problems){


        std::unordered_map<char, uint32_t> frequency_map;

        // O(n)
        for(size_t i = 0; i < str.size(); ++i){

            /*
                IF this is the first time, then
                increment by 2
            */
            if(frequency_map[str[i]] == 0)
                ++(++frequency_map[str[i]]);
            else
                ++frequency_map[str[i]];
        }

        size_t answer = 0ULL;

        // O(n)
        for(auto it = frequency_map.begin(); it != frequency_map.end(); ++it){

            answer += it->second;
        }

        std::cout << answer << std::endl;
    }

    
}   
