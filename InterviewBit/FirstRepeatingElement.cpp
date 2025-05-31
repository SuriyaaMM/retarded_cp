// https://www.interviewbit.com/problems/first-repeating-element/

#include <unordered_map>
#include <vector>

int solve(std::vector<int>& A) {

    std::unordered_map<size_t, size_t> freq_map = {};

    for (size_t i = 0; i < A.size(); ++i) {

        ++freq_map[A[i]];
    }

    for (size_t i = 0; i < A.size(); ++i) {

        if (freq_map[A[i]] > 1) {
            return A[i];
        }
    }

    return -1;
}
