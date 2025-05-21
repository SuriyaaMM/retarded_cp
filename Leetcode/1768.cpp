#include <string>
#include <iostream>

class Solution {

public:

    std::string mergeAlternately(std::string word1, std::string word2) {
        
        size_t w1_size = word1.size(), w2_size = word2.size();
        size_t merged_index = w1_size + w2_size;
        std::string merged;
        merged.resize(merged_index);
        
        // true = odd
        bool odd = true;
        size_t w1 = 0, w2 = 0;

        for(size_t i = 0; i < merged_index; ++i, odd = !odd){

            if(w1 < w1_size && w2 < w2_size){

                if(odd)
                    merged[i] = word1[w1++];
                else
                    merged[i] = word2[w2++];
            }
            else {

                if(w1 == w1_size)
                    merged[i] = word2[w2++];
                else
                    merged[i] = word1[w1++];
            }
        }
        

        return merged;
    }
};

int main(int argc, char* argv[]){

    Solution solution = {};

    std::cout << solution.mergeAlternately("abcd", "pq") << std::endl;

}