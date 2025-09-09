#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <set>
#include <vector>

int main(int, char**){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);


    size_t n = 0ULL, m = 0ULL;
    std::cin >> n >> m;

    std::vector<size_t> problem_difficulties(m);

    for(size_t i = 0; i < m; ++i){

        size_t ai = 0ULL;
        std::cin >> ai;
        problem_difficulties[i] = ai;
    }

    // solution
    /*
        so the situation here is that we have "n" difficulty levels and "m" different problems
        for the first time we have UNIQUE "n" difficult problems we can conduct a contest
        PLAN
        start inserting into std::set<size_t> say unique_set, once length(unique_set) == n
        then we conduct a contest, thereby empyting the set
        we continue this process until we have inserted all the "m" elements in the given array

    */

    // std::set<size_t> unique_problems = {};

    // for(size_t i = 0; i < problem_difficulties.size(); ++i){

    //     unique_problems.insert(problem_difficulties[i]);

    //     if(unique_problems.size() == n){
            
    //         unique_problems.clear();
    //         std::cout << 1;
    //     }
    //     else
    //         std::cout << 0;
    // }

    /*
        looks like this is not the one the thing is expecting
        suppose 
        5 20
            1 4 4 2 1 1 3 5 | 4 2 2 4 5 2 3 | 3 4 5 1  | 4\
            number of ones = 4
            number of twos = 3
            number of threes = 3
            number of fours = 5
            number of fives = 3

        so at least 3 contest's should be held

        MODIFIED PLAN
        construct an unorderd_map<size_t, size_t> [difficulty_level, frequency]
        THEN iterate through the array
        FOR EACH iteration if all "n" difficulty_level has at least one then we can conduct a contest, print 1
        OR ELSE we cant, print 0
        Lets see
    */

    // // construct a map for n difficulties
    // std::unordered_map<size_t, size_t> frequency_map(n);

    // auto is_greater_than_1 = [](size_t& elem){return elem > 1;};

    // for(size_t i = 0; i < problem_difficulties.size(); ++i){

    //     ++frequency_map[problem_difficulties[i]];

    //     size_t unique_difficulties = 0ULL;

    //     for(auto it = frequency_map.begin(); it != frequency_map.end(); ++it){

    //         if(it->second >= 1) ++unique_difficulties;
    //     }

    //     if(unique_difficulties == n){

    //         for(auto it = frequency_map.begin(); it != frequency_map.end(); ++it){

    //             --it->second;
    //         }

    //         std::cout << 1;
    //     }
    //     else {

    //         std::cout << 0;
    //     }

    // }

    /*
        OKAY GREAT it seems to work, but there is a huge bottleneck with the map, we dont have constant time lookups!
        so we use an std::vector instead
    */

    std::vector<size_t> frequency_counter(n);
    std::vector<uint16_t> output(m);
    size_t unique_difficulties = 0ULL;

    for(size_t i = 0; i < problem_difficulties.size(); ++i){

        ++frequency_counter[problem_difficulties[i] - 1];

        if(frequency_counter[problem_difficulties[i] - 1] == 1)
            ++unique_difficulties;

        if(unique_difficulties == n){

            output[i] = 1;
            for(size_t j = 0; j < n; ++j){
                --frequency_counter[j];
                if(frequency_counter[j] == 0)
                    --unique_difficulties;
            }
        }
        else {

            output[i] = 0;
        }
    }

    for(uint16_t& bit : output)
        std::cout << bit;
    std::cout << std::endl;
}