#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <cstddef>  // for size_t
#include <iostream>
#include <sstream>
#include "error.h"
using std::cout;
using std::endl;

#define COPY

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
    explicit vector(size_t capacity = 10);  // default constructor
    vector(size_t n, ValueType value); // constructor with params
    ~vector();  // destructor
#ifdef COPY
    vector(const vector<ValueType> &other); // copy constructor
    vector<ValueType> &operator=(const vector<ValueType> &other); // copy assignment
#endif

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
    iterator insert(iterator pos, const ValueType &value);
    iterator erase(iterator pos);
    void push_back(const ValueType &value);
    void pop_back();

    // Conversion Operators
    operator bool() const;

    // Operators Overloading
    ValueType &operator[](size_t index);
    const ValueType &operator[](size_t index) const;

    // Using << for debugging
    std::string toString() const;

private:
    // Instance variables
    ValueType *_elements;
    int _capacity;
    int _count;

    // Class variables
    static int num_objects;
};

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

// ********************************************
// *             Implementation               *
// ********************************************

// initializing static class variables
template <typename ValueType>
int vector<ValueType>::num_objects = 0;

// ************* Member Function **************

template <typename ValueType>
vector<ValueType>::vector(size_t capacity) {
    _capacity = capacity;
    _count = 0;
    _elements = new ValueType[_capacity]();

    cout << "=== Default Constructor finished ===" << endl;
    num_objects++;
    cout << num_objects << " vector created" << endl;
}

template <typename ValueType>
vector<ValueType>::vector(size_t n, ValueType val) {
    _capacity = 2 * n;
    _count = n;
    _elements = (n == 0) ? nullptr : new ValueType[_capacity]();
    for (size_t i = 0; i < size(); i++) {
        _elements[i] = val;
    }

    cout << "=== Constructor with params finished ===" << endl;
    num_objects++;
    cout << num_objects << " vector created" << endl;
}

template <typename ValueType>
vector<ValueType>::~vector() {
    delete[] _elements;
    num_objects--;

    cout << "Deleting..." << endl;
    cout << "=== Destructor finished ===" << endl;
    cout << num_objects << " vector remains" << endl;
}

#ifdef COPY
template <typename ValueType>
vector<ValueType>::vector(const vector<ValueType> &other) {
    _elements = new ValueType[other.capacity()];
    _capacity = other.capacity();
    _count = other.size();
    std::copy(other.begin(), other.end(), _elements);

    cout << "=== Copy Constructor finished ===" << endl;
    num_objects++;
    cout << num_objects << " vector created" << endl;
}

template <typename ValueType>
vector<ValueType> &vector<ValueType>::operator=(const vector<ValueType> &other) {
    if(this != &other){
        delete[] _elements;
        _capacity = other.capacity();
        _count = other.size();
        ValueType* _new_elems = new ValueType[other.capacity()];
        std::copy(other.begin(), other.end(), _new_elems);
        _elements = _new_elems;

        cout << "=== Copy Assignment finished ===" << endl;
    }
    return *this;
}
#endif

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
typename vector<ValueType>::const_iterator vector<ValueType>::begin() const {
    return _elements;
}
template <typename ValueType>
typename vector<ValueType>::const_iterator vector<ValueType>::end() const {
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
ValueType &vector<ValueType>::at(size_t index) {
    if (index > size()) {
        // throw std::out_of_range("Out of range!");
        error("Out of range!");  // for testing
    }
    return *(begin() + index);
}

template <typename ValueType>
ValueType &vector<ValueType>::front() {
    return *begin();
}

template <typename ValueType>
ValueType &vector<ValueType>::back() {
    return *(end() - 1);
}

template <typename ValueType>
const ValueType &vector<ValueType>::at(size_t index) const {
    if (index > size()) {
        error("Out of range!");  // for testing
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

// ************ Conversion Operators **************

template <typename ValueType>
vector<ValueType>::operator bool() const {
    return empty();
}

// *********** Operators Overloading **************

template <typename ValueType>
ValueType &vector<ValueType>::operator[](size_t index) {
    if (index > size()) {
        error("Out of range!");
    }
    return _elements[index];
}

template <typename ValueType>
const ValueType &vector<ValueType>::operator[](size_t index) const {
    if (index > size()) {
        error("Out of range!");
    }
    return _elements[index];
}

}  // namespace cs101

#endif  // MY_VECTOR_H
