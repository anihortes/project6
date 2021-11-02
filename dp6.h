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
#include <algorithm>
// For std::copy
#include <string>
// For std::string
#include <functional>
// For std::function

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
    using key_type = Key;
    using value_type = Val;    // value type in array

public:
    LLMap<key_type, value_type>() = default;

    // No copy ctor, copy/move ops
    LLMap<key_type, value_type>(const LLMap<key_type, value_type> & other) = delete;

    LLMap & operator=(const LLMap & other) = delete;

    LLMap<key_type, value_type>(LLMap<key_type, value_type> && other) = delete;

    LLMap & operator=(const LLMap && other) = delete;

    ~LLMap()= default;

public:

    // Taken from llnode2.h size() function
    [[nodiscard]] size_type size() const{
        auto p = _uPtr.get();      // Iterates through list
        size_type counter = 0;  // Number of nodes so far
        while (p != nullptr)
        {
            p = p->_next.get();
            ++counter;
        }
        return counter;
    }
    
    [[nodiscard]] bool empty() const{
        return size()==0;
    }


    const value_type * find(const key_type & findKey) const{
        auto p = _uPtr.get();
        if(p == nullptr)
            return nullptr;
        while(p->_data.first != findKey || p != nullptr) {
            p = p->_next.get();
            if (p->_data.first == findKey) {
                const value_type *temp;
                temp = &(p->_data.second);
                return temp;
            }
        }
        return nullptr;
    }

    value_type * find(const key_type & findKey){
        auto p = _uPtr.get();
       //cout << p->_data.first << " first  "<<p->_data.second<<endl;

        if(p == nullptr)
            return nullptr;
        while(p != nullptr){
            //cout << p->_data.first << "  second "<< findKey <<endl;
            if(p->_data.first == findKey){
                //cout << p->_data.first << "  found "<<p->_data.second<<endl;

                value_type *temp;
                temp = &(p->_data.second);
                return temp;
            }
            p = p->_next.get();
            //cout << p->_data.first << " third  "<<p->_data.second<<endl;

            if(p == nullptr)
                break;
        }
        return nullptr;
    }

    void insert(const key_type & keyInsert, const value_type & valInsert){
        auto p = _uPtr.get();
        if(p != nullptr) {
            bool keyNotFound = true;
            while (p != nullptr) {
                if (p->_data.first == keyInsert) {
                    p->_data.second = valInsert;
                    keyNotFound = false;
                }
                p = p->_next.get();
            }
            if (keyNotFound){
                push_front(_uPtr, std::pair<key_type, value_type>(keyInsert, valInsert));
            }
        }
        else{
            push_front(_uPtr, std::pair<key_type, value_type>(keyInsert, valInsert));
            //cout << _uPtr.get()->_data.first << "   "<<_uPtr.get()->_data.second<<endl;
        }
    }

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
                    nextP = nullptr;
                    return;
                }
                p = nextP;
                nextP = nextP->_next.get();
            }
        }
    }

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