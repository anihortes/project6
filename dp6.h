// FSTArray.h
// A. Harrison Owen
// Started: 2021-10-15
// Updated: 2021-10-28
//
// For CS 311 Fall 2021
// Frightfully smart array of int
#ifndef PROJECT6_DP6_H
#define PROJECT6_DP6_H

#include "llnode2.h"

#include <memory>
// For std::unique_ptr
#include <utility>
// For std::pair, std::move
#include <cstddef>
// For std::size_t

#include <iostream>
using std::cout;
using std::endl;
// *********************************************************************
// class FSTArray - Class definition
// *********************************************************************


// class FSTArray
// Frightfully Smart Array of int.
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of value_type, allocated with new [],
//      owned by *this, holding _capacity value_type values -- UNLESS
//      _capacity == 0, in which case _data may be nullptr.
//
// value_type = value type of array elements

template<typename ValType>
void reverseList (std::unique_ptr<LLNode2<ValType>> & head){
    if(head) {
        std::unique_ptr<LLNode2<ValType>> newHead;
        auto temp = std::move(head->_next);
        while (head) {
            head->_next = std::move(newHead);
            newHead = std::move(head);
            head = std::move(temp);
            if(head){
                temp = std::move(head->_next);
            }
        }
        head = std::move(newHead);
    }
}

template<typename Key, typename Val>
class LLMap{
    using size_type = std::size_t;
    using value_type = Val;    // value type in array

public:
    LLMap(){

    }
    LLMap(const LLMap & other){

    }

    ~LLMap(){

    }

public:
    const size_type size() const{
        return 0;
    }
    
    const bool empty() const{
        return false;
    }
    
    const value_type * find(const Key & findKey) const{
        return nullptr;
    }
     value_type * find(const Key & findKey) {
        return nullptr;
    }

    void insert(const Key & keyInsert, const Val & insertVal){
    }

    void erase(const Key & eraseKey){
    }

    template<typename T>
    void traverse(const T & functionObj){
    }

private:
    std::unique_ptr<LLNode2<std::pair<Key, Val>>> _uniquePtr;
};

#endif //PROJECT6_DP6_H
