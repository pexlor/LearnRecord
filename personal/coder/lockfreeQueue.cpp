#include <atomic>
#include <memory>

template<typename T>
class LockFreeQueue {
private:
    struct Node {
        T data;
        std::atomic<Node*> next;

        Node(T const& data_) : data(data_), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LockFreeQueue() : head(new Node(T())), tail(head.load()) {}

    ~LockFreeQueue() {
        while (Node* const old_head = head.load()) {
            head.store(old_head->next);
            delete old_head;
        }
    }

    void push(T const& data) {
        std::unique_ptr<Node> new_node(new Node(data));
        Node* const new_tail = new_node.get();

        Node* old_tail = tail.load();
        while (!old_tail->next.compare_exchange_weak(nullptr, new_tail)) {
            old_tail = tail.load();
        }

        tail.compare_exchange_weak(old_tail, new_tail);
        new_node.release();
    }

    bool pop(T& result) {
        Node* old_head = head.load();

        while (old_head && !head.compare_exchange_weak(old_head, old_head->next.load())) {
            old_head = head.load();
        }
        if (!old_head) return false;

        result = old_head->data;
        delete old_head;
        return true;
    }
};