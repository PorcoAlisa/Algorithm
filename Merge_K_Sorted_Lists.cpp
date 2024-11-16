#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct Greater
{
    bool operator()(const ListNode* x, const ListNode* y) const {
        return x->val > y->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *virHead = new ListNode(-1, nullptr);
        priority_queue<ListNode*, vector<ListNode*>, Greater> q; /* 构建了一个小顶堆 */
        for (auto &list : lists) {
            if (list != nullptr) {
                q.push(list);
            }
        }
        ListNode *cur;
        ListNode *tail = virHead;
        while (q.size() > 0) {
            cur = q.top();
            q.pop();
            while (cur != nullptr && cur->val <= q.top()->val) {
                tail->next = cur;
                tail = cur;
                cur = cur->next;
            }
            if (cur != nullptr) {
                q.push(cur);
            }
        }
        ListNode *head = virHead->next;
        delete virHead;
        return head;
    }
};