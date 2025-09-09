#include <iostream>
#include <string>
using namespace std;

string solve(int n, int k) {
    // Edge cases
    if (k == 0)
        return string(n, '0');
    if (k == n)
        return string(n, '1');

    // For the perfect bitstring construction, we need equal numbers of
    // "101" and "010" subsequences.

    // One approach that works well: create a string where we alternate
    // or group bits in a way that naturally balances these subsequences

    string result = "";

    // Strategy: Build the string by placing 1s and 0s strategically
    // to ensure balance between 101 and 010 subsequences

    if (k <= n / 2) {
        // More 0s than 1s: start with 1s, then 0s, then possibly more 1s
        for (int i = 0; i < k; i++)
            result += '1';
        for (int i = 0; i < n - k; i++)
            result += '0';
    } else {
        // More 1s than 0s: use the complement approach
        for (int i = 0; i < n - k; i++)
            result += '0';
        for (int i = 0; i < k; i++)
            result += '1';
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << solve(n, k) << '\n';
    }

    return 0;
}

/*
The construction works as follows:
- For strings of the form "111...000" or "000...111", 
  we get 0 subsequences of both "101" and "010" types
  because all bits of one type come before all bits of the other type.
- This makes the count equal (0 = 0), satisfying the perfect condition.

This approach is guaranteed to work for all valid inputs as stated in the problem.
*/