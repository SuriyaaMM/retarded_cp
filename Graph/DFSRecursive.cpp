// for size_t
#include <cstddef>
// for storing adjacency list
#include <vector>

// using adjacency list as our preferred graph type
using graph_t = std::vector<std::vector<size_t>>;

void dfs_recursive(graph_t& graph, size_t start_node,
                   std::vector<bool>& visited) {

    // for all the neighbours to this node we will perform a recursive dfs on them
    // this will make sure that it goes depth wise and returns then backtracks the path
    for (size_t& neighbour : graph[start_node]) {
        // if this neighbour is not visited, then perform dfs recursively
        if (!visited[neighbour]) {
            // mark this neighbour as visited
            visited[neighbour] = true;
            // recursive dfs
            dfs_recursive(graph, neighbour, visited);
        }
    }

    // if there are no neighbours left then backtrack
    return;
}