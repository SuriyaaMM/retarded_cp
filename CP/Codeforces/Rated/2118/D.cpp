#include <algorithm>
#include <iostream>
#include <vector>

enum State { UNKNOWN, VISITING, VISITED };

int N_lights, K_period;
std::vector<long long> P_positions;
std::vector<int> D_delays;

std::vector<std::vector<std::vector<bool>>> memo;
std::vector<std::vector<std::vector<State>>> memo_state;

// direction: 0 for positive (right), 1 for negative (left)
bool solve_dfs(int current_light_idx, long long current_time_mod_k,
               int direction) {
    // If already computed, return cached result
    if (memo_state[current_light_idx][current_time_mod_k][direction] ==
        VISITED) {
        return memo[current_light_idx][current_time_mod_k][direction];
    }
    // If currently visiting, means we found a cycle. This cycle does not lead to leaving.
    // So, we will stay on the strip indefinitely.
    if (memo_state[current_light_idx][current_time_mod_k][direction] ==
        VISITING) {
        return false;
    }

    // Mark current state as visiting
    memo_state[current_light_idx][current_time_mod_k][direction] = VISITING;

    int effective_dir = direction;
    if (current_time_mod_k == D_delays[current_light_idx]) {
        effective_dir = 1 - effective_dir;  // Turn around
    }

    bool result;
    if (effective_dir == 0) {
        if (current_light_idx == N_lights - 1) {
            result = true;
        } else {
            long long time_to_next = P_positions[current_light_idx + 1] -
                                     P_positions[current_light_idx];
            long long next_time_mod_k =
                (current_time_mod_k + time_to_next) % K_period;
            result = solve_dfs(current_light_idx + 1, next_time_mod_k,
                               effective_dir);
        }
    } else {
        if (current_light_idx == 0) {
            result = true;
        } else {
            long long time_to_next = P_positions[current_light_idx] -
                                     P_positions[current_light_idx - 1];
            long long next_time_mod_k =
                (current_time_mod_k + time_to_next) % K_period;
            result = solve_dfs(current_light_idx - 1, next_time_mod_k,
                               effective_dir);
        }
    }

    memo[current_light_idx][current_time_mod_k][direction] = result;
    memo_state[current_light_idx][current_time_mod_k][direction] = VISITED;
    return result;
}

void solve() {
    std::cin >> N_lights >> K_period;
    P_positions.resize(N_lights);
    for (int i = 0; i < N_lights; ++i) {
        std::cin >> P_positions[i];
    }
    D_delays.resize(N_lights);
    for (int i = 0; i < N_lights; ++i) {
        std::cin >> D_delays[i];
    }

    memo.assign(N_lights, std::vector<std::vector<bool>>(
                              K_period, std::vector<bool>(2, false)));
    memo_state.assign(N_lights, std::vector<std::vector<State>>(
                                    K_period, std::vector<State>(2, UNKNOWN)));

    int Q_queries;
    std::cin >> Q_queries;
    for (int q = 0; q < Q_queries; ++q) {
        long long start_pos;
        std::cin >> start_pos;

        auto it =
            std::lower_bound(P_positions.begin(), P_positions.end(), start_pos);

        if (it == P_positions.end()) {
            std::cout << "YES\n";
        } else {
            int starting_light_idx = std::distance(P_positions.begin(), it);
            long long initial_time_taken =
                P_positions[starting_light_idx] - start_pos;
            long long initial_time_mod_k = initial_time_taken % K_period;

            if (solve_dfs(starting_light_idx, initial_time_mod_k, 0)) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}