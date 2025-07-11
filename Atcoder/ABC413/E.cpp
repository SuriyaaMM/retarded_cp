#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

void reverse_segment(std::vector<int>& P, int a, int b) {
    int start = a * (1 << b);
    int end = (a + 1) * (1 << b) - 1;
    std::reverse(P.begin() + start, P.begin() + end + 1);
}

std::vector<int> solve_permutation(std::vector<int> P) {
    int n = P.size() / 2;

    // Use a greedy approach with memoization
    std::map<std::vector<int>, std::vector<int>> memo;

    for (int pos = 0; pos < 2 * n; pos++) {
        int min_val = P[pos];
        int min_pos = pos;

        // Find the minimum value that can be brought to current position
        for (int i = pos + 1; i < 2 * n; i++) {
            if (P[i] < min_val) {
                min_val = P[i];
                min_pos = i;
            }
        }

        // If we found a smaller value, try to bring it to current position
        if (min_pos != pos) {
            // Try different operations to see if we can move min_val to pos
            bool moved = false;

            // Try all possible segment operations
            for (int b = 0; b < 20 && !moved; b++) {
                int seg_size = 1 << b;
                if (seg_size > 2 * n)
                    break;

                for (int a = 0; a * seg_size < 2 * n && !moved; a++) {
                    int start = a * seg_size;
                    int end = (a + 1) * seg_size - 1;

                    if (end >= 2 * n)
                        continue;

                    // Check if this operation would help
                    if (start <= pos && pos <= end && start <= min_pos &&
                        min_pos <= end) {
                        // This operation affects both positions
                        std::vector<int> temp = P;
                        reverse_segment(temp, a, b);

                        if (temp[pos] < P[pos]) {
                            P = temp;
                            moved = true;
                        }
                    }
                }
            }
        }
    }

    return P;
}

std::vector<int> solve_optimized(std::vector<int> P) {
    int n = P.size() / 2;
    bool changed = true;

    // Keep applying operations until no improvement
    while (changed) {
        changed = false;
        std::vector<int> best = P;

        // Try all possible operations
        for (int b = 0; b < 20; b++) {
            int seg_size = 1 << b;
            if (seg_size > 2 * n)
                break;

            for (int a = 0; a * seg_size < 2 * n; a++) {
                int start = a * seg_size;
                int end = (a + 1) * seg_size - 1;

                if (end >= 2 * n)
                    continue;

                std::vector<int> temp = P;
                reverse_segment(temp, a, b);

                // Check if this gives a lexicographically smaller result
                if (temp < best) {
                    best = temp;
                    changed = true;
                }
            }
        }

        P = best;
    }

    return P;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<int> P(2 * N);
        for (int i = 0; i < 2 * N; i++) {
            std::cin >> P[i];
        }

        std::vector<int> result = solve_optimized(P);

        for (int i = 0; i < 2 * N; i++) {
            std::cout << result[i];
            if (i < 2 * N - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}