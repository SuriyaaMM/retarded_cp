// https://codeforces.com/contest/29/problem/C

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>

// unordered map, because vertices are sparse, ordered vector would require
// O(10^9) space at worst case, map would do it in O(n) in the worst case
using graph_t = std::unordered_map<size_t, std::vector<size_t>>;

void dfs(size_t current_node, graph_t& adj_list, std::vector<size_t>& path,
         std::unordered_map<size_t, bool>& visited) {

    // add this node to the path
    path.emplace_back(current_node);
    // mark this node as visited (avoid infinite loops)
    visited[current_node] = true;
    // find the adjacency_list for this node
    auto it = adj_list.find(current_node);
    // IF we have one then proceed
    if (it != adj_list.end()) {
        // ITERATE through the neighbours
        for (size_t& neighbour : it->second) {
            // CHECK whether neighbour is already visited
            auto it2 = visited.find(neighbour);
            if (it2 == visited.end() || it2->second == false) {
                // recurse on that neighbour
                dfs(neighbour, adj_list, path, visited);
            }
        }
    } else {
        // IF we don't have any more left in the adjacency list, then end the recursion
        return;
    }
}

int main(int, char**) {

    // standard io optimizations
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, u = 0UL, v = 0UL;
    std::cin >> n;

    graph_t adj_list;

    for (size_t i = 0; i < n; ++i) {

        std::cin >> u >> v;
        // construct an undirected graph
        adj_list[u].emplace_back(v);
        adj_list[v].emplace_back(u);
    }

    // find the begin vertex, it might be the end too, order doesn't matter here
    size_t begin_vertex = 0UL;
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {

        if (it->second.size() == 1) {
            begin_vertex = it->first;
            break;
        }
    }

    // unordered_map because sparse vertices
    std::unordered_map<size_t, bool> visited;
    // our actual path
    std::vector<size_t> path = {};
    // perform dfs on the graph to find the path
    dfs(begin_vertex, adj_list, path, visited);
    // print out the path
    for (size_t& numbers : path) {

        std::cout << numbers << " ";
    }
    std::cout << std::endl;

    return 0;
}