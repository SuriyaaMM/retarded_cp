#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using pair_t = std::pair<int64_t, int64_t>;

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    std::vector<pair_t> char_counts(26);

    for (int i = 0; i < 26; ++i) {
        char_counts[i] = std::make_pair(0, i);
    }

    for (char ch : s) {
        char_counts[ch - 'a'].first++;
    }

    // reverse sort
    std::sort(char_counts.begin(), char_counts.end(), std::greater<pair_t>());

    // distribute the most frequent character to balance counts
    while (char_counts[0].first > char_counts[1].first) {
        std::cout << static_cast<char>('a' + char_counts[0].second);
        char_counts[0].first--;
    }

    // distribute remaining characters in a round-robin fashion using a queue
    std::queue<pair_t> q;
    for (int i = 0; i < 26; ++i) {
        if (char_counts[i].first > 0) {
            q.push(char_counts[i]);
        }
    }

    while (!q.empty()) {
        pair_t current_char_pair = q.front();
        q.pop();

        std::cout << static_cast<char>('a' + current_char_pair.second);
        current_char_pair.first--;

        if (current_char_pair.first > 0) {
            q.push(current_char_pair);
        }
    }
    std::cout << std::endl;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T = 1;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}