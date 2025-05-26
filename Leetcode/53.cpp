#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
   public:
    int maxSubArray(std::vector<int>& nums) {

        size_t n = nums.size();

        int current_maximum = 0, overall_max = nums[0];

        for (size_t i = 1; i < n; ++i) {

            current_maximum = std::max(nums[i], nums[i] + current_maximum);
            overall_max = std::max(overall_max, current_maximum);
        }

        return overall_max;
    }
};

int main() {

    Solution solution = {};

    std::vector<int> nums = {5, 4, -1, 7, 8};

    std::cout << solution.maxSubArray(nums) << std::endl;

    return 0;
}