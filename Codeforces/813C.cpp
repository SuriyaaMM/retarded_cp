// https://codeforces.com/contest/813/problem/C

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>

// vertex -> {(neighbour, road_index)}
using pair_t = std::pair<size_t, size_t>;
using graph_t = std::vector<std::vector<pair_t>>;

void dfs(size_t current_node, graph_t& graph, std::vector<size_t>& visited,
         std::unordered_map<size_t, std::vector<size_t>>& repaired_roads,
         size_t& k, bool adjacent) {

    // ITERATE through all the neighbours and visit them
    for (size_t i = 0; i < graph[current_node].size(); ++i) {
        pair_t neighbour = graph[current_node][i];
        // IF some neighbour is unvisited
        if (!adjacent && !visited[neighbour.first]) {
            // this node has an neighbour which hasn't been visited yet (not repaired yet)
            // so we will add this neighbour to repaired roads and mark them as visited
            visited[current_node] = 1;
            // we can repair any number of roads today until the neighbour has someone
            // to visit
            repaired_roads[k].emplace_back(neighbour.second);
            // skip the very adjacent neighbour
            adjacent = true;
            // visit this neighbour
            dfs(neighbour.first, graph, visited, repaired_roads, k, !adjacent);
        }
        // We have visited all the depth neighbours of this and added them to repairable roads
        // Any neighbour in this level itself can be repaired only after a day
        if (i >= 1) {
            ++k;
        }
    }
    // at this point, none of the neighbour has someone to visit
    return;
}

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, ui = 0UL, vi = 0UL;
    std::cin >> n;

    // n+1 for 1-based indexing
    graph_t graph(n + 1);

    for (size_t i = 1; i < n; ++i) {

        std::cin >> ui >> vi;
        // construct bidirectional graph
        graph[ui].emplace_back(std::pair(vi, i));
        graph[vi].emplace_back(std::pair(ui, i));
    }

    // since it is a bidirectional graph
    std::vector<size_t> visited(n + 1);
    // day -> {road1, road2, road3 .... }
    std::unordered_map<size_t, std::vector<size_t>> repaired_roads;
    size_t k = 1UL;
    dfs(1, graph, visited, repaired_roads, k, true);

    std::cout << k << std::endl;
    for (auto it = repaired_roads.begin(); it != repaired_roads.end(); ++it) {

        std::cout << it->second.size() << " ";
        for (size_t& road : it->second) {

            std::cout << road << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}