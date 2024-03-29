#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <vector>
#include <utility>
#include "json.hpp"

typedef double                  Key;
typedef std::pair<int, int>     Value;
typedef std::pair<Key, Value>   KeyValuePair; 

class PriorityQueue {
  public:
    PriorityQueue(std::size_t max_nodes);
    void insert(Key k);
    void insert(KeyValuePair kv);
    KeyValuePair min();
    KeyValuePair removeMin();
    bool isEmpty() const;
    size_t size() const;
    nlohmann::json JSON() const;

    // helper functions
    size_t Parent(size_t i);
    size_t LeftChild(size_t i);
    size_t RightChild(size_t i);
    bool hasLeftChild(size_t i);
    bool hasRightChild(size_t i);
    bool hasParent(size_t i);
    void swap(int kv1, int kv2);
    void removeDupPlayers(Value val);
    Value getValues(size_t i);

private:
    void heapifyUp(size_t i);
    void heapifyDown(size_t i);
    void removeNode(size_t i);
    Key getKey(size_t i);

    std::vector<KeyValuePair>   nodes_;
    size_t                      max_size_;
    size_t                      size_;

    const static size_t         ROOT = 1;
};  // class PriorityQueue



#endif  // _PRIORITYQUEUE_H_