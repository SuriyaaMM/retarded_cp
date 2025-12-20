#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

bool canFormChain(const vector<long long>& x, int start, int end) {
    if (start == end) return true;

    long long min_t = 0;
    long long max_t = LLONG_MAX;

    long long T = 0;
    for (int i = start + 1; i <= end; i++) {
        long long d = x[i] - x[i - 1];
        int pos = i - start;

        // Update alternating sum
        if (pos % 2 == 1) {
            T += d;
        } else {
            T -= d;
        }

        // Update bounds on t
        if (pos % 2 == 0) {
            min_t = max(min_t, T);
        } else {
            max_t = min(max_t, T);
        }
    }

    return min_t <= max_t;
}

void solve() {
    int n;
    cin >> n;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vector<int> dp(n + 1);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = i;  // worst case: each point is its own chain
        for (int j = 0; j < i; j++) {
            if (canFormChain(x, j, i - 1)) {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }

    cout << n - dp[n] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}