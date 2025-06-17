#include <cstdint>
#include <iostream>
#include <vector>

void solve() {
    size_t n;
    std::cin >> n;

    std::vector<int64_t> w(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> w[i];
    }

    size_t bob_ptr = 0;
    size_t alice_ptr = n - 1;

    int64_t current_bob_sum = 0;
    int64_t current_alice_sum = 0;

    int64_t max_total_candies_eaten = 0;

    while (bob_ptr <= alice_ptr) {
        if (current_bob_sum < current_alice_sum) {
            current_bob_sum += w[bob_ptr];
            bob_ptr++;
        } else if (current_alice_sum < current_bob_sum) {
            current_alice_sum += w[alice_ptr];
            alice_ptr--;
        } else {

            max_total_candies_eaten = bob_ptr + (n - 1 - alice_ptr);

            current_bob_sum += w[bob_ptr];
            bob_ptr++;

            if (bob_ptr <= alice_ptr) {
                current_alice_sum += w[alice_ptr];
                alice_ptr--;
            }
        }
    }

    if (current_bob_sum == current_alice_sum) {
        max_total_candies_eaten = bob_ptr + (n - 1 - alice_ptr);
    }

    std::cout << max_total_candies_eaten << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}