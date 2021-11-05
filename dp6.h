// Project 6
// A. Harrison Owen
// Started: 2021-10-29
// Updated: 2021-11-04
//
// For CS 311 Fall 2021

#ifndef PROJECT6_DP6_H
#define PROJECT6_DP6_H

#include "llnode2.h"

#include <memory>
// For std::unique_ptr
#include <utility>
// For std::pair, std::move
#include <cstddef>
// For std::size_t
#include <string>
// For std::string
#include <functional>
// For std::function

// reverseList - reverses items in a LLNode2 class list
// No-Throw Guarantee
// Exception neutral
template<typename ValType>
void reverseList (std::unique_ptr<LLNode2<ValType>> & head){
    // if statement checks if list is empty
    if(head) {
        std::unique_ptr<LLNode2<ValType>> newHead;
        // temp points to next item in list
        auto temp = std::move(head->_next);
        while (head) {
            // swap pointers around to reverse list one node at a time
            head->_next = std::move(newHead);
            newHead = std::move(head);
            head = std::move(temp);
            if(head){
                temp = std::move(head->_next);
            }
        }
        // update head of list
        head = std::move(newHead);
    }
}


// class LLMap
// Uses a linked list to hold an associative dataset
// Invariants:
//     Each Key is unique
//     0 <= size_type
//     _uPtr: A std::unique_pointer which points to either a nullptr or
//            linked list nodes containing std::pair<Key, Value>
//
template<typename Key, typename Val>
class LLMap{
    // for size of list
    using size_type = std::size_t;
    // key and value types in nodes
    using key_type = Key;
    using value_type = Val;

public:
    // by design of std::unique_pointer, _uPtr by default points to a nullptr
    LLMap<key_type, value_type>() = default;

    // No copy ctor, copy/move ops
    LLMap<key_type, value_type>(const LLMap<key_type, value_type> & other) = delete;
    LLMap & operator=(const LLMap & other) = delete;
    LLMap<key_type, value_type>(LLMap<key_type, value_type> && other) = delete;
    LLMap & operator=(const LLMap && other) = delete;

    ~LLMap()= default;

public:

    // Taken from llnode2.h size() function
    // Written by: Dr. Glenn Chappell
    // No-Throw Guarantee
    // Exception neutral
    [[nodiscard]] size_type size() const{
        auto p = _uPtr.get();
        size_type count = 0;
        while (p != nullptr)
        {
            // points to next item
            p = p->_next.get();
            ++count;
        }
        return count;
    }

    // No-Throw Guarantee
    // Exception neutral
    [[nodiscard]] bool empty() const{
        return size()==0;
    }

    // find - const & non-const
    //    returns nullptr if list is empty or key isn't in dataset
    //    returns pointer to value associated with key, if key is found
    // Strong Guarantee
    // Exception neutral
    const value_type * find(const key_type & findKey) const{
        auto p = _uPtr.get();
        while(p != nullptr){
            if(p->_data.first == findKey){
                const value_type *temp;
                temp = &(p->_data.second);
                // temp points to Value stored in node
                return temp;
            }
            p = p->_next.get();
        }
        return nullptr;
    }
    value_type * find(const key_type & findKey){
        auto p = _uPtr.get();
        while(p != nullptr){
            if(p->_data.first == findKey){
                value_type *temp;
                temp = &(p->_data.second);
                // temp points to Value stored in node
                return temp;
            }
            p = p->_next.get();
        }
        return nullptr;
    }

    // insert
    // inserts std::pair<Key, Value> into dataset
    //     if Key already exists, then replace old Value with new Value
    // Strong Guarantee
    // Exception neutral
    void insert(const key_type & keyInsert, const value_type & valInsert){
        auto p = _uPtr.get();
        if(p != nullptr) {
            while (p != nullptr) {
                // if key exists, rewrite Value
                if (p->_data.first == keyInsert) {
                    p->_data.second = valInsert;
                    // insert did its job, leave.
                    return;
                }
                p = p->_next.get();
            }
        }
        // Key was not found, make a new node for list
        push_front(_uPtr, std::pair<key_type, value_type>(keyInsert, valInsert));
    }

    // erase
    // if Key is found, erase node from list
    // if Key is not found, do nothing
    // Strong Guarantee
    // Exception neutral
    void erase(const key_type & eraseKey){
        auto p = _uPtr.get();
        if(p != nullptr) {
            if(p->_data.first == eraseKey){
                _uPtr = std::move(_uPtr->_next);
                return;
            }
            auto nextP = p->_next.get();
            while (nextP != nullptr) {
                if (nextP->_data.first == eraseKey) {
                    p->_next = std::move(nextP->_next);
                    // make sure it doesnt point to data
                    nextP = nullptr;
                    return;
                }
                p = nextP;
                nextP = nextP->_next.get();
            }
        }
    }

    // traverse
    // do "something" to each item in the list
    // Strong Guarantee
    // Exception neutral
    void traverse(const std::function<void(key_type, value_type)> & ff){
        auto p = _uPtr.get();
        while (p != nullptr) {
            try{
                ff(p->_data.first, p->_data.second);
            }
            catch(...){
                throw;
            }

            p = p->_next.get();
        }

    }

private:

    std::unique_ptr<LLNode2<std::pair<key_type, value_type>>> _uPtr;
};



#endif //PROJECT6_DP6_H