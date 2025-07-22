#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_base_palindrome(int64_t num, int base) {
    vector<int> digits;
    while (num > 0) {
        digits.push_back(num % base);
        num /= base;
    }
    for (size_t i = 0, j = digits.size() - 1; i < j; ++i, --j) {
        if (digits[i] != digits[j])
            return false;
    }
    return true;
}

int64_t int_pow10(int exp) {
    int64_t res = 1;
    while (exp--)
        res *= 10;
    return res;
}

int64_t solve(int base, int64_t N) {
    int64_t sum = 0;

    for (int len = 1; len <= 12; ++len) {
        int half_len = (len + 1) / 2;
        int64_t start = (len == 1) ? 1 : int_pow10(half_len - 1);
        int64_t end = int_pow10(half_len);

        for (int64_t half = start; half < end; ++half) {
            string half_str = to_string(half);
            string full_str = half_str;

            if (len % 2 == 1)
                full_str += string(half_str.rbegin() + 1, half_str.rend());
            else
                full_str += string(half_str.rbegin(), half_str.rend());

            int64_t pal = stoll(full_str);
            if (pal > N)
                break;

            if (is_base_palindrome(pal, base)) {
                sum += pal;
            }
        }
    }

    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A;
    int64_t N;
    cin >> A >> N;
    cout << solve(A, N) << '\n';
    return 0;
}
