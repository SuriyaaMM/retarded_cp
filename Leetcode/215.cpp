#include <vector>
#include <iostream>
#include <queue>
#include <set>

class Solution {
public:

    int findKthLargest(std::vector<int>& nums, int k) {
        
        std::priority_queue<int> max_heap(nums.begin(), nums.end());

        while(k > 1){

            max_heap.pop(); --k;
        }

        return max_heap.top();
    }
};

int main(){

    Solution solution = {};
    std::vector<int> nums = {3,2,1,5,6,4};
    std::cout << solution.findKthLargest(nums, 2) << std::endl;

    return 0;
}