#include <cstddef>
#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

int main(int, char**){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0ULL;
    std::cin >> t;

    std::vector<std::vector<size_t>> numbers(t);

    for(size_t i = 0; i < t; ++i){

        size_t n = 0ULL;
        std::cin >> n;
        numbers[i].resize(n);

        for(size_t j = 0; j < n; ++j){

            size_t ai = 0ULL;
            std::cin >> ai;
            numbers[i][j] = ai;
        }
    }

    // solution
    for(size_t i = 0; i < numbers.size(); ++i){

        std::unordered_map<size_t, size_t> frequency_map = {};
        
        // O(n) time
        for(size_t j = 0; j < numbers[i].size(); ++j){
            ++frequency_map[numbers[i][j]];
        }

        // minimum of unique skills & max frequency
        size_t unique_skills = frequency_map.size();\
        size_t max_freq = 0;
        for(auto it = frequency_map.begin(); it != frequency_map.end(); ++it){

            max_freq = std::max(max_freq, it->second);
        }

        size_t result = std::min(max_freq, unique_skills);

        if(unique_skills == max_freq)
            std::cout << --result << std::endl;
        else
            std::cout << result << std::endl;;

        /* ----- Extremely Complicated Algorithm ----- */
        // std::priority_queue<std::pair<size_t, size_t>> max_heap;

        // // construct max_heap based on frequency
        // for(auto it = frequency_map.begin(); it != frequency_map.end(); ++it){
        //     // reverse this because comparison function sorts based on first then second
        //     // we want the max_heap to be sorted by frequency
        //     max_heap.emplace(std::pair(it->second, it->first));
        // }

        // std::priority_queue<std::pair<size_t, size_t>,
        // std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> min_heap;
        
        // // construct min_heap based on frequency
        // for(auto it = frequency_map.begin(); it != frequency_map.end(); ++it){
        //     // reverse this because comparison function sorts based on first then second
        //     // we want the max_heap to be sorted by frequency
        //     min_heap.emplace(std::pair(it->second, it->first));
        // }
        
        // // maximum divisible team size will be number of unique elements in vector
        // // minimum would be 0
        // int64_t max = 0;

        // // we iterate through x
        // for(int64_t x = frequency_map.size() - 1; x >= 0; --x){

        //     // get the most frequent element by frequency
        //     std::pair<size_t, size_t> most_frequent = max_heap.top();
        //     // make a copy of min_heap (we need to for all iterations of x)
        //     auto min_heap_copy = min_heap;
        //     // construct an empty set
        //     std::set<size_t> first_team = {};
        //     // while the min_heap is not empty && i < x
        //     // we insert the least frequenct element into the set
        //     for(size_t i = 0; i < x && !min_heap_copy.empty(); ++i){

        //         first_team.insert(min_heap_copy.top().second);
        //         min_heap_copy.pop();
        //     }
        //     // if the min_heap_copy is empty, then most_frequent required would be 1 less
        //     // else if min_heap_copy is not empty, then most_frequent required would be size of the set itself
        //     if(min_heap_copy.empty()){
        //         if(first_team.size() == most_frequent.first - 1)
        //             max = first_team.size();
        //     }
        //     else{

        //         if(first_team.size() == most_frequent.first)
        //             max = first_team.size();
        //     }
        //     --x;
        // }

        // std::cout << max << std::endl;
    }
}