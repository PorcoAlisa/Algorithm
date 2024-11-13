#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode *Traversal(int start, int end, vector<int>& nums) {
        if (start < end) {
            return nullptr;
        }
        int i;
        int maxIndex = start;
        for (i = start + 1; i <= end; i++) {
            if (nums[i] > nums[maxIndex]) {
                maxIndex = i;
            }
        }
        TreeNode *node = new TreeNode(nums[maxIndex]);
        node->left = Traversal(start, maxIndex - 1, nums);
        node->right = Traversal(maxIndex + 1, end, nums);
        return node;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return Traversal(0, nums.size() - 1, nums);
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {3,2,1,6,0,5};
    Solution s;
    s.constructMaximumBinaryTree(nums);
}