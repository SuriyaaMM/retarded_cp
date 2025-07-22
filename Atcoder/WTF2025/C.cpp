#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

bool is_valid(const vector<i64>& A, i64 d) {
    i64 leftover = 0;
    for (i64 a : A) {
        i64 total = a + leftover;
        i64 use = min(total, 2 * d);
        leftover = use - a;
        if (leftover < 0)
            leftover = 0;
    }
    return leftover == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    vector<string> answers;
    while (T--) {
        int N;
        cin >> N;
        vector<i64> A(N);
        i64 max_a = 0;
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            max_a = max(max_a, A[i]);
        }

        i64 low = 1, high = max_a;
        while (low < high) {
            i64 mid = (low + high) / 2;
            if (is_valid(A, mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        cout << low << '\n';
    }

    return 0;
}
