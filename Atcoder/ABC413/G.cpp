#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

struct DSU {
    std::vector<int> parent;
    DSU(int n) : parent(n) { std::iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }
    bool connected(int x, int y) { return find(x) == find(y); }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int H, W, K;
    std::cin >> H >> W >> K;

    std::set<std::pair<int, int>> obstacles;
    std::map<int, std::vector<int>> row_obs, col_obs;
    for (int i = 0; i < K; i++) {
        int r, c;
        std::cin >> r >> c;
        obstacles.insert({r, c});
        row_obs[r].push_back(c);
        col_obs[c].push_back(r);
    }

    // Step 1: Identify Critical Cells
    std::set<std::pair<int, int>> critical_set;
    critical_set.insert({1, 1});
    critical_set.insert({H, W});

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (auto const& [r, c] : obstacles) {
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            if (nr >= 1 && nr <= H && nc >= 1 && nc <= W &&
                obstacles.find({nr, nc}) == obstacles.end()) {
                critical_set.insert({nr, nc});
            }
        }
    }

    std::vector<std::pair<int, int>> critical_cells(critical_set.begin(),
                                                    critical_set.end());
    std::map<std::pair<int, int>, int> cell_to_idx;
    for (size_t i = 0; i < critical_cells.size(); ++i) {
        cell_to_idx[critical_cells[i]] = i;
    }

    // Step 2: Group Critical Cells by Row and Column
    std::map<int, std::vector<int>> row_crit, col_crit;
    for (const auto& cell : critical_cells) {
        row_crit[cell.first].push_back(cell.second);
        col_crit[cell.second].push_back(cell.first);
    }

    DSU dsu(critical_cells.size());

    // Step 3: Connect Along Rows
    for (auto const& [r, crit_cols_map] : row_crit) {
        std::vector<int> crit_cols = crit_cols_map;  // Get a mutable copy
        auto obs_it = row_obs.find(r);
        if (obs_it == row_obs.end()) {  // No obstacles in this row
            for (size_t i = 0; i < crit_cols.size() - 1; ++i) {
                dsu.unite(cell_to_idx[{r, crit_cols[i]}],
                          cell_to_idx[{r, crit_cols[i + 1]}]);
            }
        } else {
            std::vector<int>& obs = obs_it->second;
            std::sort(obs.begin(), obs.end());
            for (size_t i = 0; i < crit_cols.size() - 1; ++i) {
                int c1 = crit_cols[i];
                int c2 = crit_cols[i + 1];
                auto it = std::lower_bound(obs.begin(), obs.end(), c1);
                if (it == obs.end() ||
                    *it > c2) {  // No obstacle between c1 and c2
                    dsu.unite(cell_to_idx[{r, c1}], cell_to_idx[{r, c2}]);
                }
            }
        }
    }

    // Step 4: Connect Along Columns
    for (auto const& [c, crit_rows_map] : col_crit) {
        std::vector<int> crit_rows = crit_rows_map;  // Get a mutable copy
        auto obs_it = col_obs.find(c);
        if (obs_it == col_obs.end()) {  // No obstacles in this column
            for (size_t i = 0; i < crit_rows.size() - 1; ++i) {
                dsu.unite(cell_to_idx[{crit_rows[i], c}],
                          cell_to_idx[{crit_rows[i + 1], c}]);
            }
        } else {
            std::vector<int>& obs = obs_it->second;
            std::sort(obs.begin(), obs.end());
            for (size_t i = 0; i < crit_rows.size() - 1; ++i) {
                int r1 = crit_rows[i];
                int r2 = crit_rows[i + 1];
                auto it = std::lower_bound(obs.begin(), obs.end(), r1);
                if (it == obs.end() ||
                    *it > r2) {  // No obstacle between r1 and r2
                    dsu.unite(cell_to_idx[{r1, c}], cell_to_idx[{r2, c}]);
                }
            }
        }
    }

    // Step 5: Check Final Connectivity
    if (cell_to_idx.find({1, 1}) == cell_to_idx.end() ||
        cell_to_idx.find({H, W}) == cell_to_idx.end()) {
        std::cout << "No\n";  // Should not happen if H,W > 0
    } else {
        int startIdx = cell_to_idx[{1, 1}];
        int endIdx = cell_to_idx[{H, W}];
        if (dsu.connected(startIdx, endIdx)) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}