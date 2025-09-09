// #include <cstddef>
// #include <deque>
// #include <iostream>
// #include <vector>

// int main(int, char**) {

//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     size_t n = 0UL;
//     std::cin >> n;
//     std::vector<size_t> a(n);

//     for (size_t i = 0; i < n; ++i) {
//         std::cin >> a[i];
//     }

//     std::vector<size_t> kth_sums(n);

//     // solution
//     for (size_t k = 1; k <= n; ++k) {

//         std::deque<size_t> monotonic_decreasing_deque = {};

//         // construct a sliding window and iterare through it
//         size_t kth_sum = 0UL;
//         for (size_t i = 0; i < n; ++i) {

//             // clear all the elements out of this window in the deque
//             while (!monotonic_decreasing_deque.empty() &&
//                    monotonic_decreasing_deque.front() <= (i - k)) {
//                 monotonic_decreasing_deque.pop_front();
//             }

//             // remove all the elements in the deque that are less than the current element
//             // those removed elements can never become maximum
//             while (!monotonic_decreasing_deque.empty() &&
//                    a[monotonic_decreasing_deque.back()] <= a[i]) {

//                 monotonic_decreasing_deque.pop_back();
//             }

//             monotonic_decreasing_deque.emplace_back(i);

//             // if we reach the end of this window
//             if (i >= k - 1)
//                 // front element of the deque will be the maximum
//                 kth_sum += a[monotonic_decreasing_deque.front()];
//         }

//         kth_sums[k - 1] = kth_sum;
//     }

//     for (size_t& kth_sum : kth_sums) {
//         std::cout << kth_sum << std::endl;
//     }

//     return 0;
// }

#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

void explain_on_approach() {
    cout << "=== O(N) APPROACH DETAILED EXPLANATION ===" << endl;

    // Example: [5, 3, 4, 2] (1-indexed: a[1]=5, a[2]=3, a[3]=4, a[4]=2)
    vector<int> a = {0, 5, 3, 4, 2};  // 0-th index unused
    int n = 4;

    cout << "Input array: [5, 3, 4, 2]" << endl << endl;

    // STEP 1: Find left and right boundaries for each element
    cout << "STEP 1: Find boundaries where each element is maximum" << endl;
    cout << "For each element, find nearest greater elements on left and right"
         << endl
         << endl;

    vector<int> L(n + 1), R(n + 1);
    stack<int> st;

    // Left boundaries: nearest greater element on left
    cout << "Finding left boundaries (L[i]):" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Processing a[" << i << "] = " << a[i] << endl;

        // Remove elements smaller than current
        while (!st.empty() && a[st.top()] < a[i]) {
            cout << "  Removing " << a[st.top()] << " (smaller than " << a[i]
                 << ")" << endl;
            st.pop();
        }

        if (!st.empty()) {
            L[i] = st.top();
            cout << "  L[" << i << "] = " << L[i]
                 << " (nearest greater on left)" << endl;
        } else {
            L[i] = 0;
            cout << "  L[" << i << "] = 0 (no greater element on left)" << endl;
        }
        st.push(i);
        cout << "  Stack now: ";
        stack<int> temp = st;
        vector<int> stack_contents;
        while (!temp.empty()) {
            stack_contents.push_back(temp.top());
            temp.pop();
        }
        reverse(stack_contents.begin(), stack_contents.end());
        for (int x : stack_contents)
            cout << x << " ";
        cout << endl << endl;
    }

    // Clear stack
    while (!st.empty())
        st.pop();

    // Right boundaries: nearest greater element on right
    cout << "Finding right boundaries (R[i]):" << endl;
    for (int i = n; i >= 1; i--) {
        cout << "Processing a[" << i << "] = " << a[i] << endl;

        // Remove elements smaller or equal than current
        while (!st.empty() && a[st.top()] <= a[i]) {
            cout << "  Removing " << a[st.top()] << " (smaller/equal than "
                 << a[i] << ")" << endl;
            st.pop();
        }

        if (!st.empty()) {
            R[i] = st.top();
            cout << "  R[" << i << "] = " << R[i]
                 << " (nearest greater on right)" << endl;
        } else {
            R[i] = n + 1;
            cout << "  R[" << i << "] = " << n + 1
                 << " (no greater element on right)" << endl;
        }
        st.push(i);
        cout << endl;
    }

    cout << "\nBoundary Summary:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "a[" << i << "] = " << a[i] << ", L[" << i << "] = " << L[i]
             << ", R[" << i << "] = " << R[i] << endl;
        cout << "  → a[" << i << "] is maximum in range (" << L[i] << ", "
             << R[i] << ")" << endl;
    }

    // STEP 2: Calculate contribution of each element
    cout << "\nSTEP 2: Calculate how each element contributes to different k "
            "values"
         << endl;

    for (int i = 1; i <= n; i++) {
        int l =
            i -
            L[i];  // positions where element can be leftmost in its "dominance range"
        int r =
            R[i] -
            i;  // positions where element can be rightmost in its "dominance range"

        cout << "\nElement a[" << i << "] = " << a[i] << ":" << endl;
        cout << "  Can be leftmost maximum in " << l << " positions" << endl;
        cout << "  Can be rightmost maximum in " << r << " positions" << endl;
        cout << "  Total subarrays where it's maximum: " << l * r << endl;

        // Show which subarrays contain this element as maximum
        cout << "  Subarrays where a[" << i << "] is maximum:" << endl;
        for (int start = L[i] + 1; start <= i; start++) {
            for (int end = i; end < R[i]; end++) {
                if (end - start + 1 <= n) {
                    cout << "    [" << start << ".." << end << "] (length "
                         << end - start + 1 << ")" << endl;
                }
            }
        }

        // Calculate contribution to each k
        cout << "  Contribution to each k:" << endl;
        for (int k = 1; k <= n; k++) {
            int count = 0;
            // Count subarrays of length k where this element is maximum
            for (int start = max(1, max(L[i] + 1, i - k + 1));
                 start <= min(i, n - k + 1); start++) {
                int end = start + k - 1;
                if (end < R[i] && end >= i) {
                    count++;
                }
            }
            if (count > 0) {
                cout << "    k=" << k << ": appears in " << count
                     << " subarrays, contributes " << count * a[i] << endl;
            }
        }
    }

    // STEP 3: Use difference array technique for efficient summation
    cout << "\nSTEP 3: Difference Array Technique" << endl;
    cout
        << "Instead of calculating each k separately, use mathematical formula:"
        << endl;

    vector<long long> ans2(n + 2, 0), ans1(n + 2, 0), ans(n + 2, 0);

    for (int i = 1; i <= n; i++) {
        int l = i - L[i];
        int r = R[i] - i;

        cout << "\nFor a[" << i << "] = " << a[i] << " (l=" << l << ", r=" << r
             << "):" << endl;

        // This is the key insight: mathematical formula for contribution
        cout << "  Adding " << a[i] << " to ans2[1]" << endl;
        cout << "  Subtracting " << a[i] << " from ans2[" << l + 1 << "]"
             << endl;
        cout << "  Subtracting " << a[i] << " from ans2[" << r + 1 << "]"
             << endl;
        cout << "  Adding " << a[i] << " to ans2[" << l + r + 1 << "]" << endl;

        ans2[1] += a[i];
        ans2[l + 1] -= a[i];
        ans2[r + 1] -= a[i];
        ans2[l + r + 1] += a[i];
    }

    cout << "\nDifference array ans2: ";
    for (int i = 1; i <= n + 1; i++) {
        cout << ans2[i] << " ";
    }
    cout << endl;

    // Convert difference array to actual values
    cout << "\nConverting to final answers:" << endl;
    for (int i = 1; i <= n; i++) {
        ans1[i] = ans1[i - 1] + ans2[i];
        ans[i] = ans[i - 1] + ans1[i];
        cout << "k=" << i << ": ans[" << i << "] = " << ans[i] << endl;
    }
}

int main() {

    explain_on_approach();
    return 0;
}