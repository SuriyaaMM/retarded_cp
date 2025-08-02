#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

// Global constants and variables for easy access within helper functions.
constexpr const int64_t inf = std::numeric_limits<int64_t>::max();
const int N_MAX = 501;

int64_t N_val, T_val;
int64_t dist_fw[N_MAX][N_MAX];
int64_t temp_dist[N_MAX][N_MAX];  // Temporary storage for Type 1 query updates
bool has_airport[N_MAX];
std::vector<int64_t> airport_cities;
int64_t min_dist_to_airport[N_MAX];

// Recomputes the shortest distance from every city to the nearest airport.
void recompute_all_min_dist_to_airports() {
    for (int i = 1; i <= N_val; ++i) {
        min_dist_to_airport[i] = inf;
        for (int64_t airport_city : airport_cities) {
            if (dist_fw[i][airport_city] != inf) {
                min_dist_to_airport[i] =
                    std::min(min_dist_to_airport[i], dist_fw[i][airport_city]);
            }
        }
    }
}

void solve() {
    int M, K, Q;
    std::cin >> N_val >> M >> K >> T_val;

    // Initialize distance matrix and airport status
    for (int i = 1; i <= N_val; ++i) {
        std::fill(dist_fw[i] + 1, dist_fw[i] + N_val + 1, inf);
        dist_fw[i][i] = 0;
        has_airport[i] = false;
    }

    // Read initial roads
    for (int i = 0; i < M; ++i) {
        int u, v;
        int64_t c;
        std::cin >> u >> v >> c;
        dist_fw[u][v] = std::min(dist_fw[u][v], c);
        dist_fw[v][u] = std::min(dist_fw[v][u], c);
    }

    // Read initial airports
    for (int i = 0; i < K; ++i) {
        int d;
        std::cin >> d;
        if (!has_airport[d]) {
            has_airport[d] = true;
            airport_cities.push_back(d);
        }
    }

    // Initial Floyd-Warshall for all-pairs shortest paths on roads
    for (int k = 1; k <= N_val; ++k) {
        for (int i = 1; i <= N_val; ++i) {
            for (int j = 1; j <= N_val; ++j) {
                if (dist_fw[i][k] != inf && dist_fw[k][j] != inf) {
                    dist_fw[i][j] =
                        std::min(dist_fw[i][j], dist_fw[i][k] + dist_fw[k][j]);
                }
            }
        }
    }

    recompute_all_min_dist_to_airports();

    std::cin >> Q;
    while (Q--) {
        int type;
        std::cin >> type;
        if (type == 1) {  // Add a road
            int x, y;
            int64_t t;
            std::cin >> x >> y >> t;

            if (dist_fw[x][y] > t) {
                for (int i = 1; i <= N_val; ++i) {
                    for (int j = 1; j <= N_val; ++j) {
                        int64_t path1 = inf, path2 = inf;
                        if (dist_fw[i][x] != inf && dist_fw[y][j] != inf) {
                            path1 = dist_fw[i][x] + t + dist_fw[y][j];
                        }
                        if (dist_fw[i][y] != inf && dist_fw[x][j] != inf) {
                            path2 = dist_fw[i][y] + t + dist_fw[x][j];
                        }
                        temp_dist[i][j] =
                            std::min({dist_fw[i][j], path1, path2});
                    }
                }
                for (int i = 1; i <= N_val; ++i) {
                    for (int j = 1; j <= N_val; ++j) {
                        dist_fw[i][j] = temp_dist[i][j];
                    }
                }
                recompute_all_min_dist_to_airports();
            }
        } else if (type == 2) {  // Add an airport
            int x;
            std::cin >> x;
            if (!has_airport[x]) {
                has_airport[x] = true;
                airport_cities.push_back(x);
                for (int i = 1; i <= N_val; ++i) {
                    if (dist_fw[i][x] != inf) {
                        min_dist_to_airport[i] =
                            std::min(min_dist_to_airport[i], dist_fw[i][x]);
                    }
                }
            }
        } else {  // Calculate sum of shortest paths
            int64_t total_sum = 0;
            for (int i = 1; i <= N_val; ++i) {
                for (int j = 1; j <= N_val; ++j) {
                    int64_t dist_air = inf;
                    if (min_dist_to_airport[i] != inf &&
                        min_dist_to_airport[j] != inf) {
                        dist_air = min_dist_to_airport[i] + T_val +
                                   min_dist_to_airport[j];
                    }
                    int64_t final_dist = std::min(dist_fw[i][j], dist_air);
                    if (final_dist != inf) {
                        total_sum += final_dist;
                    }
                }
            }
            std::cout << total_sum << "\n";
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