#include <iostream>
#include <map>
#include <cassert>


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

    ~LRUCache() {
        // 删除链表的所有节点
        Node* node = head_->next;
        while(node != tail_) {
            Node* next = node->next;
            delete node;
            node = next;
        }

        delete head_;
        delete tail_;
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
                delete last;
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
    
public: // for test
    std::map<int, Node*> node_map_;
    Node* head_;
    Node* tail_;
    int node_count_;
    int capacity_ = 0;
};


int main() {
    std::cout << "开始LRU缓存测试..." << std::endl;
    
    try {
        // 测试基本操作
        {
            std::cout << "测试基本操作..." << std::endl;
            LRUCache cache(3);  // 创建容量为3的缓存
            
            cache.Put(1, 1);
            cache.Put(2, 2);
            cache.Put(3, 3);
            assert(cache.Get(1) == 1);
            assert(cache.Get(2) == 2);
            assert(cache.Get(3) == 3);
            
            std::cout << "基本插入和获取测试通过" << std::endl;
        }

        // 测试淘汰机制
        {
            std::cout << "测试淘汰机制..." << std::endl;
            LRUCache cache(3);
            
            cache.Put(1, 1);
            cache.Put(2, 2);
            cache.Put(3, 3);
            
            cache.Put(4, 4);  // 应该淘汰1
            assert(cache.Get(1) == -1);  // 1应该已经被淘汰
            assert(cache.Get(2) == 2);
            assert(cache.Get(3) == 3);
            assert(cache.Get(4) == 4);
            
            std::cout << "淘汰机制测试通过" << std::endl;
        }

        // 测试更新现有值
        {
            std::cout << "测试更新现有值..." << std::endl;
            LRUCache cache(3);
            
            cache.Put(1, 1);
            cache.Put(2, 2);
            cache.Put(1, 10);  // 更新1的值
            
            assert(cache.Get(1) == 10);
            
            std::cout << "更新现有值测试通过" << std::endl;
        }

        // 测试访问顺序
        {
            std::cout << "测试访问顺序..." << std::endl;
            LRUCache cache(3);
            
            cache.Put(1, 1);
            cache.Put(2, 2);
            cache.Put(3, 3);
            
            cache.Get(1);  // 访问1，使其变为最近使用
            
            cache.Put(4, 4);  // 应该淘汰2而不是1
            
            assert(cache.Get(1) == 1);   // 1应该还在
            assert(cache.Get(2) == -1);  // 2应该被淘汰
            assert(cache.Get(3) == 3);
            assert(cache.Get(4) == 4);
            
            std::cout << "访问顺序测试通过" << std::endl;
        }

        std::cout << "所有测试通过！" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}



