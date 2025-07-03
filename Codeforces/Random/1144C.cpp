#include <functional>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <cstdint>
#include <vector>

int main(int, char**){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n = 0ULL;
    std::cin >> n;

    std::vector<size_t> sequence(n);

    for(size_t i = 0; i < n; ++i){

        size_t ai = 0ULL;
        std::cin >> ai;
        sequence[i] = ai;
    }

    // solution
    std::string output = "YES";
    std::unordered_map<size_t, size_t> frequencyMap;

    for(size_t i = 0; i < sequence.size(); ++i)
        ++frequencyMap[sequence[i]];

    // by default stores largest element at top (max heap)
    std::priority_queue<size_t> decreasingSequence;
    // by default stores smallest element at top (min heap)
    std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> increasingSequence;

    for(auto it = frequencyMap.begin(); it != frequencyMap.end(); ++it){

        if(it->second > 2) 
            output = "NO";
        else if(it->second == 2) {

            increasingSequence.push(it->first); decreasingSequence.push(it->first);
        }
        else 
            decreasingSequence.push(it->first);
    }

    if(output == "YES"){

        std::cout << output << std::endl;
        std::cout << increasingSequence.size() << std::endl;
        while(!increasingSequence.empty()){

            std::cout << increasingSequence.top() << " ";
            increasingSequence.pop();
        }
        std::cout << std::endl << decreasingSequence.size() << std::endl;
        while(!decreasingSequence.empty()){
            
            std::cout << decreasingSequence.top() << " ";
            decreasingSequence.pop();
        }
        std::cout << std::endl;
    }
    else {

        std::cout << output << std::endl;
    }

    return 0;
}