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

void PriorityQueue::swap(int kv1, int kv2) {
    KeyValuePair temp = nodes_[kv1];
    nodes_[kv1] = nodes_[kv2];
    nodes_[kv2] = temp;
}

PriorityQueue::PriorityQueue(std::size_t max_size) :
        nodes_(max_size + 1, KeyValuePair()),
        max_size_(max_size),
        size_(0) {
}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
    // TODO: complete this function
    size_++;
    nodes_[size_] = kv;
    heapifyUp(size_-1);
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
    removeNode(1);
    return pair;
}

bool PriorityQueue::isEmpty() const {
    // TODO: complete this function
    if (size_ == 0)
        return true;
    return false;
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
    while(i > 0){
        int Parent  = 1/2;
        if (nodes_[Parent].first > nodes_[i].first){
            swap(Parent, i);
        }
        i--;
    }
}

void PriorityQueue::heapifyDown(size_t i) {
    // TODO: complete this function
    while(i < size_) {
        int LeftChild = 2 * i;                      // NEED TO CHECK IF NULL
        int RightChild = 2 * i + 1;
        if ((LeftChild <= size_) && (RightChild <= size_) && (nodes_[LeftChild].first < nodes_[RightChild].first)){
            if (nodes_[LeftChild].first < nodes_[i].first) {       // left child smaller, heapify down that branch
                swap(LeftChild, i);
            }
        }
        else if ((RightChild <= size_) && (nodes_[RightChild].first < nodes_[i].first)) {        // right child smaller, heapify down that branch
            swap(RightChild, i);
        }

        i++;
    }

void PriorityQueue::removeNode(size_t i) {
    // TODO: complete this function
    nodes_[i] = nodes_[size_];          // sets pos to last element in array
    // nodes_.erase(nodes_.end());         // erases last element in array
    heapifyDown(i);                     // calls heapify down to move root to correct position
}

Key PriorityQueue::getKey(size_t i) {
    // TODO: complete this function
    return nodes_[i].first;
}