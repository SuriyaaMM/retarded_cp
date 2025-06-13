#include <cstddef>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using edge_t = std::pair<size_t, size_t>;
using graph_t = std::vector<std::vector<edge_t>>;
using minheap_t =
    std::priority_queue<edge_t, std::vector<edge_t>, std::greater<edge_t>>;
using maxheap_t = std::priority_queue<edge_t>;

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    char i = 'b';

    std::cout << static_cast<int>(i - 'a') << std::endl;

    return 0;
}