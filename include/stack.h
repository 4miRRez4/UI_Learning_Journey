#ifndef STACK_H
#define STACK_H

#include <vector>
#include <cstddef>

template<typename T>
class Stack {
private:
    T* arr;
    size_t top;
    size_t size;
    size_t capacity;
    
public:
    Stack() : top(-1), size(0), capacity(1000){
        this->arr = new T[capacity];
    }
    ~Stack(){
        delete[] arr;
    }   

    void push(const T item){
        if(size == capacity)
            resize(capacity*2);
        
        size++;
        arr[++top] = item;
    }

    T pop(){
        if(isEmpty())
            throw std::runtime_error("Can not pop from an Empty stack");

        T last = arr[top--];
        size--;

        if(size > 1000 && size <= capacity/4)
            resize(capacity/2);

        return last;
    }

    T Top() const{
        if(isEmpty())
            throw std::runtime_error("Can not top an empty stack");

        return arr[top];
    }

    bool isEmpty()  const{
        return size == 0;
    }   

    size_t Size()  const{
        return size;
    };

private:
    void resize(size_t new_capacity){
        T* newArr = new T[new_capacity];
        for(size_t i=0; i<=top; i++)
            newArr[i] = arr[i];
        
        delete[] arr;
        arr = newArr;
        capacity = new_capacity;
    }
};

#endif