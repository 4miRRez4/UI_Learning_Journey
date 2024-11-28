#ifndef STACK_CPP
#define STACK_CPP

#include "../include/stack.h"
#include <stdexcept>

template<typename T>
Stack<T>::Stack() : size(0), top(-1), capacity(1000){
    this->arr = new T[capacity];
}

template<typename T>
void Stack<T>::resize(size_t new_capacity){
    T* newArr = new T[new_capacity];
    for(size_t i=0; i<=top; i++)
        newArr[i] = arr[i];
    
    delete[] arr;
    arr = newArr;
    capacity = new_capacity;
}

template<typename T>
void Stack<T>::push(const T item){
    if(size == capacity)
        resize(capacity*2);
    
    size++;
    arr[++top] = item;
}

template<typename T>
T Stack<T>::pop(){
    if(isEmpty())
        throw std::runtime_error("Can not pop from an Empty stack");

    T last = arr[top--];
    size--;

    if(size > 0 && size <= capacity/4)
        resize(capacity/2);

    return last;
}

template<typename T>
T Stack<T>::Top() const{
    if(isEmpty())
        throw std::runtime_error("Can not top an empty stack");

    return arr[top];
}

template<typename T>
bool Stack<T>::isEmpty() const{
    return size == 0;
}

template<typename T>
size_t Stack<T>::Size() const{
    return size;
}

template<typename T>
Stack<T>::~Stack() {
    delete[] arr;
}

#endif