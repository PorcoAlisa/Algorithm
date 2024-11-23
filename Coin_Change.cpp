#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

/* 这个解法是错误的，我本来以为面值越大的硬币使用的数量越多，那么最终结果一定是越小的，
但实际上不一定是这样，比如硬币面额为 2,4,8,9，实际上这里用2个9和2,4是可以得到24的，但
是实际上3个8得到24使用的硬币数量才是最少的 */

/*
改过之后，代码能跑过了，但是耗时太长
*/

/*
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, 0));
        for (int i = 0; i <= coins.size(); i++) {
            dp[i][0] = 0;
        }
        for (int j = 1; j <= amount; j++) {
            dp[0][j] = -1;
        }
        for (int i = 1; i <= coins.size(); i++) {
            for (int j = 1; j <= amount; j++) {
                dp[i][j] = INT_MAX;
                int remainder = j % coins[i - 1];
                for (int k = (j - remainder) / coins[i - 1]; k >= 0; k--) {
                    if (dp[i - 1][j - k * coins[i - 1]] != -1) {
                        dp[i][j] = min(dp[i - 1][j - k * coins[i - 1]] + k, dp[i][j]);
                    }
                }
                if (dp[i][j] == INT_MAX) {
                    dp[i][j] = -1;
                }
            }
        }
        return dp[coins.size()][amount];
    }
};
*/

/* 这种拼命迭代，直接超时，不可取 */

/*
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) {
            return 0;
        }
        if (amount < 0) {
            return -1;
        }
        int ans = INT_MAX;
        for (auto &coin : coins) {
            int tmp = coinChange(coins, amount - coin);
            if (tmp >= 0) {
                ans = min(tmp + 1, ans);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
*/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, -1);
        for (auto & coin : coins) {
            dp[amount] = min(dp[amount], dp[amount - coin]);
        }
    }
};

int main()
{
    Solution s1;
    vector<int> coins = {1,2,5};
    s1.coinChange(coins, 11);
}