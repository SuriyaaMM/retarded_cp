#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t Height, Width, TrashCount;
    std::cin >> Height >> Width >> TrashCount;

    // Maps Row -> Set of Columns with Trash
    std::unordered_map<size_t, std::unordered_set<size_t>> RowTrash;
    // Maps Column -> Set of Rows with Trash
    std::unordered_map<size_t, std::unordered_set<size_t>> ColTrash;

    for (size_t I = 0; I < TrashCount; ++I) {

        size_t X, Y;
        std::cin >> X >> Y;

        --X; --Y; // 0-based indexing

        RowTrash[X].insert(Y);
        ColTrash[Y].insert(X);
    }

    size_t QueryCount;

    std::cin >> QueryCount;

    std::vector<std::pair<size_t, size_t>> Queries(QueryCount);

    for (size_t I = 0; I < QueryCount; ++I) {

        size_t Type, Val;
        std::cin >> Type >> Val;

        --Val; // 0-based

        Queries[I] = { Type, Val };
    }

    for (const auto& [Type, Val] : Queries) {

        if (Type == 1) {
           
            auto It = RowTrash.find(Val);

            if (It == RowTrash.end()) {

                std::cout << 0 << '\n';
                continue;
            }

            size_t Count = It->second.size();

            for (auto Col : It->second) {

                ColTrash[Col].erase(Val);

                if (ColTrash[Col].empty()) {

                    ColTrash.erase(Col);
                }
            }
            RowTrash.erase(Val);
            std::cout << Count << '\n';

        }
        else {
           
            auto It = ColTrash.find(Val);

            if (It == ColTrash.end()) {

                std::cout << 0 << '\n';
                continue;
            }

            size_t Count = It->second.size();

            for (auto Row : It->second) {

                RowTrash[Row].erase(Val);

                if (RowTrash[Row].empty()) {

                    RowTrash.erase(Row);
                }
            }

            ColTrash.erase(Val);

            std::cout << Count << '\n';
        }
    }

    return 0;
}
