using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *virHead = new ListNode(-1, head);
        ListNode *right = virHead;
        ListNode *left = virHead;
        for (int i = 0; i <= n; i++) {
            right = right->next;
        }
        while (right != nullptr) {
            left = left->next;
            right = right->next;
        }
        ListNode *del = left->next;
        left->next = left->next->next;
        delete del;
        head = virHead->next;
        delete virHead;
        return head;
    }
};