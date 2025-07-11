#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

// A large value to represent infinity
const long long INF = 1e18;

// Structure to hold state in the priority queue
struct State {
    long long dist;
    int r, c;

    // Custom comparator for min-heap behavior
    bool operator>(const State& other) const { return dist > other.dist; }
};

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int H, W, K;
    std::cin >> H >> W >> K;

    // dist[r][c]: min moves from (r, c) to a goal.
    // Padded with a border to simplify boundary checks.
    std::vector<std::vector<long long>> dist(
        H + 2, std::vector<long long>(W + 2, INF));

    // Min-priority queue for the Dijkstra-like algorithm
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    // Initialize goals: distance is 0.
    for (int i = 0; i < K; ++i) {
        int r, c;
        std::cin >> r >> c;
        if (dist[r][c] > 0) {  // Avoid pushing duplicate goals
            dist[r][c] = 0;
            pq.push({0, r, c});
        }
    }

    // Possible moves (Up, Down, Left, Right)
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Main algorithm loop
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        long long d = current.dist;
        int r = current.r;
        int c = current.c;

        // If we've found a shorter path already, skip.
        if (d > dist[r][c]) {
            continue;
        }

        // The finalized distance for (r, c) might affect its neighbors.
        // Check and potentially update each one.
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Skip if the neighbor is out of the HxW grid
            if (nr < 1 || nr > H || nc < 1 || nc > W) {
                continue;
            }

            // --- The Core Minimax Logic ---
            // Re-evaluate the cost of being at cell (nr, nc).
            std::vector<long long> neighbor_dists;
            for (int j = 0; j < 4; ++j) {
                int nnr = nr + dr[j];
                int nnc = nc + dc[j];
                neighbor_dists.push_back(dist[nnr][nnc]);
            }

            std::sort(neighbor_dists.begin(), neighbor_dists.end());

            // Aoki blocks the best move, Takahashi takes the second best.
            long long second_best_exit_dist = neighbor_dists[1];

            if (second_best_exit_dist == INF) {
                continue;
            }

            long long new_dist_for_neighbor = 1 + second_best_exit_dist;

            // If this new path is better, update and push to queue.
            if (new_dist_for_neighbor < dist[nr][nc]) {
                dist[nr][nc] = new_dist_for_neighbor;
                pq.push({new_dist_for_neighbor, nr, nc});
            }
        }
    }

    // --- Final Calculation ---
    long long total_moves = 0;
    for (int i = 1; i <= H; ++i) {
        for (int j = 1; j <= W; ++j) {
            if (dist[i][j] != INF) {
                total_moves += dist[i][j];
            }
        }
    }

    std::cout << total_moves << std::endl;

    return 0;
}