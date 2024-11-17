#include <vector>
#include <algorithm>
using namespace std;

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
                dp[i][j] = -1;
                int remainder = j % coins[i - 1];
                for (int k = (j - remainder) / coins[i - 1]; k >= 0; k--) {
                    if (dp[i - 1][j - k * coins[i - 1]] != -1) {
                        dp[i][j] = dp[i - 1][j - k * coins[i - 1]] + k;
                        break;
                    }
                }
            }
        }
        return dp[coins.size()][amount];
    }
};

int main()
{
    Solution s1;
    vector<int> coins = {186,419,83,408};
    s1.coinChange(coins, 6249);
}