#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <cstddef>  // for size_t
#include "error.h"
#include <iostream>
#include <sstream>

#define OVERLOADING

namespace cs101 {

// ********************************************
// *               Interface                  *
// ********************************************

template <typename ValueType>
class vector {
public:
    using iterator = ValueType *;  // raw pointer
    using const_iterator = const ValueType *;

    // Member Function
    explicit vector(size_t capacity = 10);  // default constructor(with default value)
    vector(size_t n, ValueType value);
    ~vector();                     // destructor

    // Iterators
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    // Capacity
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void reserve(size_t n);

    // Element access
    ValueType &at(size_t index);
    ValueType &front();
    ValueType &back();

    const ValueType &at(size_t index) const;
    const ValueType &front() const;
    const ValueType &back() const;

    // Modifiers
    void clear();
    iterator insert(iterator pos,const ValueType& value);
    iterator erase(iterator pos);
    void push_back(const ValueType& value);
    void pop_back();

#ifdef OVERLOADING
    // Conversion Operators
    operator bool() const;

    // Operators Overloading
    ValueType& operator [](size_t index);
    const ValueType &operator[](size_t index) const;

    // Using << for debugging
    std::string toString() const;
#endif

private:
    // Instance variables
    ValueType *_elements;
    int _capacity;
    int _count;
};

#ifdef OVERLOADING
// Non-member function overloads
template <typename ValueType>
std::ostream &operator<<(std::ostream &os, const vector<ValueType> &vec) {
    os << "{";
    int len = vec.size();
    for (int i = 0; i < len; i++) {
        if (i > 0) os << ", ";
        os << vec.at(i);
    }
    return os << "}";
}

template <typename ValueType>
std::string vector<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}
#endif

// ********************************************
// *             Implementation               *
// ********************************************

// ************* Member Function **************

template <typename ValueType>
vector<ValueType>::vector(size_t capacity) {
    _capacity = capacity;
    _count = 0;
   _elements = new ValueType[_capacity]();
}

template <typename ValueType>
vector<ValueType>::vector(size_t n, ValueType val){
    _capacity = 2 * n;
    _count = n;
    _elements = (n == 0) ? nullptr : new ValueType[_capacity]();
    for (size_t i = 0; i < size(); i++) {
        _elements[i] = val;
    }
}

template <typename ValueType>
vector<ValueType>::~vector() {
    delete[] _elements;
}

// ***************** Iterator ******************

template <typename ValueType>
typename vector<ValueType>::iterator vector<ValueType>::begin() {
    return _elements;
}
template <typename ValueType>
typename vector<ValueType>::iterator vector<ValueType>::end() {
    return _elements + size();
}

template <typename ValueType>
typename vector<ValueType>::const_iterator vector<ValueType>::begin() const{
    return _elements;
}
template <typename ValueType>
typename vector<ValueType>::const_iterator vector<ValueType>::end() const{
    return _elements + size();
}


// ***************** Capacity ******************

template <typename ValueType>
bool vector<ValueType>::empty() const {
    return size() == 0;
}

template <typename ValueType>
size_t vector<ValueType>::size() const {
    return _count;
}

template <typename ValueType>
size_t vector<ValueType>::capacity() const {
    return _capacity;
}

template <typename ValueType>
void vector<ValueType>::reserve(size_t n) {
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

template <typename ValueType>
ValueType &vector<ValueType>::at(size_t index){
    if (index > size()) {
        // throw std::out_of_range("Out of range!");
        error("Out of range!"); // for testing
    }
    return *(begin() + index);
}

template <typename ValueType>
ValueType &vector<ValueType>::front(){
    return *begin();
}

template <typename ValueType>
ValueType &vector<ValueType>::back(){
    return *(end() - 1);
}

template <typename ValueType>
const ValueType &vector<ValueType>::at(size_t index) const {
    if (index > size()) {
        error("Out of range!"); // for testing
    }
    return *(begin() + index);
}

template <typename ValueType>
const ValueType &vector<ValueType>::front() const {
    return *begin();
}

template <typename ValueType>
const ValueType &vector<ValueType>::back() const {
    return *(end() - 1);
}

// **************** Modifiers ******************

template <typename ValueType>
void vector<ValueType>::clear() {
    _count = 0;
}

template <typename ValueType>
typename vector<ValueType>::iterator vector<ValueType>::insert(
    iterator pos, const ValueType &value) {
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

template <typename ValueType>
typename vector<ValueType>::iterator vector<ValueType>::erase(iterator pos) {
    int index = pos - begin();
    for (int i = index + 1; i < size(); i++) {
        _elements[i - 1] = _elements[i];
    }
    --_count;
    return pos;
}

template <typename ValueType>
void vector<ValueType>::push_back(const ValueType &value) {
    insert(end(), value);
}

template <typename ValueType>
void vector<ValueType>::pop_back() {
    --_count;
}

#ifdef OVERLOADING
// ************ Conversion Operators **************

template <typename ValueType>
vector<ValueType>::operator bool() const{
    return empty();
}

// *********** Operators Overloading **************

template <typename ValueType>
ValueType &vector<ValueType>::operator[](size_t index) {
    if(index > size()){
        error("Out of range!");
    }
    return _elements[index];
}

template <typename ValueType>
const ValueType &vector<ValueType>::operator[](size_t index) const {
    if(index > size()){
        error("Out of range!");
    }
    return _elements[index];
}
#endif

}  // namespace cs101

#endif  // MY_VECTOR_H
