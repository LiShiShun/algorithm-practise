#include <iostream>
#include <map>

#define NDEBUG
#include <assert.h>


class LRUCache {
public:
    // 双向链表节点
    struct Node {
        int key;
        int value;
        struct Node* prev;
        struct Node* next;

        Node(int k, int v):key(k),value(v),prev(nullptr),next(nullptr){}
        Node():key(0),value(0),prev(nullptr),next(nullptr){}
    };


public:
    LRUCache(int capacity) {
        node_map_.clear();

        head_ = new Node();
        tail_ = new Node();
        head_->next = tail_;
        head_->prev = nullptr;
        tail_->prev = head_;
        tail_->next = nullptr;
        node_count_ = 0;

        capacity_ = capacity < 0? 0 : capacity;
    }

    int Get(int key) {
        Node* node = GetNode(key);
        if(node == nullptr) {
            return -1;
        }

        DeleteNode(*node);
        MoveToHead(*node);
        return node->value;
    }

    void Put(int key, int value) {
        Node* node = GetNode(key);
        if(node == nullptr) {
            node = new Node(key, value);
            node_map_[key] = node;
            MoveToHead(*node);
            node_count_++;
            if(node_count_ > capacity_) {
                Node* last = tail_->prev;
                DeleteNode(*last);
                node_count_--;
                auto last_it = node_map_.find(last->key);
                if(last_it != node_map_.end()) {
                    node_map_.erase(last_it);
                }
            }

        } else {
            node->value = value;
            DeleteNode(*node);
            MoveToHead(*node);
        }
    }

private:
    Node* GetNode(int key) {
        auto it = node_map_.find(key);
        if(it == node_map_.end()) {
            return nullptr;
        }

        return it->second;
    }

    void DeleteNode(Node& node) {
        node.prev->next = node.next;
        node.next->prev = node.prev;
    }

    void MoveToHead(Node& node) {
        node.next = head_->next;
        node.prev = head_;
        head_->next->prev = &node;
        head_->next = &node;
    }
    
private:
    std::map<int, Node*> node_map_;
    Node* head_;
    Node* tail_;
    int node_count_;
    int capacity_ = 0;
};


int main() {
    LRUCache cache(2);
    cache.Put(1, 1);
    cache.Put(2, 2);
    
    int ret = cache.Get(1); // 返回 1
    assert(ret == 1);
    std::cout<<"lru 1 "<< (ret == 1) << std::endl;

    cache.Put(3, 3); // 该操作会使得关键字 2 作废
    ret = cache.Get(2); // 返回 -1 (未找到)
    std::cout << "lru 2 " << (ret == -1) << std::endl;
    cache.Put(4, 4); // 该操作会使得关键字 1 作废
    ret = cache.Get(1); // 返回 -1 (未找到)
    std::cout << "lru 3 " << (ret == -1) << std::endl;
    ret = cache.Get(3); // 返回 3
    std::cout << "lru 3 " << (ret == 3) << std::endl;
    ret = cache.Get(4); // 返回 4
    std::cout << "lru 3 " << (ret == 4) << std::endl;

    std::cout<<"lru finish"<<std::endl;

    return 0;
}



