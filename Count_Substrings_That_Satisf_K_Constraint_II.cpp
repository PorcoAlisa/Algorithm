#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> count(2, 0);
        vector<int> right(n, n); /* 当i到某个点时，后续的右边界都是s.size() */
        /* prefix[i]的含义是：以s[0]..s[i]结尾的符合k约束的子字符串数量，例如prefix[1]表示，以s[0]、s[1]结尾的所有子字符串中，符合k约束的字符串数量 */
        vector<long long> prefix(n + 1, 0); /* n + 1, 因为第一位要保持为0 */
        /* i代表左端点，j代表右端点，j是刚好不符合K约束的右边界 */ 
        int i = 0;
        for (int j = 0; j < n; j++) {
            count[s[j] - '0']++;
            /* 这里需要循环，因为有可能在上一个j的时候，0和1的数量符合k约束，j++之后，多了一个1，不符合k约束，而i++之后，i前进pass掉的字符都是0，即i++，不能保证满足k约束 */
            while (count[0] > k && count[1] > k) {
                count[s[i] - '0']--; /* i即将++，s[i]即将被pass掉，需要更新count */
                right[i] = j;
                i++;
            }
            /* i已经++，保证从s[i]开始到目前的s[j]，所有以s[j]结尾的字符串都是符合k约束的（从s[i - 1]开始则不符合要求），从s[i]至s[j]，以s[j]结尾的子字符串数量为j - i + 1 */
            prefix[j + 1] = prefix[j] + j - i + 1; 
        }

        vector<long long> answer(queries.size(), 0);
        int l, r, R;
        for (int ii = 0; ii < queries.size(); ii++) {
            l = queries[ii][0];
            r = queries[ii][1];
            R = min(right[l], r + 1);
            answer[ii] = 1LL * (R - l) * (R - l + 1) / 2; /* right[l]可能超过r+1 */
            answer[ii] += (prefix[r + 1] - prefix[R]);
        }
        return answer;
    }
};