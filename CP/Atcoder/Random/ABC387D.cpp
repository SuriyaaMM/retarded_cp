// https://atcoder.jp/contests/abc387/tasks/abc387_d

#include <cstddef>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using pair_t = std::pair<int64_t, int64_t>;
using dij_t = std::tuple<int64_t, int64_t, pair_t>;

template <typename T>
using grid_t = std::vector<std::vector<T>>;
template <typename T>
using grid3_t = std::vector<std::vector<std::vector<T>>>;

void solve() {
    int64_t h = 0, w = 0;
    std::cin >> h >> w;

    pair_t start = {0, 0}, end = {0, 0};
    grid_t<char> grid(h, std::vector<char>(w, '.'));

    for (int64_t i = 0; i < h; ++i) {
        std::string s = "";
        std::cin >> s;
        for (int64_t j = 0; j < w; ++j) {
            if (s[j] == 'S') {
                start = {i, j};
            } else if (s[j] == 'G') {
                end = {i, j};
            }
            grid[i][j] = s[j];
        }
    }

    // distance[row][col][direction]
    // direction: 0 = last move was horizontal, 1 = last move was vertical
    grid3_t<int64_t> distance(
        h,
        std::vector<std::vector<int64_t>>(
            w, std::vector<int64_t>(2, std::numeric_limits<int64_t>::max())));

    std::priority_queue<dij_t, std::vector<dij_t>, std::greater<>> pq;

    // Start with both directions possible (distance 0)
    distance[start.first][start.second][0] = 0;
    distance[start.first][start.second][1] = 0;

    // Push both possible starting directions
    pq.push(
        {0, 0, start});  // last move was horizontal (can move vertical next)
    pq.push(
        {0, 1, start});  // last move was vertical (can move horizontal next)

    while (!pq.empty()) {
        auto [dist, last_direction, coord] = pq.top();
        auto [row, col] = coord;
        pq.pop();

        if (dist > distance[row][col][last_direction]) {
            continue;
        }

        // Direction alternation:
        // If last_direction == 0 (horizontal), next move must be vertical (change row)
        // If last_direction == 1 (vertical), next move must be horizontal (change col)

        if (last_direction == 0) {
            // Last move was horizontal, now we must move vertically (change row)

            // Move up (decrease row)
            if (row - 1 >= 0 && grid[row - 1][col] != '#') {
                int64_t new_dist = dist + 1;
                if (distance[row - 1][col][1] > new_dist) {
                    distance[row - 1][col][1] = new_dist;
                    pq.push({new_dist, 1, {row - 1, col}});
                }
            }

            // Move down (increase row)
            if (row + 1 < h && grid[row + 1][col] != '#') {
                int64_t new_dist = dist + 1;
                if (distance[row + 1][col][1] > new_dist) {
                    distance[row + 1][col][1] = new_dist;
                    pq.push({new_dist, 1, {row + 1, col}});
                }
            }
        } else {
            // Last move was vertical, now we must move horizontally (change col)

            // Move left (decrease col)
            if (col - 1 >= 0 && grid[row][col - 1] != '#') {
                int64_t new_dist = dist + 1;
                if (distance[row][col - 1][0] > new_dist) {
                    distance[row][col - 1][0] = new_dist;
                    pq.push({new_dist, 0, {row, col - 1}});
                }
            }

            // Move right (increase col)
            if (col + 1 < w && grid[row][col + 1] != '#') {
                int64_t new_dist = dist + 1;
                if (distance[row][col + 1][0] > new_dist) {
                    distance[row][col + 1][0] = new_dist;
                    pq.push({new_dist, 0, {row, col + 1}});
                }
            }
        }
    }

    int64_t result = std::min(distance[end.first][end.second][0],
                              distance[end.first][end.second][1]);

    if (result == std::numeric_limits<int64_t>::max()) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << result << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}