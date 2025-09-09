//https://atcoder.jp/contests/abc405/tasks/abc405_d

#include <cstddef>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using pair_t = std::pair<int64_t, int64_t>;

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t h = 0UL, w = 0UL;
    std::cin >> h >> w;

    // solution
    // initialize distance to infinity
    std::vector<std::vector<int64_t>> distance(
        h, std::vector<int64_t>(w, std::numeric_limits<int64_t>::max()));
    // actual grid
    // std::vector<std::vector<char>> grid(h, std::vector<char>(w, '.'));
    std::vector<std::string> grid(h);
    for (auto& s : grid)
        std::cin >> s;
    // answer grid
    std::vector<std::vector<char>> answer(h, std::vector<char>(w, '.'));
    // multi-source bfs queue
    std::queue<pair_t> q;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 'E')
                q.emplace(i, j);
        }
    }

    // for (int64_t i = 0; i < h; ++i) {
    //     for (int64_t j = 0; j < w; ++j) {
    //         std::cin >> grid[i][j];
    //         // IF it is an emergency exit, then it is the source for BFS
    //         if (grid[i][j] == 'E') {
    //             answer[i][j] = 'E';
    //             distance[i][j] = 0;
    //             q.emplace(std::pair(i, j));
    //         } else if (grid[i][j] == '#') {
    //             answer[i][j] = '#';
    //         }
    //     }
    // }

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    auto ok = [&](int i, int j) {
        return 0 <= i and i < h and 0 <= j and j < w;
    };
    std::string A = "^<v>";
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if (!ok(ni, nj))
                continue;
            if (grid[ni][nj] != '.')
                continue;
            grid[ni][nj] = A[k];
            q.emplace(ni, nj);
        }
    }
    for (auto& s : grid)
        std::cout << s << "\n";

    // // perform multi-source bfs
    // while (!q.empty()) {
    //     // get the node for performing bfs on
    //     auto& [i, j] = q.front();
    //     // pop if off the queue
    //     q.pop();
    //     int64_t effective_moveable_cost = distance[i][j] + 1;
    //     // we can move to any of the adjacent cell unless it has already less distance from some
    //     // other exit point, or is it not blocked.
    //     // check whether we can move to right cell and add it to queue if possible
    //     if (j + 1 < w) {
    //         if (grid[i][j + 1] != '#' &&
    //             distance[i][j + 1] > effective_moveable_cost) {
    //             distance[i][j + 1] = effective_moveable_cost;
    //             q.emplace(std::pair(i, j + 1));
    //         }
    //     }
    //     // check whether we can move to left cell and add it to queue if possible
    //     if (j - 1 >= 0) {
    //         if (grid[i][j - 1] != '#' &&
    //             distance[i][j - 1] > effective_moveable_cost) {
    //             distance[i][j - 1] = effective_moveable_cost;
    //             q.emplace(std::pair(i, j - 1));
    //         }
    //     }
    //     // check whether we can move to bottom cell and add it to queue if possible
    //     if (i + 1 < h) {
    //         if (grid[i + 1][j] != '#' &&
    //             distance[i + 1][j] > effective_moveable_cost) {
    //             distance[i + 1][j] = effective_moveable_cost;
    //             q.emplace(std::pair(i + 1, j));
    //         }
    //     }
    //     // check whether we can move to top cell and add it to queue if possible
    //     if (i - 1 >= 0) {
    //         if (grid[i - 1][j] != '#' &&
    //             distance[i - 1][j] > effective_moveable_cost) {
    //             distance[i - 1][j] = effective_moveable_cost;
    //             q.emplace(std::pair(i - 1, j));
    //         }
    //     }
    // }

    // for (int64_t i = 0; i < h; ++i) {
    //     for (int64_t j = 0; j < w; ++j) {
    //         // check which neighbour has distance value which is one less than the current distance
    //         // because shortest path would increase one by one according to bfs distance grid
    //         // constructed earlier
    //         // check rightmost cell because of higher cache hit
    //         // check distance for right cell
    //         if (grid[i][j] == '.') {
    //             if (j + 1 < w && distance[i][j + 1] == distance[i][j] - 1) {
    //                 answer[i][j] = '>';
    //             } else if (j - 1 >= 0 &&
    //                        distance[i][j - 1] == distance[i][j] - 1) {
    //                 answer[i][j] = '<';
    //             } else if (i + 1 < h &&
    //                        distance[i + 1][j] == distance[i][j] - 1) {
    //                 answer[i][j] = 'v';
    //             } else if (i - 1 >= 0 &&
    //                        distance[i - 1][j] == distance[i][j] - 1) {
    //                 answer[i][j] = '^';
    //             }
    //         }

    //         std::cout << answer[i][j];
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}