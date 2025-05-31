#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

class Solution {
   public:
    double getMinDistSum(std::vector<std::vector<int>>& positions) {

        size_t x_center = 0UL, y_center = 0UL;
        size_t min_distance = std::numeric_limits<size_t>::max();

        for (size_t i = 0; i < positions.size(); ++i) {

            size_t diff_x = positions[i][0] - x_center;
            size_t diff_y = positions[i][1] - y_center;

            size_t distance = std::sqrt((diff_x * diff_x) + (diff_y * diff_y));

            if (min_distance > distance) {
                min_distance = distance;
            }
        }
    }
};