#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// reads the vector
#define read_vec(begin, end, vec)         \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i];

// prints the vector
#define print_vec(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cout << vec[i] << " ";

// infinity
constexpr const int64_t inf = std::numeric_limits<int64_t>::max();
// negative infinity
constexpr const int64_t ninf = std::numeric_limits<int64_t>::min();

// pair
using pair_t = std::pair<int64_t, int64_t>;
// generic pair
template <typename T1, typename T2>
using gpair_t = std::pair<T1, T2>;
// unweighted graph
using graph_t = std::vector<std::vector<int64_t>>;
// weighted graph
using wgraph_t = std::vector<std::vector<pair_t>>;

void solve() {

    int64_t h = 0LL, w = 0LL;
    std::cin >> h >> w;

    std::vector<std::vector<char>> grid(h, std::vector<char>(w, ' '));

    for (int64_t i = 0; i < h; ++i)
        for (int64_t j = 0; j < w; ++j)
            std::cin >> grid[i][j];

    std::array<int64_t, 8> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    std::array<int64_t, 8> dy = {-1, 0, 1, -1, 1, -1, 0, 1};

    std::vector<pair_t> snuke_coords(5, {0, 0});

    std::string forward_sequence = "snuke", backward_sequence = "kuns";

    for (int64_t i = 0; i < h; ++i) {
        for (int64_t j = 0; j < w; ++j) {
            for (int64_t d = 0; d < 8; ++d) {
                int64_t x = i, y = j;
                std::string what = "";

                for (int64_t k = 0; k < 5; ++k) {
                    if (x >= h || x < 0 || y >= w || y < 0) {
                        break;
                    }

                    what += grid[x][y];
                    x += dx[d];
                    y += dy[d];
                }

                if (what == forward_sequence) {
                    for (int64_t k = 0; k < 5; ++k) {
                        // +1 for 1 based
                        std::cout << i + k * dx[d] + 1 << " "
                                  << j + k * dy[d] + 1 << std::endl;
                    }
                    return;
                }
            }
        }
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}