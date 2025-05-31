#include <cstddef>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n = 0UL, m = 0UL;
    std::cin >> n >> m;

    std::vector<size_t> a(n, 0), l(m, 0);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < m; ++i) {
        std::cin >> l[i];
    }

    // solution
    /*
        we are given n integers from a1, a2, .... an and m integers l1, l2, .... lm
        we need to find number of unique integers for each li for a_li, a_li+1, ..... a_n.
        so maybe we can build a set<size_t> for unique numbers
    */

    // // FOREACH li in l O(n)
    // for (size_t i = 0; i < m; ++i) {
    //     // construct a set for unique elements that can be found, worst case insertion
    //     // O(m)
    //     std::unordered_set<size_t> unique_a = {};

    //     size_t li = l[i] - 1;

    //     // WHILE li < n, we will insert into the set
    //     while (li < n) {
    //         unique_a.insert(a[li]);
    //         ++li;
    //     }
    //     // unique_a contains only elements of a which are unique and satisfy the question constraints
    //     std::cout << unique_a.size() << std::endl;
    // }
    // overall complexity O(nxm) which we cannot afford
    // so we should do some preprocessing to pre-compute answers for each query and
    // process each query in O(1) time

    // ---------- solution ----------
    std::vector<size_t> suffix_distinct(n, 0);
    std::unordered_set<size_t> hash_set = {};

    // so what it does is calculates the distinct number of elements from the end of the array
    // so for an array like [1, 17, 44, 63, 17, 32, 15000, 17, 12]
    // suffix_disctinct looks like [7,6,6,5,4,4,3,2,1]
    // so suppose li = 1, then starting from index 1 (li - 1 for zero based) we could have
    // seen 7 distinct elements
    for (int64_t i = n - 1; i >= 0; --i) {

        hash_set.insert(a[i]);
        suffix_distinct[i] = hash_set.size();
    }

    for (size_t i = 0; i < m; ++i) {

        std::cout << suffix_distinct[l[i] - 1] << std::endl;
    }

    return 0;
}