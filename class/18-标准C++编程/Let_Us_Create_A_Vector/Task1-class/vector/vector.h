#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <cstddef>  // for size_t

namespace cs101 {

class vector {
public:
    using ValueType = int;   // Alias for data type
    using iterator = int *;  // raw pointer

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

}  // namespace cs101

// Non-member function overloads

#endif  // MY_VECTOR_H
