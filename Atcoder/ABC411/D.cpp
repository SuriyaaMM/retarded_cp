#include <iostream>
#include <memory>  // Required for std::shared_ptr
#include <string>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t n = 0L, q = 0L;
    std::cin >> n >> q;

    struct string_node {
        int64_t parent_id;
        std::string string;

        string_node(const int64_t& _parent_id, const std::string& _string)
            : parent_id(_parent_id), string(_string) {};
    };

    std::vector<string_node> strings;
    strings.emplace_back(string_node(-1, ""));

    int64_t server_id = 0L, string_id = 0L;
    std::vector<int64_t> pc_ids(n + 1, 0L);

    for (int64_t i = 0L; i < q; ++i) {

        int type = 0L;
        std::cin >> type;

        if (type == 1) {
            int64_t p = 0L;
            std::cin >> p;

            pc_ids[p] = server_id;
        } else if (type == 2) {
            int64_t p = 0L;
            std::string s = "";
            std::cin >> p >> s;
            ++string_id;
            // O(s.size()) operation
            strings.emplace_back(string_node(pc_ids[p], s));
            pc_ids[p] = string_id;
        } else {
            int64_t p = 0L;
            std::cin >> p;
            server_id = pc_ids[p];
        }
    }

    std::vector<std::string> answer;

    while (server_id != -1) {
        answer.emplace_back(strings[server_id].string);
        server_id = strings[server_id].parent_id;
    }

    for (auto it = answer.rbegin(); it != answer.rend(); ++it) {
        std::cout << *it;
    }
    std::cout << "\n";

    return 0;
}