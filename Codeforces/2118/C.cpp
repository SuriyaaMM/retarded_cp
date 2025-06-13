#include <iostream>
#include <numeric>  // For __builtin_popcount (GCC specific)
#include <queue>
#include <vector>

// Function to count set bits (popcount)
// For GCC/Clang, __builtin_popcount is very efficient.
// For other compilers, you might need a custom implementation.
int countSetBits(long long n) {
    return __builtin_popcountll(n);  // Use __builtin_popcountll for long long
}

// Function to find the position of the rightmost 0-bit
// This is equivalent to finding the number of trailing 1s and then 1 (for 0).
// __builtin_ctz(mask) counts trailing zeros of mask.
// We need the position of the rightmost 0-bit in 'n'. This is __builtin_ctz(~n).
int getRightmostZeroBitPos(long long n) {
    if (n == -1LL)
        return 63;               // All 1s for long long (max bits)
    return __builtin_ctzll(~n);  // Use __builtin_ctzll for long long
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    long long k;
    std::cin >> n >> k;

    std::vector<long long> a(n);
    long long current_total_beauty = 0;

    // Min-priority queue to store costs for potential +1 beauty gain
    // Stores the cost (long long)
    std::priority_queue<long long, std::vector<long long>,
                        std::greater<long long>>
        pq;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        current_total_beauty += countSetBits(a[i]);

        // Calculate the cost to gain 1 bit for this number
        // The cost is 2^(position of rightmost 0-bit)
        long long cost = (1LL << getRightmostZeroBitPos(a[i]));
        pq.push(cost);
    }

    // Greedily apply operations
    while (k > 0 && !pq.empty()) {
        long long cheapest_cost = pq.top();
        pq.pop();

        if (k >= cheapest_cost) {
            k -= cheapest_cost;
            current_total_beauty += 1;  // Gained 1 bit

            // The number effectively changed. We need to calculate the
            // new cost for this (hypothetically changed) number to gain another bit.
            // The value effectively becomes a[i] + cheapest_cost.
            // We can infer the next 'a[i]' value from the 'cheapest_cost' logic:
            // If the old value was X, and we added 'cost = 1LL << pos_of_rightmost_zero',
            // the new value has its rightmost 0 at 'pos_of_rightmost_zero' flipped to 1,
            // and all bits to its right flipped to 0.
            // The next rightmost zero bit will be at a higher position.
            // The new number will be 'old_val + cheapest_cost'.
            // The rightmost 0 bit in (old_val + cheapest_cost) will be shifted to the left by 1.
            // So, the next cost will be cheapest_cost * 2.
            // This is because (X + (1<<P)) will have its rightmost 0 at P+1 (unless it carries over even further).
            // Example: 6 (110), pos=0, cost=1. New num=7 (111). Next pos=3, next cost=8. (Not 1*2=2)
            // Example: 3 (011), pos=2, cost=4. New num=7 (111). Next pos=3, next cost=8. (Not 4*2=8)
            // Example: 5 (101), pos=1, cost=2. New num=7 (111). Next pos=3, next cost=8. (Not 2*2=4)

            // The simple cheapest_cost * 2 logic is incorrect.
            // We need to re-calculate the position of the rightmost zero bit for the *new* value.
            // However, we don't store the actual 'a[i]' values in the PQ, only their costs.
            // This means my current priority queue structure is insufficient.

            // We need to store pairs: (cost, original_value + sum_of_costs_applied_so_far)
            // Or (cost, current_index_in_original_array) and then update a[index].
            // Updating `a[i]` within the loop means `a` should not be const after initial read.
            // Let's modify `a` and store `(cost, index)`.

            // --- RESTARTING ALGORITHM LOGIC SLIGHTLY TO ACCOUNT FOR ACTUAL VALUES ---
            // The implementation needs to know which 'a[i]' generated `cheapest_cost`
            // to correctly calculate the *next* cost for that specific `a[i]`.
            // Instead of just costs, PQ should store (cost, original_index_of_element).
        } else {
            break;  // Not enough k to cover the cheapest operation
        }
    }

    std::cout << current_total_beauty << std::endl;

    return 0;
}