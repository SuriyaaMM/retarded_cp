#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

long long MOD = 998244353;

// --- Modular Arithmetic Helpers ---
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) { return power(n, MOD - 2); }

// Global Inverses
long long INV4, INV16;

// Indices mapping: 0:U, 1:D, 2:L, 3:R
// Directions
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

void solve() {
    int N, M;
    cin >> N >> M;

    // dp[c][tr_type]
    // Stores flow entering cell (r, c) from TOP, conditioned on P(r-1, c) ==
    // tr_type.
    vector<vector<long long>> dp_u(M + 1, vector<long long>(4, 0));

    // Buffer for next row
    vector<vector<long long>> next_dp_u(M + 1, vector<long long>(4, 0));

    // Global accumulator for probability that car STOPS inside grid
    long long total_valid_prob = 0;

    for (int r = 1; r <= N; r++) {
        // Horizontal flow entering cell (r, c) from LEFT
        // h_flow[bl_type] -> conditioned on P(r, c-1) == bl_type
        vector<long long> h_flow(4, 0);
        vector<long long> next_h_flow(4, 0);

        // Reset next row buffer
        for (int c = 0; c <= M; c++)
            fill(next_dp_u[c].begin(), next_dp_u[c].end(), 0);

        for (int c = 1; c <= M; c++) {
            // Reset horizontal out buffer
            fill(next_h_flow.begin(), next_h_flow.end(), 0);

            // SPECIAL CASE: (1, 1) - Injection point
            if (r == 1 && c == 1) {
                // We treat the car as appearing here with probability 1.
                // It effectively behaves like "Flow from Top" with
                // unconstrained parents, OR "Flow from Left" with unconstrained
                // parents. Let's manually simulate the transitions for the
                // start cell.

                // Iterate over BR (P(1,1))
                for (int br = 0; br < 4; br++) {
                    long long p_br = INV4;

                    // 1. Try Move Down
                    // Condition: BL != R, BR != L
                    // BL is virtual/uniform -> P(BL != R) = 3/4
                    long long prob_down = 0;
                    if (br != LEFT) {
                        prob_down = (3 * INV4) % MOD;
                    }

                    // 2. Try Move Right
                    // Condition: Blocked Down AND Right Open
                    // Blocked Down = 1 - prob_down
                    // Right Open: TR != D, BR != U
                    // TR is virtual/uniform -> P(TR != D) = 3/4
                    long long prob_blocked_down = (1 + MOD - prob_down) % MOD;

                    long long prob_right = 0;
                    if (br != UP) {
                        // If BR!=U, P(RightOpen) = 3/4
                        prob_right = (prob_blocked_down * 3 % MOD * INV4) % MOD;
                    } else {
                        // If BR==U, Right is blocked (P(RightOpen)=0)
                        prob_right = 0;
                    }

                    // 3. Stop
                    long long prob_stop =
                        (1 + MOD - prob_down - prob_right + MOD + MOD) % MOD;

                    // Accumulate Stop
                    total_valid_prob =
                        (total_valid_prob + prob_stop * p_br) % MOD;

                    // Send Flow Down (becomes V-flow for (2,1) with TR = br)
                    next_dp_u[c][br] =
                        (next_dp_u[c][br] + prob_down * p_br) % MOD;

                    // Send Flow Right (becomes H-flow for (1,2) with BL = br)
                    next_h_flow[br] =
                        (next_h_flow[br] + prob_right * p_br) % MOD;
                }

                h_flow = next_h_flow;
                continue;
            }

            // --- STANDARD CELL PROCESSING ---

            // Iterate over BR (The new point P(r, c))
            for (int br = 0; br < 4; br++) {
                long long p_br = INV4;

                // --- 1. Process Vertical Input (dp_u) ---
                // We sum over possible TR types
                for (int tr = 0; tr < 4; tr++) {
                    long long flow = dp_u[c][tr];
                    if (flow == 0) continue;

                    // V-Flow treats BL as Uniform (1/4 for each type)

                    // A. Probability of Moving Down
                    // Requires: BL != R AND BR != L
                    long long p_down = 0;
                    if (br != LEFT) {
                        // If BR ok, prob depends on BL != R (3/4)
                        p_down = (3 * INV4) % MOD;
                    }

                    // B. Probability of Moving Right
                    // Requires: Blocked Down AND Right Open
                    // Right Open depends on TR and BR
                    // Right Open: TR != D AND BR != U
                    bool right_open_possible = (tr != DOWN && br != UP);

                    long long p_right = 0;
                    if (right_open_possible) {
                        // Prob Right = P(Blocked Down) * 1
                        // P(Blocked Down) = 1 - p_down
                        long long p_blocked_down = (1 + MOD - p_down) % MOD;
                        p_right = p_blocked_down;
                    }

                    // C. Stop
                    long long p_stop =
                        (1 + MOD - p_down - p_right + 2 * MOD) % MOD;

                    // Update States
                    // Stop
                    long long term = (flow * p_br) % MOD;
                    total_valid_prob = (total_valid_prob + term * p_stop) % MOD;

                    // Down -> next_dp_u[c][br]
                    next_dp_u[c][br] = (next_dp_u[c][br] + term * p_down) % MOD;

                    // Right -> next_h_flow[br]
                    next_h_flow[br] = (next_h_flow[br] + term * p_right) % MOD;
                }

                // --- 2. Process Horizontal Input (h_flow) ---
                // We sum over possible BL types
                for (int bl = 0; bl < 4; bl++) {
                    long long flow = h_flow[bl];
                    if (flow == 0) continue;

                    // H-Flow treats TR as Uniform (1/4 for each type)

                    // A. Probability of Moving Down
                    // Requires: BL != R AND BR != L
                    // Here BL is FIXED (from loop), BR is FIXED (from loop)
                    long long p_down = 0;
                    if (bl != RIGHT && br != LEFT) {
                        p_down = 1;
                    }

                    // B. Probability of Moving Right
                    // Requires: Blocked Down AND Right Open
                    // Blocked Down: Not (BL!=R and BR!=L) -> (BL==R or BR==L)
                    // Right Open: TR != D and BR != U
                    // We treat TR as Uniform -> P(TR != D) = 3/4
                    long long p_right = 0;

                    // Check blocked down first (Deterministic)
                    bool blocked_down = (bl == RIGHT || br == LEFT);

                    if (blocked_down && br != UP) {
                        // If blocked down and BR allows right, we need TR != D
                        // (3/4 chance)
                        p_right = (3 * INV4) % MOD;
                    }

                    // C. Stop
                    long long p_stop =
                        (1 + MOD - p_down - p_right + 2 * MOD) % MOD;

                    // Update States
                    long long term = (flow * p_br) % MOD;
                    total_valid_prob = (total_valid_prob + term * p_stop) % MOD;

                    // Down
                    next_dp_u[c][br] = (next_dp_u[c][br] + term * p_down) % MOD;

                    // Right
                    next_h_flow[br] = (next_h_flow[br] + term * p_right) % MOD;
                }
            }

            // Move next_h_flow to h_flow for next column iteration
            h_flow = next_h_flow;
        }

        // Move next_dp_u to dp_u for next row iteration
        dp_u = next_dp_u;
    }

    // Final Scaling
    // We computed weighted probability assuming every point is chosen 1/4.
    // Result needs to be multiplied by Total Combinations 4^((N+1)(M+1))
    long long total_points = (long long)(N + 1) * (M + 1);
    long long total_combinations = power(4, total_points);
    long long ans = (total_valid_prob * total_combinations) % MOD;

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    INV4 = modInverse(4);
    INV16 = modInverse(16);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}