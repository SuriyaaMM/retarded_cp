#include <vector>
#include <iostream>
#include <algorithm>

class Solution {

public:

    int largestAltitude(std::vector<int>& gain) {
        
        std::vector<int> prefix_sum(gain.size() + 1, 0);

        for(size_t i = 0; i < gain.size(); ++i){

            prefix_sum[i+1] = prefix_sum[i] + gain[i];
        }

        int ans = *std::max_element(prefix_sum.begin(), prefix_sum.end());
        return ans;
    }
};

int main(){

    Solution solution = {};

    std::vector<int> gain = {-5,1,5,0,-7};

    std::cout << solution.largestAltitude(gain) << std::endl;
}