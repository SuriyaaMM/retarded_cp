#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;

ll compute_sum_floor(ll N, ll MOD) {
    ll sum = 0;
    for (ll l = 1; l <= N;) {
        ll q = N / l;
        if (q == 0)
            break;
        ll r = N / q;
        if (r > N)
            r = N;
        sum = (sum + (q % MOD) * ((r - l + 1) % MOD) % MOD) % MOD;
        l = r + 1;
    }
    return sum;
}

int main() {
    ll N;
    cin >> N;
    if (N < 3) {
        cout << 0 << endl;
        return 0;
    }
    ll sum_floor = compute_sum_floor(N, MOD);

    ll half_n_minus_1_times_n = (N - 1) % MOD * (N % MOD) % MOD;
    ll inv2 = (MOD + 1) / 2;
    ll first_term = (half_n_minus_1_times_n * inv2) % MOD;

    ll ans = (first_term + N % MOD - sum_floor + MOD) % MOD;

    cout << ans << endl;
    return 0;
}