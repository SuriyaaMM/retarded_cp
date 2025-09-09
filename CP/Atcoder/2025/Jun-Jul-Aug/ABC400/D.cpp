#include <cstddef>
#include <deque>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t h = 0UL, w = 0UL;
    std::cin >> h >> w;

    std::vector<std::vector<char>> grid(h, std::vector<char>(w));

    for (size_t i = 0; i < h; ++i) {
        std::string s = "";
        std::cin >> s;
        for (size_t j = 0; j < w; ++j) {
            grid[i][j] = s[j];
        }
    }

    size_t a_1_indexed, b_1_indexed, c_1_indexed, d_1_indexed;
    std::cin >> a_1_indexed >> b_1_indexed >> c_1_indexed >> d_1_indexed;

    size_t a = a_1_indexed - 1;
    size_t b = b_1_indexed - 1;
    size_t c = c_1_indexed - 1;
    size_t d = d_1_indexed - 1;

    std::vector<std::vector<size_t>> dp(
        h, std::vector<size_t>(w, std::numeric_limits<size_t>::max()));

    std::deque<std::pair<size_t, size_t>> q;

    dp[a][b] = 0UL;
    q.push_front({a, b});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        std::pair<size_t, size_t> curr = q.front();
        q.pop_front();
        size_t r = curr.first;
        size_t col = curr.second;

        // 0-cost moves (adjacent cells)
        for (int i = 0; i < 4; ++i) {
            size_t nr = r + dr[i];
            size_t nc = col + dc[i];

            // Check bounds
            if (nr < h && nc < w) {
                // If it's a road
                if (grid[nr][nc] == '.') {
                    if (dp[r][col] < dp[nr][nc]) {
                        dp[nr][nc] = dp[r][col];
                        q.push_front({nr, nc});
                    }
                }
            }
        }

        // 1-cost moves (front kicks)
        // Up kick: affects (r-1, col), (r-2, col)
        for (int k_dist = 1; k_dist <= 2; ++k_dist) {
            if (r >= k_dist) {  // Check bounds for r - k_dist
                size_t kr = r - k_dist;
                size_t kc = col;
                if (dp[r][col] + 1 < dp[kr][kc]) {
                    dp[kr][kc] = dp[r][col] + 1;
                    q.push_back({kr, kc});
                }
            }
        }
        // Down kick: affects (r+1, col), (r+2, col)
        for (int k_dist = 1; k_dist <= 2; ++k_dist) {
            if (r + k_dist < h) {  // Check bounds for r + k_dist
                size_t kr = r + k_dist;
                size_t kc = col;
                if (dp[r][col] + 1 < dp[kr][kc]) {
                    dp[kr][kc] = dp[r][col] + 1;
                    q.push_back({kr, kc});
                }
            }
        }
        // Left kick: affects (r, col-1), (r, col-2)
        for (int k_dist = 1; k_dist <= 2; ++k_dist) {
            if (col >= k_dist) {  // Check bounds for col - k_dist
                size_t kr = r;
                size_t kc = col - k_dist;
                if (dp[r][col] + 1 < dp[kr][kc]) {
                    dp[kr][kc] = dp[r][col] + 1;
                    q.push_back({kr, kc});
                }
            }
        }
        // Right kick: affects (r, col+1), (r, col+2)
        for (int k_dist = 1; k_dist <= 2; ++k_dist) {
            if (col + k_dist < w) {  // Check bounds for col + k_dist
                size_t kr = r;
                size_t kc = col + k_dist;
                if (dp[r][col] + 1 < dp[kr][kc]) {
                    dp[kr][kc] = dp[r][col] + 1;
                    q.push_back({kr, kc});
                }
            }
        }
    }

    std::cout << dp[c][d] << std::endl;

    return 0;
}