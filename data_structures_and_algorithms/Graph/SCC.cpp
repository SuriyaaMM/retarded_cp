#include <bits/stdc++.h>

void dfs(int64_t current_node, int64_t &timer,
         std::vector<std::vector<int64_t>> &adjlist,
         std::vector<int64_t> &timestamp, std::vector<int64_t> &lowlink,
         std::vector<bool> &onstack, std::stack<int64_t> &st,
         std::vector<std::vector<int64_t>> *pscc) {

    timestamp[current_node] = timer;
    lowlink[current_node] = timer;
    onstack[current_node] = true;
    st.emplace(current_node);
    timer++;

    for (const auto &neighbour : adjlist[current_node]) {
        // IF already visited the node & is in stack, then it is an backedge
        if (timestamp[neighbour] != -1 && onstack[neighbour] == true) {
            lowlink[current_node] =
                std::min(lowlink[current_node], timestamp[neighbour]);
        }

        // IF we have not visited the node
        if (timestamp[neighbour] == -1) {
            // we will visit the node's subtree
            dfs(neighbour, timer, adjlist, timestamp, lowlink, onstack, st,
                pscc);
            // neighbour might have just hit the root of the scc
            // update the low links by choosing the lowest one of all
            lowlink[current_node] =
                std::min(lowlink[neighbour], lowlink[current_node]);
        }
    }

    // after visiting all the subgraphs from the current node
    if (timestamp[current_node] == lowlink[current_node]) {
        // initialise and empty compoenent and push back it
        pscc->push_back({});
        pscc->back().emplace_back(current_node);

        // if either we reach the current node (end of SCC)
        // or we have emptied the stack, pop the scc's off the shelf
        for (;;) {
            if (st.empty()) break;
            int64_t v = st.top();
            st.pop();
            // remove from history
            onstack[v] = false;
            pscc->back().emplace_back(v);
            if (v == current_node) break;
        }
    }
}

void scc(std::vector<std::vector<int64_t>> &adjlist,
         std::vector<std::vector<int64_t>> *pscc) {

    // Implements Tarjans Algorithm

    int64_t n = (int64_t)adjlist.size();

    std::vector<int64_t> timestamp(n, -1);
    std::vector<int64_t> lowlink(n, 0);
    std::vector<bool> onstack(n, false);
    std::stack<int64_t> st;

    int64_t timer = 0;
    for (int64_t i = 0; i < n; ++i) {
        if (timestamp[i] == -1) {
            dfs(i, timer, adjlist, timestamp, lowlink, onstack, st, pscc);
        }
    }
}

int main(int, char **) {}