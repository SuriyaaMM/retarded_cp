#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// reads the vector
#define read_vec(begin, end, vec)         \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i];

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

// prints the vector
#define print_vec(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cout << vec[i] << " ";

// infinity
constexpr const int64_t inf = std::numeric_limits<int64_t>::max();
// negative infinity
constexpr const int64_t ninf = std::numeric_limits<int64_t>::min();

// 128 bit types

// pair
using pair_t = std::pair<int64_t, int64_t>;
// generic pair
template <typename T1, typename T2>
using gpair_t = std::pair<T1, T2>;
// unweighted graph
using graph_t = std::vector<std::vector<int64_t>>;
// weighted graph
using wgraph_t = std::vector<std::vector<pair_t>>;

int64_t min_moves = inf;

int64_t min_moves_to_destroy_monster(int64_t h, int64_t moves,
                                     std::vector<pair_t> effects,
                                     std::vector<pair_t>& magic) {
    // if health is already less than zero, then we can quit
    if (h <= 0)
        return moves;

    int64_t reduction_in_this_state = 0LL, reduction_from_previous_states = 0LL,
            max_reduction_in_this_state = ninf, this_states_reduction = 0LL,
            lasting_period = 0LL;

    // calculate effects that are to be passed from previous states
    for (auto it = effects.begin(); it != effects.end();) {
        reduction_from_previous_states += it->first;
        --it->second;
        // if effect's time period ended, we will remove it from effects
        if (it->second == 0)
            effects.erase(it);
        else
            ++it;
    }
    // apply the max magic at this state
    for (int64_t i = 0; i < magic.size(); ++i) {

        std::vector<pair_t> this_branch_effects = effects;

        reduction_in_this_state =
            magic[i].second + reduction_from_previous_states;

        this_states_reduction = magic[i].second;
        lasting_period = magic[i].first - 1;

        // add these to our existing effects
        this_branch_effects.emplace_back(
            std::make_pair(this_states_reduction, lasting_period));

        min_moves = std::min(
            min_moves,
            min_moves_to_destroy_monster(h - reduction_in_this_state, moves + 1,
                                         this_branch_effects, magic));
    }

    return min_moves;
}

void solve() {

    int64_t n = 0LL, h = 0LL;
    std::cin >> n >> h;

    std::vector<pair_t> magic(n, {0, 0});
    read_vecp(0, n, magic);
    // sort the magic based on time
    std::sort(magic.begin(), magic.end());
    // maximum damage that the magic can do (reduced using sum of magic[i].second)
    std::vector<int64_t> max_magic_at_any_time_ti(n, 0);
    for (int64_t i = 0; i < n - 1; ++i) {
        max_magic_at_any_time_ti[i + 1] = std::max(
            max_magic_at_any_time_ti[i], magic[i].first * magic[i].second);
    }

    int64_t moves = 0LL;
    std::vector<pair_t> effects;

    min_moves_to_destroy_monster(h, moves, effects, magic);

    std::cout << min_moves << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}