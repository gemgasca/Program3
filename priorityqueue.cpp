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
    return (Parent(i) < 0);
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
    for (int i = 1; i <= size_; i++){       // iterates over every node
        Value pos = getValues(i);           // gets values for that node
        if (pos.first == value1 || pos.first == value2 || pos.second == value1 || pos.second == value2){
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
    removeNode(1);
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
    int Parent  = i/2;
    while((i > 0) && hasParent(i)){
        if (nodes_[Parent].first > nodes_[i].first){
            swap(Parent, i);
        }
        i--;
        int Parent  = i/2;
    }
}

//void PriorityQueue::heapifyDown(size_t i){
//    // TODO: complete this function
//    while (i <= size_) {
//        size_t left = LeftChild(i);
//        size_t right = RightChild(i);
//        if (hasLeftChild(i) && hasRightChild(i)) {
//            if (nodes_[left].first < nodes_[right].first && (nodes_[left].first < nodes_[i].first)) {       // left child smaller than current, heapify down that branch
//                swap(left, i);
//            }
//            else if (nodes_[right].first < nodes_[i].first) {        // right child smaller than current, heapify down that branch
//                swap(right, i);
//            }
//        }
//        else if (hasLeftChild(i) && (nodes_[left].first < nodes_[i].first)){ // left child smaller than current, heapify down that branch
//            swap(left, i);
//        }
//        else if (hasRightChild(i) && (nodes_[right].first < nodes_[i].first)){          // only has right
//            swap(right, i);
//        }
//        i++;
//    }
//}

//void PriorityQueue::heapifyDown(size_t i){
//    // TODO: complete this function
//    while (hasLeftChild(i)){           // has at least right child
//        size_t left = LeftChild(i);
//        size_t right = RightChild(i);
//        size_t child = left;        // the child to be swapped with
//        if (hasRightChild(i) && nodes_[left].first > nodes_[right].first){      // if right exists, and is smaller
//            child = right;
//        }
//
//        if (nodes_[child].first < nodes_[i].first){         // if child is smaller than current node, swap
//            swap(child, i);
//        }
//        else{
//            break;
//        }
//        i = child;
//    }
//}


void PriorityQueue::heapifyDown(size_t i){
}


void PriorityQueue::removeNode(size_t i) {
    // TODO: complete this function
    nodes_[i] = nodes_[size_];          // sets pos to last element in array
    size_--;
    heapifyDown(i);                     // calls heapify down to move root to correct position
}