// https://codeforces.com/problemset/problem/570/A

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using pair_t = std::pair<size_t, size_t>;

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, m = 0UL;
    std::cin >> n >> m;

    std::vector<std::vector<size_t>> a(m, std::vector<size_t>(n, 0));
    // index_of_maximum_vote_candiate -> (num_citites_candidate_won)
    std::unordered_map<size_t, size_t> hashmap;
    // min votes is 0 and min index is 0
    size_t current_city_max = 0UL, current_city_max_candidate_index = 0UL;

    for (size_t i = 0; i < m; ++i) {
        current_city_max = 0UL;
        current_city_max_candidate_index = 0UL;
        for (size_t j = 0; j < n; ++j) {

            std::cin >> a[i][j];

            // for a given city, we update the max only if the candidates votes is strictly
            // higher then out current max
            if (current_city_max < a[i][j]) {
                current_city_max = a[i][j];
                current_city_max_candidate_index = j;
            }
        }
        // increase the number of cities the candidate won by 1
        ++hashmap[current_city_max_candidate_index];
    }

    size_t elected_candiate = 0UL, num_cities_elected_candidate_won = 0UL;

    for (auto& [index, num_cities] : hashmap) {
        if (num_cities_elected_candidate_won < num_cities) {
            elected_candiate = index;
            num_cities_elected_candidate_won = num_cities;
        } else if (num_cities_elected_candidate_won == num_cities) {
            elected_candiate = std::min(elected_candiate, index);
        }
    }

    // +1 for 1-based indexing
    std::cout << elected_candiate + 1 << std::endl;

    return 0;
}