// // https://atcoder.jp/contests/abc408/tasks/abc408_d

// #include <algorithm>
// #include <cstddef>
// #include <iostream>
// #include <numeric>
// #include <vector>

// int main(int, char**) {

//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     size_t t = 0UL;
//     std::cin >> t;

//     std::vector<size_t> answers(t);

//     for (size_t i = 0; i < t; ++i) {

//         size_t n = 0UL;
//         std::string S = "";

//         std::cin >> n >> S;

//         std::vector<size_t> sequence_count;

//         size_t max_sequence_count = 0UL;

//         size_t sequence_begin = 0UL, sequence_end = 0UL;

//         for (size_t i = 0; i < S.size();) {

//             if (S[i] == '1') {
//                 sequence_begin = i;
//                 sequence_end = i;

//                 while (S[++sequence_end] == '1') {}
//                 i = sequence_end;

//                 size_t diff = sequence_end - sequence_begin;
//                 if (max_sequence_count < diff) {
//                     max_sequence_count = diff;
//                 }
//                 sequence_count.emplace_back(diff);
//             } else {
//                 ++i;
//             }
//         }

//         size_t total_sum =
//             std::accumulate(sequence_count.begin(), sequence_count.end(), 0UL);

//         answers[i] = total_sum - max_sequence_count;
//     }

//     for (auto& answer : answers) {

//         std::cout << answer << std::endl;
//     }

//     return 0;
// }

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::string s;
        std::cin >> n >> s;

        const int INF = 1e9;
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(3, INF));

        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            char c = s[i];

            if (dp[i][0] < INF) {

                if (c == '1') {
                    dp[i + 1][0] = std::min(dp[i + 1][0], dp[i][0] + 1);
                } else {
                    dp[i + 1][0] = std::min(dp[i + 1][0], dp[i][0]);
                }

                if (c == '1') {
                    dp[i + 1][1] = std::min(dp[i + 1][1], dp[i][0]);
                } else {
                    dp[i + 1][1] = std::min(dp[i + 1][1], dp[i][0] + 1);
                }
            }

            if (dp[i][1] < INF) {

                if (c == '1') {
                    dp[i + 1][1] = std::min(dp[i + 1][1], dp[i][1]);
                } else {
                    dp[i + 1][1] = std::min(dp[i + 1][1], dp[i][1] + 1);
                }

                if (c == '1') {
                    dp[i + 1][2] = std::min(dp[i + 1][2], dp[i][1] + 1);
                } else {
                    dp[i + 1][2] = std::min(dp[i + 1][2], dp[i][1]);
                }
            }

            if (dp[i][2] < INF) {
                if (c == '1') {
                    dp[i + 1][2] = std::min(dp[i + 1][2], dp[i][2] + 1);
                } else {
                    dp[i + 1][2] = std::min(dp[i + 1][2], dp[i][2]);
                }
            }
        }

        int result = std::min({dp[n][0], dp[n][1], dp[n][2]});
        std::cout << result << '\n';
    }

    return 0;
}