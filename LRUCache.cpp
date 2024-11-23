#include <unordered_map>
#include <iostream>
using namespace std;

struct DLinkedNode {
    int key;
    int value;
    DLinkedNode *prev;
    DLinkedNode *next;
    DLinkedNode(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    int _capacity;
    int _size;
    unordered_map<int, DLinkedNode *> _map;
    DLinkedNode *virHead; /* 队列的队头，指向最久未使用的元素 */
    DLinkedNode *virTail; /* 队列的队尾，指向最近使用的元素 */
    LRUCache(int capacity) : _capacity(capacity) {
        /* 指定LRUCache的容量大小 */
        virHead = new DLinkedNode(-1, -1);
        virTail = new DLinkedNode(-1, -1);
        virHead->next = virTail;
        virTail->prev = virHead;
    }

    ~LRUCache() {
        /* 释放内存 */
        DLinkedNode *node = virHead;
        while (node != nullptr) {
            DLinkedNode *tmp = node->next;
            delete node;
            node = tmp;
        }
    }

    void updateList(DLinkedNode *target) {
        target->prev->next = target->next;
        target->next->prev = target->prev;
        target->next = virTail;
        target->prev = virTail->prev;
        target->prev->next = target;
        virTail->prev = target;
    }

    void pop() {
        if (_map.size() == 0) { /* 没有元素可以pop */
            return;
        }
        DLinkedNode *needDelNode = virHead->next;
        _map.erase(needDelNode->key);
        virHead->next = virHead->next->next;
        virHead->next->prev = virHead;
        delete needDelNode;
    }

    void push(DLinkedNode *node) {
        node->next = virTail;
        node->prev = virTail->prev;
        node->prev->next = node;
        node->next->prev = node;
    }

    int get(int key) {
        /* 1、通过key，获取指定的value，如未命中则返回-1 */
        auto it = _map.find(key);
        if (it == _map.end()) {
            return -1;
        }
        /* 2、如果命中，由于该数据最近被访问，所以将该数据移动至最近使用数据 */
        DLinkedNode *target = it->second;
        updateList(target);
        return target->value;
    }
    
    void put(int key, int value) {
        /* 1、插入kv数据，如果key已存在，则更新数据 */
        auto it = _map.find(key);
        if (it != _map.end()) {
            it->second->value = value;
            updateList(it->second);
            return;
        }
        /* 2、如果数据不存在，则插入数据；插入数据需要判断当前容量是否已达到LRUCache容量，如果已达到容量，则弹出最久未使用的一条数据，如果尚未达到LRUCache容量，则直接插入数据，并更新当前size */
        if (_map.size() == _capacity) {
            pop();
        }
        DLinkedNode *node = new DLinkedNode(key, value);
        /* 3、由于插入的数据被操作，所以该数据需要放到最近使用数据的位置 */
        _map[key] = node;
        push(node);
    }
};

int main(int argc, char *argv[])
{
    LRUCache lRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    cout << lRUCache.get(1) << endl;    // 返回 1
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    cout << lRUCache.get(2) << endl;    // 返回 -1 (未找到)
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    cout << lRUCache.get(1) << endl;    // 返回 -1 (未找到)
    cout << lRUCache.get(3) << endl;    // 返回 3
    cout << lRUCache.get(4) << endl;    // 返回 4
}