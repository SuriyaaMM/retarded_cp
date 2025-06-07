// for size_t
#include <cstddef>
// for storing adjacency list
#include <vector>
// stack for dfs
#include <stack>

// using adjacency list as our preferred graph type
using graph_t = std::vector<std::vector<size_t>>;

void dfs(graph_t& graph, size_t num_vertices, size_t start_node) {

    // visited vector for avoiding loops
    std::vector<bool> visited(num_vertices, 0);

    // initialize stack
    std::stack<size_t> dfs_stack;
    dfs_stack.push(start_node);

    // mark this initial node as visited
    visited[start_node] = true;

    // if there is nothing in the stack, it means we have explored the graph
    while (!dfs_stack.empty()) {
        // the next node (v) to visit will always be stored at top of our stack
        size_t v = dfs_stack.top();
        // pop this node off the stack
        dfs_stack.pop();
        // for all neighbours to this v, push them to stack
        for (size_t& neighbour : graph[v]) {
            // push only if the neighbour is not visited already, or else we would end up in loop
            if (!visited[neighbour]) {
                // mark this neighbour as visited
                visited[neighbour] = true;
                // push it to stack
                dfs_stack.push(neighbour);
            }
        }
    }
}