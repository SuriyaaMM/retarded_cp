#include <iostream>
#include <unordered_set>
#include <vector>

void dfs(size_t current_node, size_t parent_node, size_t current_streak,
         std::vector<size_t>& a, size_t& m,
         std::vector<std::vector<size_t>>& adj_list, size_t& reachable_count) {

    if (a[current_node] == 1) {
        ++current_streak;
    } else {
        current_streak = 0;
    }

    // If we exceed the maximum consecutive cats, return early
    if (current_streak > m) {
        return;
    }

    bool is_leaf = true;
    for (size_t& neighbour : adj_list[current_node]) {
        if (neighbour != parent_node) {
            is_leaf = false;
            break;
        }
    }

    if (is_leaf) {
        ++reachable_count;
        return;
    }

    for (size_t& neighbour : adj_list[current_node]) {
        if (neighbour !=
            parent_node) {  // Important: check parent before recursion
            dfs(neighbour, current_node, current_streak, a, m, adj_list,
                reachable_count);
        }
    }
}

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n = 0UL, m = 0UL, xi = 0UL, yi = 0UL;
    std::cin >> n >> m;

    std::vector<size_t> a(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<std::vector<size_t>> adj_list(n);

    for (size_t i = 0; i < n - 1; ++i) {
        std::cin >> xi >> yi;
        adj_list[xi - 1].emplace_back(yi - 1);
        adj_list[yi - 1].emplace_back(xi - 1);
    }

    size_t reachable_count = 0UL;
    // Use SIZE_MAX or n as parent for root node to avoid confusion
    dfs(0, SIZE_MAX, 0, a, m, adj_list, reachable_count);
    std::cout << reachable_count << std::endl;

    return 0;
}