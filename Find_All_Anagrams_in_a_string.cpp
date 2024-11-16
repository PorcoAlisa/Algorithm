#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> alphaTable(26, 0);
        int num = 0;
        for (auto &c : p) {
            alphaTable[c - 'a']++;
            num++;
        }

        int left = 0;
        int right = 0;
        vector<int> ans;
        while (right < s.size()) {
            if (alphaTable[s[right] - 'a'] > 0) {
                alphaTable[s[right] - 'a']--;
                num--;
                if (num == 0) {
                    ans.push_back(left);
                    alphaTable[s[left] - 'a']++;
                    num++;
                    left++;
                }
                right++;
            } else {
                if (left == right) {
                    right++;
                } else {
                    alphaTable[s[left] - 'a']++;
                    num++;
                }
                left++;
            }
        }
        return ans;
    }
};

int main(int argc, char *argv[])
{
    Solution s1;
    vector<int> ans = s1.findAnagrams("cbaebabacd", "abc");
}