#include <vector>
using namespace std;



// class Solution
// {
// public:
//     vector<int> RightElement() {
//         queue<int> que;

//         que.push(root);
//         vector<int> ans;
//         while (que.size() > 0) {
//             int size = que.size();
//             TreeNode *node;
//             for (int i = 0; i < size; i++) {
//                 node = que.front();
//                 que.pop();
//                 if (node->left != nullptr)
//                     que.push(node->left);
//                 if (node->right != nullptr) 
//                     que.push(node->right);
//             }
//             ans.push_back(node->val);
//         }
//         return ans;
//     }
// };


