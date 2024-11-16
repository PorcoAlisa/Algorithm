#include <string>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        string window;
        int left = 0;
        int right = 0;
        while (right < s.size()) {
            char c = s[right];
            right++;
            window += c;
        }
    }
};