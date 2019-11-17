#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"

// helper functions
size_t PriorityQueue::Parent(size_t i) {       // returns parent
    return i / 2;
}
size_t PriorityQueue::LeftChild(size_t i) {    // returns left child
    return 2 * i;
}
size_t PriorityQueue::RightChild(size_t i) {   // returns right child
    return 2 * i + 1;
}

bool PriorityQueue::hasRightChild(size_t i){
    return (RightChild(i) <= size_);
}

bool PriorityQueue::hasLeftChild(size_t i){
    return (LeftChild(i) <= size_);
}

bool PriorityQueue::hasParent(size_t i){
    return (Parent(i) > 0);
}

Key PriorityQueue::getKey(size_t i) {
    // TODO: complete this function
    return nodes_[i].first;
}

Value PriorityQueue::getValues(size_t i){
    return nodes_[i].second;
}

void PriorityQueue::swap(int kv1, int kv2) {
    KeyValuePair temp = nodes_[kv1];
    nodes_[kv1] = nodes_[kv2];
    nodes_[kv2] = temp;
}

void PriorityQueue::removeDupPlayers(Value val){
    int value1 = val.first;
    int value2 = val.second;
    for (size_t i = 1; i <= size_; i++){       // iterates over every node
        Value posDup = getValues(i);           // gets values for that node
        if (posDup.first == value1 || posDup.first == value2 || posDup.second == value1 || posDup.second == value2){
            removeNode(i);          // removes node if nay of the values match
        }
    }
}

PriorityQueue::PriorityQueue(std::size_t max_size) : nodes_(max_size + 1, KeyValuePair()),max_size_(max_size), size_(0) {}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
    // TODO: complete this function
    size_++;
    nodes_[size_] = kv;
    heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
    // TODO: complete this function
    if (isEmpty()){
        throw std::underflow_error("Empty priority queue!");     // returns empty pair if queue empty
    }
    return nodes_[ROOT];
}

KeyValuePair PriorityQueue::removeMin() {
    // TODO: complete this function
    if (isEmpty()){
        throw std::underflow_error("Empty priority queue!");     // returns empty pair if queue empty
    }

    KeyValuePair pair = min();
    removeNode(ROOT);
    return pair;
}

bool PriorityQueue::isEmpty() const {
    // TODO: complete this function
    return (size_ == 0);
}

size_t PriorityQueue::size() const {
    // TODO: complete this function
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
    nlohmann::json result;
    for (size_t i = 1; i <= size(); i++) {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(i / 2);
        }
        if (2 * i <= size_) {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_) {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    // TODO: complete this function
    while(hasParent(i)){
        if (nodes_[Parent(i)].first > nodes_[i].first){
            swap(Parent(i), i);
        }
        i = Parent(i);
    }
}

void PriorityQueue::heapifyDown(size_t i){
    // TODO: complete this function
    while(hasLeftChild(i)){                     // checks if has left child at least
        int small_child = LeftChild(i);
        if(hasRightChild(i) && nodes_[RightChild(i)].first < nodes_[LeftChild(i)].first){       // checks if has right child and is smaller than left
            small_child = RightChild(i);
        }

        if (nodes_[small_child].first < nodes_[i].first){       // if node is smaller than current, swap
            swap(small_child, i);
        }
        else{           // don't have to heapify anymore, since rest of tree should be in order
            break;
        }

        i = small_child;
    }
}


void PriorityQueue::removeNode(size_t i) {
    // TODO: complete this function
    nodes_[i] = nodes_[size_];          // sets pos to last element in array
    size_--;
    heapifyDown(i);                     // calls heapify down to move root to correct position
}