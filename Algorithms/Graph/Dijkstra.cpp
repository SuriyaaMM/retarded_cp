// for size_t
#include <cstddef>
// for storing adjacency list
#include <vector>
// for min heap (priority queue)
#include <queue>
// for max value of size_t
#include <limits>

// pair_t will hold (vertex, weight)
using pair_t = std::pair<size_t, size_t>;
// using adjacency list as our preferred graph type
using graph_t = std::vector<std::vector<pair_t>>;

void dijkstra(graph_t& graph, size_t num_vertices, size_t start_node) {

    // our distances array for calculating distance, initially every node is unreachable (inf distance)
    std::vector<size_t> distances(num_vertices,
                                  std::numeric_limits<size_t>::max());
    distances[start_node] = 0;

    // visited vector for avoiding loops
    std::vector<bool> visited(num_vertices, false);

    // mark this initial node as visited
    visited[start_node] = true;

    // priority_queue is essential minheap when used with greater<T>
    // here greater<pair_t> will sort elements by pair_t->first then pair_t->second
    std::priority_queue<pair_t, std::vector<pair_t>, std::greater<pair_t>>
        min_heap;

    // initialize the min heap always we can reach the starting node with 0 distance
    min_heap.emplace(pair_t(start_node, 0));

    // if there is nothing in the priority_queue, it means we have explored the graph
    while (!min_heap.empty()) {
        // get the least distance neighbour
        auto& [distance, v] = min_heap.top();
        // pop it off the heap
        min_heap.pop();

        // for all the neighbours
        for (auto& [neighbour, w_neighbour] : graph[v]) {
            // if this neighbour is not visited previouslt
            if (!visited[neighbour]) {
                // if their distance is smaller then update it
                // distance[v](current minimal distance to v) + weight(distance to travel to neighbour)
                if (w_neighbour > distances[v] + distance) {
                    w_neighbour = distances[v] + distance;
                }
                // add it to to queue
                min_heap.push(pair_t(w_neighbour, neighbour));
            }
        }
    }
}