using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* Solution 1
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode *virHead = new ListNode(0, head);
        ListNode *lowTail = virHead;
        ListNode *highHead = nullptr;
        ListNode *highTail = nullptr;
        while (lowTail->next != nullptr) {
            while (lowTail->next != nullptr && lowTail->next->val < x) {
                lowTail = lowTail->next;
            }
            if (highTail != nullptr) {
                highTail->next = lowTail->next;
                highTail = highTail->next;
            }
            if (highHead == nullptr) {
                highHead = lowTail->next;
                highTail = highHead;
            }
            while (highTail != nullptr && highTail->next != nullptr && highTail->next->val >= x) {
                highTail = highTail->next;
            }
            if (highTail == nullptr || highTail->next == nullptr) {
                break;
            }
            lowTail->next = highTail->next;
            lowTail = lowTail->next;
        }
        lowTail->next = highHead;
        if (highTail != nullptr) {
            highTail->next = nullptr;
        }
        ListNode *ans = virHead->next;
        delete virHead;
        return ans;
    }
}; */

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *dummy1 = new ListNode(-1, nullptr);
        ListNode *dummy2 = new ListNode(-1, nullptr);

        ListNode *p1 = dummy1;
        ListNode *p2 = dummy2;

        ListNode *cur = head;
        while (cur != nullptr) {
            if (cur->val < x) {
                p1->next = cur;
                p1 = p1->next;
            } else {
                p2->next = cur;
                p2 = p2->next;
            }
            cur = cur->next;
        }
        p1->next = dummy2->next;
        p2->next = nullptr;

        head = dummy1->next;

        delete dummy1;
        delete dummy2;

        return head;
    }
};

int main()
{
    ListNode n1(2);
    ListNode n2(5, &n1);
    ListNode n3(2, &n2);
    ListNode n4(3, &n3);
    ListNode n5(4, &n4);
    ListNode n6(1, &n5);

    Solution s1;
    s1.partition(&n6, 3);
}