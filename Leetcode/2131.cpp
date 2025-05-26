#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
   public:
    int longestPalindrome(std::vector<std::string>& words) {

        // hashmap for efficient lookup
        std::unordered_map<std::string, size_t> two_letter_word_map;

        // output variable
        size_t longest_palindrome = 0ULL;
        bool found_center_word = false;

        // iterate through each of two letter characters & add them to map
        for (std::string& two_letter_word : words) {
            ++two_letter_word_map[two_letter_word];
        }

        for (auto it = two_letter_word_map.begin();
             it != two_letter_word_map.end(); ++it) {

            // Process words with same letters (e.g., "gg")
            if (it->first[0] == it->first[1]) {
                // Calculate pairs: (count / 2) groups of two words, each contributing 4 to length
                longest_palindrome += (it->second / 2) * 4;

                // If there's an odd count, it means one word can be the center
                if (it->second % 2 == 1) {
                    found_center_word = true;
                }
            }
            // Process words with different letters (e.g., "ab")
            else {
                // Create the reversed string
                std::string reversed_string = it->first;
                std::reverse(reversed_string.begin(), reversed_string.end());

                auto it2 = two_letter_word_map.find(reversed_string);

                // If we find this string's reverse counterpart
                if (it2 != two_letter_word_map.end()) {
                    // Determine how many pairs we can form (minimum of current word's count and its reverse's count)
                    size_t min_pairs = std::min(it->second, it2->second);

                    // Each pair contributes 4 to the palindrome length (e.g., "ab" + "ba" -> "abba")
                    longest_palindrome += min_pairs * 4;

                    // Consume the words by reducing their counts in the map
                    it->second -= min_pairs;
                    it2->second -= min_pairs;
                }
            }
        }

        if (found_center_word) {
            longest_palindrome += 2;
        }

        return longest_palindrome;
    }
};

int main(int, char**) {
    Solution solution = {};
    std::vector<std::string> words = {"lc", "cl", "gg"};
    std::cout << solution.longestPalindrome(words) << std::endl;  // Expected: 6

    std::vector<std::string> words2 = {"ab", "ty", "yt", "lc", "cl", "ab"};
    std::cout << "Test 2: " << solution.longestPalindrome(words2)
              << std::endl;  // Expected: 8

    std::vector<std::string> words3 = {"gg", "gg", "gg"};
    std::cout << "Test 3: " << solution.longestPalindrome(words3)
              << std::endl;  // Expected: 6

    std::vector<std::string> words4 = {"em", "pe", "mp", "em", "me", "me"};
    std::cout << "Test 4: " << solution.longestPalindrome(words4)
              << std::endl;  // Expected: 10

    std::vector<std::string> words5 = {"gg", "bb"};
    std::cout << "Test 5: " << solution.longestPalindrome(words5)
              << std::endl;  // Expected: 2

    std::vector<std::string> words6 = {"aa", "aa", "aa", "aa", "aa",
                                       "aa", "aa", "aa", "aa", "aa"};
    std::cout << "Test 6: " << solution.longestPalindrome(words6)
              << std::endl;  // Expected: 20

    std::vector<std::string> words7 = {"ab", "ty", "yt", "lc",
                                       "cl", "ab", "ba"};
    std::cout << "Test 7: " << solution.longestPalindrome(words7)
              << std::endl;  // Expected: 12

    std::vector<std::string> words8 = {"aa", "aa", "bb", "bb", "cc"};
    std::cout << "Test 8: " << solution.longestPalindrome(words8)
              << std::endl;  // Expected: 10 (your previous test case)
    return 0;
}
