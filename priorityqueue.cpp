#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"

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
    nodes_[size_+1] = kv;
    size_++;
    heapifyUp(size_-1);
}

KeyValuePair PriorityQueue::min() {
    // TODO: complete this function
    return nodes_[ROOT];
}

KeyValuePair PriorityQueue::removeMin() {
    // TODO: complete this function
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
    for (size_t i = 1; i <= size_; i++) {
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
    int next_up = i - 1;
    while (nodes_[i].second < nodes_[next_up].second){
        Value temp = nodes_[next_up].second;
        nodes_[next_up].second = nodes_[i].second;
        nodes_[i].second = temp;
        i--;
        next_up--;
    }
}

void PriorityQueue::heapifyDown(size_t i) {
    // TODO: complete this function
    int next_up = i + 1;
    while(nodes_[i].second > nodes_[next_up].second) {
        Value temp = nodes_[next_up].second;
        nodes_[next_up].second = nodes_[i].second;
        nodes_[i].second = temp;
        i++;
        next_up++;
    }
}

void PriorityQueue::removeNode2(size_t i) {
    // TODO: complete this function
    nodes_.erase(nodes_.begin()+i);
    for(size_t j = 1; j < size_ - 1; j++){
        while(j >= i && j < size_ - 1){
            nodes_[i] = nodes_[j];
            i++;
            j++;
        }
    }
    size_--;
}

void PriorityQueue::removeNode(size_t i) {
    // TODO: complete this function
    nodes_[i] = nodes_[size_];
    heapifyDown(i);
}

Key PriorityQueue::getKey(size_t i) {
    // TODO: complete this function
    return nodes_[i].first;
}

// helper functions
int PriorityQueue::Parent(size_t i) {       // returns parent
    return i / 2;
}
int PriorityQueue::LeftChild(size_t i) {    // returns left child
    return 2 * i;
}
int PriorityQueue::RightChild(size_t i) {   // returns right child
    return 2 * i + 1;
}
