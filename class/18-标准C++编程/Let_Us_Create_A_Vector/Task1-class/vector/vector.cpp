#include "vector.h"
#include "error.h"
#include <iostream>

using namespace cs101;

// ************* Member Function **************

vector::vector(size_t capacity) {
    _capacity = capacity;
    _count = 0;
   _elements = new ValueType[_capacity]();
}

vector::vector(size_t n, ValueType val){
    _capacity = 2 * n;
    _count = n;
    _elements = (n == 0) ? nullptr : new ValueType[_capacity]();
    for (size_t i = 0; i < size(); i++) {
        _elements[i] = val;
    }
}

vector::~vector() {
    delete[] _elements;
}

// ***************** Iterator ******************

vector::iterator vector::begin() {
    return _elements;
}
vector::iterator vector::end() {
    return _elements + size();
}

// ***************** Capacity ******************

bool vector::empty() {
    return size() == 0;
}

size_t vector::size() {
    return _count;
}

size_t vector::capacity() {
    return _capacity;
}

void vector::reserve(size_t n) {
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

// **************** Modifiers ******************


// ************** Element access ***************

vector::ValueType &vector::at(size_t index){
    if (index > size()) {
        // throw std::out_of_range("Out of range!");
        error("Out of range!"); // for testing
    }
    return *(begin() + index);
}

vector::ValueType &vector::front(){
    return *begin();
}

vector::ValueType &vector::back(){
    return *(end() - 1);
}

void vector::clear() {
    _count = 0;
}

vector::iterator vector::insert(iterator pos, ValueType value) {
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

vector::iterator vector::erase(iterator pos) {
    int index = pos - begin();
    for (int i = index + 1; i < size(); i++) {
        _elements[i - 1] = _elements[i];
    }
    --_count;
    return pos;
}

void vector::push_back(ValueType value) {
    insert(end(), value);
}

void vector::pop_back() {
    --_count;
}
