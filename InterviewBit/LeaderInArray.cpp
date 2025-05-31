// https://www.interviewbit.com/problems/leaders-in-an-array/
#include <cstdint>
#include <iostream>
#include <vector>

std::vector<int> solve(std::vector<int>& A) {

    size_t max_so_far = 0;
    std::vector<int> out;

    for (int64_t i = A.size() - 1; i >= 0; --i) {

        if (A[i] > max_so_far) {

            max_so_far = A[i];
            out.emplace_back(A[i]);
        }
    }

    return out;
}