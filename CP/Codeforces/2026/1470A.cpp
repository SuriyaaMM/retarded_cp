#include <bits/stdc++.h>

/*
The problem becomes trivial once we sort the array k.
after we sort the array k, for the first example it looks like this 

2 2 3 3 4
3 5 12 20

now we have two options, forward iterate through k or backward iterate through k
and pick the smallest index.
if we forward iterate and pick the smallest value everytime using two pointers
we see that as we go higher and higher, the cost increases because we sorted
the array k.
so it should be immediatly obvious here that for larger values to pair with
smaller values to get the most because choosing cost(3) for k(2) will only
make things worse for us in future because it eliminates something that i can
pair k(4) with and i am forced to pair k(4) with cost(20).

the code assumes one based indexing
if(k[pk] > pc) translates to whether I can pick this cost for the current k,
if i can pick this i should absolutely pick this or else i have no other
option but pick c[k[pk]]
*/

void solve() {
    int32_t n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<int32_t> k(n + 1, 0);
    std::vector<int64_t> c(m + 1, 0);

    for (int32_t i = 1; i <= n; ++i) std::cin >> k[i];
    for (int32_t i = 1; i <= m; ++i) std::cin >> c[i];

    std::sort(k.begin(), k.end());

    int32_t pk = n, pc = 1;
    int64_t answer = 0;

    for (; (pk > 0) && (pc <= m); pk--) {
        if (k[pk] > pc) {
            answer += c[pc];
            pc++;
        } else {
            answer += c[k[pk]];
        }
    }

    std::cout << answer << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}