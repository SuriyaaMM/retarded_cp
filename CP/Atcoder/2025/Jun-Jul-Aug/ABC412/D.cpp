#include <algorithm>  // For std::sort, std::next_permutation, std::min
#include <climits>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

// Global variables
int N, M;
std::set<std::pair<int, int>> input_edges;  // Stores edges of the initial graph
int min_operations = INT_MAX;  // Stores the minimum operations found

// Recursive function to generate partitions of vertices
// `current_vertex_idx`: The vertex we are currently trying to assign to a part
// `current_partition`: A vector of vectors, where each inner vector is a part (potential cycle)
void generate_partitions(int current_vertex_idx,
                         std::vector<std::vector<int>>& current_partition) {
    // Base case: If all vertices have been assigned to a part
    if (current_vertex_idx == N + 1) {
        // All vertices are partitioned. Now, evaluate this specific partition.
        // First, check if all parts have at least 3 vertices (required for a cycle).
        for (const auto& part : current_partition) {
            if (part.size() < 3) {
                return;  // Invalid partition for forming cycles, prune this branch
            }
        }

        // If the partition is valid, proceed to generate actual cycles for each part
        // and calculate the total edges of the 2-regular graph.

        // This lambda function recursively tries all cycle configurations for each part
        // of the current_partition.
        std::function<void(int, std::set<std::pair<int, int>>)>
            explore_cycle_configurations = [&](int part_idx,
                                               std::set<std::pair<int, int>>
                                                   accumulated_edges) {
                // Base case for `explore_cycle_configurations`: all parts have been assigned a cycle.
                if (part_idx == current_partition.size()) {
                    // `accumulated_edges` now contains all edges for a valid 2-regular graph.
                    // Calculate the symmetric difference with `input_edges`.
                    int diff = 0;
                    for (const auto& edge : accumulated_edges) {
                        if (input_edges.find(edge) == input_edges.end()) {
                            diff++;  // Edge in target but not in input (add operation)
                        }
                    }
                    for (const auto& edge : input_edges) {
                        if (accumulated_edges.find(edge) ==
                            accumulated_edges.end()) {
                            diff++;  // Edge in input but not in target (remove operation)
                        }
                    }
                    min_operations = std::min(min_operations, diff);
                    return;
                }

                // Recursive step for `explore_cycle_configurations`:
                // Get the vertices for the current part.
                std::vector<int> part_nodes = current_partition[part_idx];

                // To generate unique cycles and avoid rotations/reflections:
                // 1. Sort the part_nodes to ensure a canonical starting point for permutation.
                // 2. Fix the first element of the permutation.
                // 3. Permute the remaining elements.
                // 4. To handle reflections (e.g., 1-2-3-1 vs 1-3-2-1), we will simply generate both
                //    and insert their edge sets into a `std::set<std::set<std::pair<int, int>>>`
                //    to automatically handle uniqueness.

                std::sort(part_nodes.begin(), part_nodes.end());

                // Store unique edge sets for cycles formed by `part_nodes`
                std::set<std::set<std::pair<int, int>>>
                    distinct_cycle_edge_sets_for_this_part;

                // Generate all permutations of `part_nodes` with the first element fixed.
                // Create a permutation vector starting with the fixed first node.
                std::vector<int> current_perm = part_nodes;

                // The `do-while(next_permutation)` on `current_perm.begin() + 1` correctly generates (k-1)! permutations.
                // By inserting the resulting edge set into a `std::set`, we inherently handle rotational and reflection duplicates.
                do {
                    std::set<std::pair<int, int>> temp_cycle_edges;
                    for (size_t i = 0; i < current_perm.size(); ++i) {
                        int u = current_perm[i];
                        int v =
                            current_perm[(i + 1) %
                                         current_perm
                                             .size()];  // Connect last to first
                        if (u > v)
                            std::swap(
                                u,
                                v);  // Store edges canonically (smaller, larger)
                        temp_cycle_edges.insert({u, v});
                    }
                    distinct_cycle_edge_sets_for_this_part.insert(
                        temp_cycle_edges);
                } while (std::next_permutation(current_perm.begin() + 1,
                                               current_perm.end()));

                // Now, for each distinct cycle configuration for the current part,
                // recurse to assign a cycle configuration to the next part.
                for (const auto& cycle_edges_config :
                     distinct_cycle_edge_sets_for_this_part) {
                    std::set<std::pair<int, int>> next_accumulated_edges =
                        accumulated_edges;
                    for (const auto& edge : cycle_edges_config) {
                        next_accumulated_edges.insert(edge);
                    }
                    explore_cycle_configurations(part_idx + 1,
                                                 next_accumulated_edges);
                }
            };

        // Initial call to explore cycle configurations for the first part (index 0)
        explore_cycle_configurations(0, std::set<std::pair<int, int>>{});
        return;  // Return after evaluating this partition
    }

    // Recursive step for `generate_partitions`:
    // Try to add `current_vertex_idx` to an existing part, or start a new part.

    // Option 1: Add `current_vertex_idx` to an existing part
    for (auto& part : current_partition) {
        part.push_back(current_vertex_idx);
        generate_partitions(current_vertex_idx + 1, current_partition);
        part.pop_back();  // Backtrack: remove vertex for other branches
    }

    // Option 2: Start a new part with `current_vertex_idx`
    current_partition.push_back({current_vertex_idx});
    generate_partitions(current_vertex_idx + 1, current_partition);
    current_partition
        .pop_back();  // Backtrack: remove the new part for other branches
}

int main() {
    // Optimize I/O operations
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Read N and M
    std::cin >> N >> M;

    // Read input edges and store them in a set for efficient lookup
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        if (u > v)
            std::swap(u,
                      v);  // Ensure canonical representation (smaller, larger)
        input_edges.insert({u, v});
    }

    // Start the partitioning process from vertex 1
    std::vector<std::vector<int>> initial_partition;
    generate_partitions(1, initial_partition);

    // Print the minimum operations found
    std::cout << min_operations << "\n";

    return 0;
}