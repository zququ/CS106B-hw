#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <cstddef>  // for size_t
#include "error.h"
#include <iostream>

namespace cs101 {

// ********************************************
// *               Interface                  *
// ********************************************

template <typename T>
class vector {
public:
    using ValueType = T;   // Alias for data type
    using iterator = T *;  // raw pointer

    // Member Function
    vector(size_t capacity = 10);  // default constructor(with default value)
    vector(size_t n, ValueType val);
    ~vector();                     // destructor

    // Iterators
    iterator begin();
    iterator end();

    // Capacity
    bool empty();
    size_t size();
    size_t capacity();
    void reserve(size_t n);

    // Element access
    ValueType &at(size_t index);
    ValueType &front();
    ValueType &back();

    // Modifiers
    void clear();
    iterator insert(iterator pos, ValueType value);
    iterator erase(iterator pos);
    void push_back(ValueType value);
    void pop_back();

private:
    // Instance variables
    ValueType *_elements;
    int _capacity;
    int _count;
};

// Non-member function overloads

// ********************************************
// *             Implementation               *
// ********************************************

// ************* Member Function **************

template <typename T>
vector<T>::vector(size_t capacity) {
    _capacity = capacity;
    _count = 0;
   _elements = new ValueType[_capacity]();
}

template <typename T>
vector<T>::vector(size_t n, ValueType val){
    _capacity = 2 * n;
    _count = n;
    _elements = (n == 0) ? nullptr : new ValueType[_capacity]();
    for (size_t i = 0; i < size(); i++) {
        _elements[i] = val;
    }
}

template <typename T>
vector<T>::~vector() {
    delete[] _elements;
}

// ***************** Iterator ******************

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
    return _elements;
}
template <typename T>
typename vector<T>::iterator vector<T>::end() {
    return _elements + size();
}

// ***************** Capacity ******************

template <typename T>
bool vector<T>::empty() {
    return size() == 0;
}

template <typename T>
size_t vector<T>::size() {
    return _count;
}

template <typename T>
size_t vector<T>::capacity() {
    return _capacity;
}

template <typename T>
void vector<T>::reserve(size_t n) {
    if (n > capacity()) {
        ValueType *_new_elems = new ValueType[n];
        for (size_t i = 0; i < size(); i++) {
            _new_elems[i] = _elements[i];
        }
        delete[] _elements;
        _elements = _new_elems;
        _capacity = n;
    }
}

// ************** Element access ***************

template <typename T>
typename vector<T>::ValueType &vector<T>::at(size_t index){
    if (index > size()) {
        // throw std::out_of_range("Out of range!");
        error("Out of range!"); // for testing
    }
    return *(begin() + index);
}

template <typename T>
typename vector<T>::ValueType &vector<T>::front(){
    return *begin();
}

template <typename T>
typename vector<T>::ValueType &vector<T>::back(){
    return *(end() - 1);
}

template <typename T>
void vector<T>::clear() {
    _count = 0;
}

// **************** Modifiers ******************

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, ValueType value) {
    int index = pos - begin();
    if (size() == capacity()) {
        reserve(2 * size());
        pos = begin() + index;
    }
    for (int i = size(); i > index; i--) {
        _elements[i] = _elements[i - 1];
    }
    _elements[index] = value;
    ++_count;
    return pos;
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(iterator pos) {
    int index = pos - begin();
    for (int i = index + 1; i < size(); i++) {
        _elements[i - 1] = _elements[i];
    }
    --_count;
    return pos;
}

template <typename T>
void vector<T>::push_back(ValueType value) {
    insert(end(), value);
}

template <typename T>
void vector<T>::pop_back() {
    --_count;
}

}  // namespace cs101

#endif  // MY_VECTOR_H
