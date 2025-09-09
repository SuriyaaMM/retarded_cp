#include <cmath>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

long long count_distinct_lcm(long long L, long long R) {
    if (L == R) {
        return 1;
    }

    std::set<long long> prime_powers_in_range;

    long long limit = sqrt(R);
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long p = 2; p * p <= limit; ++p) {
        if (is_prime[p]) {
            for (long long i = p * p; i <= limit; i += p)
                is_prime[i] = false;
        }
    }

    std::vector<long long> primes;
    for (long long p = 2; p <= limit; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
        }
    }

    long long start_num = L + 1;
    if (start_num > R) {
        return 1;
    }

    std::vector<bool> is_composite(R - start_num + 1, false);
    for (long long p : primes) {
        long long start_idx = (start_num + p - 1) / p;
        long long start = std::max(start_idx, p) * p;
        for (long long j = start; j <= R; j += p) {
            if (j >= start_num) {
                is_composite[j - start_num] = true;
            }
        }
    }

    for (long long i = 0; i < is_composite.size(); ++i) {
        if (!is_composite[i]) {
            long long current_num = start_num + i;
            if (current_num > 1) {
                prime_powers_in_range.insert(current_num);
            }
        }
    }

    for (long long p : primes) {
        long long power = p;

        if (R / p < power) {
            continue;
        }
        power *= p;

        while (power <= R) {
            if (power >= start_num) {
                prime_powers_in_range.insert(power);
            }
            if (R / p < power) {
                break;
            }
            power *= p;
        }
    }

    return 1 + prime_powers_in_range.size();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    long long L, R;
    std::cin >> L >> R;
    std::cout << count_distinct_lcm(L, R) << std::endl;
    return 0;
}