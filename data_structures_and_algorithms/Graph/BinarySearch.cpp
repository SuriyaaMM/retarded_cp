#include <cstdint>
// for dynamic array
#include <vector>
// for streaming
#include <iostream>

int64_t binary_search(int64_t& target, int64_t n = 300000) {
    std::vector<int64_t> a(n, 0);
    int64_t low = 0, high = n;

    while (low < high) {
        int64_t mid = low + (high - low) / 2;
        // reduce higher bound, target is lower
        if (a[mid] > target) {
            high = mid;
        } else if (a[mid] < target) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {}