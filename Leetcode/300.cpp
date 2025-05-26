#include <algorithm>
#include <vector>
#include <iostream>

class Solution {
public:

    int lengthOfLIS(std::vector<int>& nums) {
        
        std::vector<int> dp(nums.size());

        dp[nums.size() - 1] = 1;

        for(int64_t i = (int64_t)nums.size() - 2; i >= 0; --i){

            dp[i] = 1;

            for(int64_t j = i + 1; j < nums.size(); ++j){

                if(nums[j + 1] > nums[j]) {
                dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
        }

        return *std::max_element(dp.begin(), dp.end());   
    }
};

int main(int, char**){

    Solution solution = {};

    std::vector<int> nums = {10,9,2,5,3,7,101,18};

    std::cout << solution.lengthOfLIS(nums) << std::endl;
}

