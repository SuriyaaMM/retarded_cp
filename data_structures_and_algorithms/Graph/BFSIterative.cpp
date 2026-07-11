// for storing our bfs traversal order
#include <queue>
// for adjacency list
#include <vector>
// for size_t
#include <cstddef>

// using adjacency list as our preferred graph type
using graph_t = std::vector<std::vector<size_t>>;

void bfs(graph_t& graph, size_t num_vertices, size_t start_node) {

    // visited vector for avoiding loops
    std::vector<bool> visited(num_vertices, 0);

    // mark this initial node as visited
    visited[start_node] = true;

    // initialize queue
    std::queue<size_t> bfs_queue;
    bfs_queue.push(start_node);

    // if there is nothing in the queue, it means we have explored the graph
    while (!bfs_queue.empty()) {
        // the next node (v) to visit will always be stored at front of our queue
        size_t v = bfs_queue.front();
        // pop this node off the queue
        bfs_queue.pop();
        // for all neighbours to this v, push them to queue
        for (size_t& neighbour : graph[v]) {
            // push only if the neighbour is not visited already, or else we would end up in loop
            if (!visited[neighbour]) {
                // mark this neighbour as visited
                visited[neighbour] = true;
                // push it to queue
                bfs_queue.push(neighbour);
            }
        }
    }
}