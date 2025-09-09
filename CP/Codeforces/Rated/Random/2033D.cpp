#include <algorithm>
#include <cstddef>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
 
int main() {
 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int t = 0;
    std::cin >> t;
 
    std::vector<size_t> output(t);
 
    for (size_t j = 0; j < t; ++j) {
 
        size_t n = 0;
        std::cin >> n;
        
        // Use long long for prefix sums to avoid overflow if array elements are large
        // and n is large. Max sum: 10^5 elements * 10^5 value = 10^10, fits in long long.
        std::vector<long long> prefix_sum_arr(n + 1, 0); 
        for (size_t i = 1; i <= n; ++i) {
 
            int32_t val;
            std::cin >> val;
            prefix_sum_arr[i] = prefix_sum_arr[i-1] + val;
        }
        
        // memoization map
        // Key: prefix sum value
        // Value: The maximum 'dp' value achieved AT the index where this prefix sum was calculated.
        std::unordered_map<long long, int> prefix_sum_to_max_dp_val; // Changed type to long long for key
        // Base case: prefix sum 0 is at index 0 (before any elements), with 0 beautiful segments.
        prefix_sum_to_max_dp_val[0] = 0; 
        
        // dp array - dp[i] is max segments up to index i-1 of the original array.
        std::vector<int> dp(n + 1, 0);
        
        for (size_t i = 1; i <= n; ++i) { // i corresponds to prefix_sum_arr[i] and original array element a[i-1]
 
            // Option 1: Don't form a beautiful segment ending at a[i-1].
            // Max segments is same as for previous prefix.
            dp[i] = dp[i-1];
            
            // Option 2: Check if we can form a beautiful segment ending at a[i-1].
            // This happens if current prefix_sum_arr[i] equals a previous prefix_sum_arr[prev].
            if (prefix_sum_to_max_dp_val.count(prefix_sum_arr[i])) { // Check if current prefix sum exists in map
 
                // 'prev_dp_val' is the max segments we had *before* the start of this new segment.
                int prev_dp_val = prefix_sum_to_max_dp_val[prefix_sum_arr[i]];
                
                // If we form this segment, total segments = prev_dp_val + 1.
                // Take the maximum of Option 1 and Option 2.
                dp[i] = std::max(dp[i], prev_dp_val + 1);
            }
            
            // Crucial Update:
            // Update the map with the CURRENT best 'dp' value for this 'prefix_sum_arr[i]'.
            // If we've seen this prefix sum before, we update it only if the current dp[i]
            // yields a better result for that prefix sum. This allows future segments
            // that depend on this prefix sum to use the best possible previous count.
            if (prefix_sum_to_max_dp_val.find(prefix_sum_arr[i]) == prefix_sum_to_max_dp_val.end() ||
                dp[i] > prefix_sum_to_max_dp_val[prefix_sum_arr[i]]) {
                
                prefix_sum_to_max_dp_val[prefix_sum_arr[i]] = dp[i];
            }
        }
        
        output[j] = dp[n];
    }
 
    for(size_t& out : output){
        
        std::cout << out << "\n";
    }
    
    return 0;
}