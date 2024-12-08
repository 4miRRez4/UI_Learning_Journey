#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>

template<typename T>
class Queue {
private:
    T* arr;
    size_t front;
    size_t size;
    size_t capacity;

public:
    Queue() : front(-1), size(0), capacity(1000){
        arr = new T[capacity];
    }

    ~Queue(){
        delete[] arr;
    }

    void enqueue(T item){
        if(size == capacity)
            resize(capacity*2);
        
        arr[(front+size)%capacity] = item;
        size++;
    }
    
    T dequeue(){
        if(isEmpty())
            throw std::runtime_error("Can not dequeue empty queue");
        
        T first = arr[front];
        front = (front + 1)%capacity;
        --size;

        if(size > 0 && size <= capacity/4)
            resize(capacity/2);

        return first;
    }

    T Front() const{
        if(isEmpty())
            throw std::runtime_error("Can not Front empty queue");
        return arr[front];
    }

    bool isEmpty() const{
        return size == 0;
    }

    size_t Size() const{
        return size;
    }

private:
    void resize(size_t new_capacity){
        T* newArr = new T[new_capacity];
        for(size_t i=0; i<size; i++)
            newArr[i] = arr[i];
        
        delete[] arr;
        arr = newArr;
        capacity = new_capacity;
    }
};

#endif