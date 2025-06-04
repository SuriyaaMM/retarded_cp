// https://codeforces.com/contest/802/problem/J

#include <cstddef>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using adj_list_t = std::vector<std::vector<std::pair<size_t, size_t>>>;

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, u = 0UL, v = 0UL, c = 0UL;
    std::cin >> n;

    adj_list_t adj_list(n);

    for (size_t i = 0; i < n - 1; ++i) {

        std::cin >> u >> v >> c;
        // construct a directed graph with cost
        adj_list[u].push_back({v, c});
        adj_list[v].push_back({u, c});
    }

    // queue for storing nodes for breadth first order traversal
    std::queue<std::pair<size_t, size_t>> nodes = {};
    // mark visited nodes to avoid infinite looping
    std::vector<size_t> visited(n, 0);
    // max cost is the answer
    size_t max_cost = 0UL;

    // always cost's Jenny 0 to give to Jenny itself
    nodes.push({0, 0});
    // mark Jenny as visited
    visited[0] = 1;

    // WHILE there are nodes to traverse
    while (!nodes.empty()) {
        // get the last pushed node
        std::pair<size_t, size_t> front = nodes.front();
        // pop it off the queue
        nodes.pop();
        // find max cost for choosing this node
        max_cost = std::max(max_cost, front.second);
        // for all neighbours for this node, add them to queue for traversal
        for (auto& neighbour : adj_list[front.first]) {
            // IF that neighbour is not visited then add
            if (!visited[neighbour.first]) {
                // MARK the neighbour as visited
                visited[neighbour.first] = 1;
                // accumulate cost for previous node and this node, then push to queue
                nodes.push({neighbour.first, neighbour.second + front.second});
            }
        }
    }

    std::cout << max_cost << std::endl;

    return 0;
}