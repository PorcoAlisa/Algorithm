
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

typedef enum {
    FALSE_FALSE = 0,
    TRUE_FALSE = 1,
    TRUE_TRUE = 2,
} STATUS;

class Solution {
public:
int cnt_;
    int Traversal(TreeNode* node) {
        if (node == nullptr) {
            return TRUE_FALSE;
        }

        int leftStatus = Traversal(node->left);
        int rightStatus = Traversal(node->right);
        int minStatus = leftStatus < rightStatus ? leftStatus : rightStatus;
        int maxStatus = leftStatus > rightStatus ? leftStatus : rightStatus;

        if (minStatus == FALSE_FALSE) {
            cnt_++;
            return TRUE_TRUE;
        }
        if (maxStatus == TRUE_FALSE) {
            return FALSE_FALSE;
        }
        return TRUE_FALSE;
    }

    int minCameraCover(TreeNode* root) {
        cnt_ = 0;
        int status = Traversal(root);
        if (status == FALSE_FALSE) {
            cnt_++;
        }
        return cnt_;
    }
};