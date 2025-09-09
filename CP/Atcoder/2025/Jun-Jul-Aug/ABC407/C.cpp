#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>

std::string applyB(const std::string& t) {
    std::string result = t;
    for (char& c : result) {
        c = (c == '9') ? '0' : c + 1;
    }
    return result;
}

int bfs_min_presses(const std::string& S) {

    std::unordered_set<std::string> visited;
    std::queue<std::pair<std::string, int>> q;

    q.push({"", 0});
    visited.insert("");

    while (!q.empty()) {
        auto [t, steps] = q.front();
        q.pop();

        if (t == S)
            return steps;
        if (t.length() > S.length())
            continue;

        // Press A
        std::string nextA = t + "0";
        if (!visited.count(nextA)) {
            visited.insert(nextA);
            q.push({nextA, steps + 1});
        }

        // Press B
        if (!t.empty()) {
            std::string nextB = applyB(t);
            if (!visited.count(nextB)) {
                visited.insert(nextB);
                q.push({nextB, steps + 1});
            }
        }
    }

    return -1;  // Should not reach here if S is reachable
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string S;
    std::cin >> S;

    int result = bfs_min_presses(S);
    std::cout << result << "\n";
    return 0;
}
