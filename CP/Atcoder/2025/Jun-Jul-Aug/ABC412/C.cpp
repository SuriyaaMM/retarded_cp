#include <algorithm>
#include <climits>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

void solve() {
    int64_t N;
    std::cin >> N;
    std::vector<int64_t> S(N);
    for (int64_t i = 0; i < N; ++i) {
        std::cin >> S[i];
    }

    std::vector<std::pair<int64_t, int64_t>> dominoes(N);
    for (int64_t i = 0; i < N; ++i) {
        dominoes[i] = {S[i], i + 1};
    }
    std::sort(dominoes.begin(), dominoes.end());

    // BFS
    std::queue<int64_t> q;
    std::vector<int64_t> dist(N + 1, INT64_MAX);
    q.push(1);
    dist[1] = 1;

    int64_t processed_ptr = 0;

    while (!q.empty()) {

        if (dist[N] != INT64_MAX) {
            break;
        }

        int64_t current_dist = dist[q.front()];

        std::queue<int64_t> current_level_q;

        while (!q.empty() && dist[q.front()] == current_dist) {
            current_level_q.push(q.front());
            q.pop();
        }

        int64_t max_reach_S_this_level = 0;
        while (!current_level_q.empty()) {
            int64_t u = current_level_q.front();
            current_level_q.pop();
            max_reach_S_this_level =
                std::max(max_reach_S_this_level, 2 * S[u - 1]);
        }

        auto it =
            std::upper_bound(dominoes.begin() + processed_ptr, dominoes.end(),
                             std::make_pair(max_reach_S_this_level, INT64_MAX));
        int64_t end_pos = it - dominoes.begin();

        for (int64_t k = processed_ptr; k < end_pos; ++k) {
            int64_t v = dominoes[k].second;
            if (dist[v] == INT64_MAX) {
                dist[v] = current_dist + 1;
                q.push(v);
            }
        }

        processed_ptr = end_pos;
    }

    if (dist[N] != INT64_MAX) {
        std::cout << dist[N] << "\n";
    } else {
        std::cout << -1 << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}