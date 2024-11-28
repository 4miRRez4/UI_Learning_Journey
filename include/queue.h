#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>

template<typename T>
class Queue {
private:
    T* arr;
    int front;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity);
public:
    Queue();
    ~Queue();

    void enqueue(const T item);
    T dequeue();
    T Front() const;
    bool isEmpty() const;
    size_t Size() const;

};

#endif