#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "../include/queue.h"
#include <stdexcept>

template<typename T>
Queue<T>::Queue() : front(-1), size(0), capacity(1000){
    arr = new T[capacity];
}

template<typename T>
void Queue<T>::resize(size_t new_capacity){
    T* newArr = new T[new_capacity];
    for(size_t i=0; i<size; i++)
        newArr[i] = arr[i];
    
    delete[] arr;
    arr = newArr;
    capacity = new_capacity;
}

template<typename T>
void Queue<T>::enqueue(T item){
    if(size == capacity)
        resize(capacity*2);
    
    arr[(front+size)%capacity] = item;
    size++;
}

template<typename T>
T Queue<T>::dequeue(){
    if(isEmpty())
        throw std::runtime_error("Can not dequeue empty queue");
    
    T first = arr[front];
    front = (front + 1)%capacity;
    --size;

    if(size > 0 && size <= capacity/4)
        resize(capacity/2);

    return first;
}

template<typename T>
T Queue<T>::Front() const{
    if(isEmpty())
        throw std::runtime_error("Can not Front empty queue");
    return arr[front];
}

template<typename T>
bool Queue<T>::isEmpty() const{
    return size == 0;
}

template<typename T>
size_t Queue<T>::Size() const{
    return size;
}

template<typename T>
Queue<T>::~Queue(){
    delete[] arr;
}

#endif 