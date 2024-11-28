#ifndef STACK_H
#define STACK_H

#include <vector>
#include <cstddef>

template<typename T>
class Stack {
private:
    T* arr;
    int top;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity);
    
public:
    Stack();
    ~Stack();

    void push(const T item);
    T pop();
    T Top() const;
    bool isEmpty() const;
    size_t Size() const;
};

#endif