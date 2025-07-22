#include <iostream>
#include <numeric>
#include <vector>

// Define the modulus for calculations
const long long MOD = 998244353;

// --- Modular Arithmetic Utilities ---

// Computes (base^exp) % MOD using binary exponentiation
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Computes the modular multiplicative inverse of n modulo MOD
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// --- Precomputation and Combinatorics ---

// Vectors to store precomputed factorials and their inverses
std::vector<long long> fact;
std::vector<long long> invFact;

// Precomputes factorials up to a given limit 'n'
void precompute_factorials(int n) {
    fact.resize(n + 1);
    invFact.resize(n + 1);
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
        // Inverse of fact[i] can be computed from invFact[i-1]
        // but using modInverse is safe and fast enough here.
    }
    invFact[n] = modInverse(fact[n]);
    for (int i = n - 1; i >= 1; --i) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// Calculates nCr (combinations) modulo a prime
long long nCr_mod_p(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }
    return (((fact[n] * invFact[r]) % MOD) * invFact[n - r]) % MOD;
}

// Calculates the n-th Catalan number
long long catalan(int n) {
    if (n < 0) {
        return 0;
    }
    // C_n = (1/(n+1)) * (2n C n)
    long long combinations = nCr_mod_p(2 * n, n);
    long long inv_n_plus_1 = modInverse(n + 1);
    return (combinations * inv_n_plus_1) % MOD;
}

// --- Main Logic ---

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    // We need Catalan numbers up to C_{N-2}, which requires factorials up to 2*(N-2).
    // Precomputing up to 2*N is safe.
    precompute_factorials(2 * N);

    std::vector<long long> ans(N);  // ans[d] stores the result for distance d

    // Case d=1 and d=2
    long long c_n_minus_2 = catalan(N - 2);
    if (1 < N)
        ans[1] = c_n_minus_2;
    if (2 < N)
        ans[2] = c_n_minus_2;

    // Cases for d > 2
    for (int d = 3; d < N; ++d) {
        int catalan_index;
        if (d % 2 != 0) {  // d is odd
            catalan_index = N - (d + 3) / 2;
        } else {  // d is even
            catalan_index = N - (d + 2) / 2;
        }
        ans[d] = catalan(catalan_index);
    }

    // Print results for d = 1 to N-1
    for (int d = 1; d < N; ++d) {
        std::cout << ans[d] << (d == N - 1 ? "" : "\n");
    }
    std::cout << std::endl;

    return 0;
}