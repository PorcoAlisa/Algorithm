#include <unordered_map>
using namespace std;

class DoubleLinkedNode {
public:
    DoubleLinkedNode *last_ = nullptr;
    DoubleLinkedNode *next_ = nullptr;
    int key_;
    DoubleLinkedNode(int key):key_(key) {}
};

class DoubleLinkedList {
private:
    DoubleLinkedNode *head_;
    DoubleLinkedNode *tail_;
public:
    ~DoubleLinkedList() {
        while (head_ != nullptr) {
            DoubleLinkedNode *node = head_;
            head_ = head_->next_;
            delete node;
        }
    }

    int Front() {
        if (head_ != nullptr) {
            return head_->key_;
        }
        return 0;
    }

    void Push_back(DoubleLinkedNode *node) {
        if (tail_ == nullptr) {
            tail_ = node;
            head_ = tail_;
        } else {
            tail_->next_ = node;
            node->last_ = tail_;
            node->next_ = nullptr;
            tail_ = node;
        }
    }

    void Erase(DoubleLinkedNode *node) {
        if (node == nullptr) {
            return;
        }
        DoubleLinkedNode *lastNode = node->last_;
        DoubleLinkedNode *nextNode = node->next_;

        if (lastNode == nullptr) { /* 说明node就是head */
            head_ = nextNode;
        } else {
            lastNode->next_ = nextNode;
        }

        if (nextNode == nullptr) { /* 说明node就是tail */
            tail_ = lastNode;
        } else {
            nextNode->last_ = lastNode;
        }

        delete node;
    }
};

class OrderedHashSet {
private:
    /* <key, address of the key in keyList_> */
    unordered_map<int, DoubleLinkedNode *> keyMap_;
    DoubleLinkedList keyList_;
public:
    void Insert(int key) {
        DoubleLinkedNode *node = new DoubleLinkedNode(key);
        keyList_.Push_back(node);
        keyMap_[key] = node;
    }

    void Erase(int key) {
        if (keyMap_.find(key) == keyMap_.end()) { /* 如果找不到，说明key不存在，没有继续执行erase的必要 */
            return;
        }
        keyList_.Erase(keyMap_[key]);
        keyMap_.erase(key);
    }

    int Size() {
        return keyMap_.size();
    }

    int Front() {
        return keyList_.Front();
    }
};

class LFUCache {
private:
    unordered_map<int, int> kvMap_; /* key to value */
    unordered_map<int, int> kfMap_; /* key to freq */
    unordered_map<int, OrderedHashSet> freqToHashKeyMap_; /* freq to key */
    int maxCapacity_;
    int minFreq_ = 0;
public:
    LFUCache(int capacity):maxCapacity_(capacity) {

    }
    
    int get(int key) {
        if (kvMap_.find(key) == kvMap_.end()) {
            return -1;
        }
        int value = kvMap_[key];
        UpdateKeyFreqInVisit(key);
        return value;
    }
    
    void put(int key, int value) {
        if (kvMap_.find(key) == kvMap_.end()) {
            if (kvMap_.size() >= maxCapacity_) {
                /* 移除最不经常使用的一项 */
                int delKey = freqToHashKeyMap_[minFreq_].Front();
                FreqToHashKeyMapErase(minFreq_, delKey);
                kfMap_.erase(delKey);
                kvMap_.erase(delKey);
            }
            kfMap_[key] = 1;
            minFreq_ = 1;
            FKMapInsert(1, key);
        } else {
            UpdateKeyFreqInVisit(key);
        }
        kvMap_[key] = value;
    }

    void UpdateKeyFreqInVisit(int key) {
        int freq = kfMap_[key];
        FreqToHashKeyMapErase(freq, key);
        FKMapInsert(freq + 1, key);
        kfMap_[key]++;
    }

    void FreqToHashKeyMapErase(int freq, int key) {
        freqToHashKeyMap_[freq].Erase(key);
        if (freqToHashKeyMap_[freq].Size() == 0) {
            freqToHashKeyMap_.erase(freq);
/* minFreq_的变化分为两种情况：
一种是读了数据或者更新了数据，导致freq++，这时候，如果当前freq是minfreq，只需要minfreq++，因为freq将变为freq+1；
一种是插入数据时，纯粹地删掉minfreq的头部节点元素，这时候，如果minfreq的链表为空，minfreq将移动到下一个freq，而下一个freq并不一定是freq + 1
而到底下一个freq是多少，并不知道，但由于这时候，插入了一个新的元素，所以下一个freq是谁并不重要，因为minfreq将必然变为1 */
            if (freq == minFreq_) {
                minFreq_++;
            }
        }
    }

    void FKMapInsert(int freq, int key) {
        freqToHashKeyMap_[freq].Insert(key);
    }
};

int main(int argc, char *argv[])
{
    return 0;
}