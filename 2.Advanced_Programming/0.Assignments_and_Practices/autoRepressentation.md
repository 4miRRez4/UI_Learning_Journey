### Welcome

- Introduction To Cpp11
- What is Auto keyword?
- Importance of Auto keyword and Type Deduction
- Advantages of Using Auto keyword
- Syntax And Usage of 'auto'
- Limitation of 'auto'
- Conclusion

---

### Introduction To Cpp11

- C++11 is a major update to the C++ programming language.

- It started a new era in C++.

- Modern C++ refers to the use of features and best practices introduced in C++11 and later standards.

- Introduced many new features and improvements to enhance readability, maintainability, and performance.

- Solved many limitations and complexities in earlier versions of C++.

- Improved productivity of programmers.

- Some features added to C++ in version 11:
```
    Lambda expression
    Smart pointers
    nullptr
    Threading support
    and Auto keyword...
```

---

### What is 'auto'?

- The auto keyword allows the compiler to automatically deduce the type of a variable at compile-time based on its initializer.
- Part of the C++11 version to enhance type inference.

### Importance of Auto Keyword and Type Deduction?

**Coding in High Level**

- Being part of a big picture.
- Not wasting time telling compiler what it knows.
- Consistency with Other Languages (vs python)
- Many other advantages discussed later.
- (https://open-std.org/jtc1/sc22/wg21/docs/papers/2009/n2869.html)

---

### Advantages of using 'auto'

**Simplification**

**Readability**

**Maintenance and Refactoring**

**Reduce Error**

---

### Syntax And Usage Of 'auto'
```
"auto variable_name = initializer";
```

**Basic**
```cpp
auto x = 10; // int
auto y = 3.14; // double
auto ptr = &x; // int*
```

**Iterators**

```cpp
std::vector<int> vec = {1, 2, 3};
for (auto it = vec.begin(); it != vec.end(); ++it) { /* ... */ }
```

**Function Return Types**
```cpp
auto getVector() { /* ... */ }
```

**Lambda Expressions**
```cpp
auto lambda = [](int x, int y) { return x * y; };
```

**Template Code**
```cpp
template <typename T, typename U>
auto multiply(T a, U b) {
    return a * b;
}
```

---

### Limitation of 'auto'

**Uninitialized Variables**

- cannot be used when the type cannot be deduced;

**Loss of Type Information**

- auto may not consider references and const qualifiers.

- Example:
```cpp
const int& ref = 5; 
auto var = ref; // var is int, not const int&
```

**Unintended Conversions**

- Some expressions may lead to unintended type conversions.

- Example:
```cpp
auto sum = 3 + 3.14; // sum is double
```

**Over Use**
- may reduce code clarity if over used.

---

### Conclusion

- The auto keyword introduced in C++11 enhances simplifies code and reduces redundancy.
- It is part of big approach.
- It is useful for improving readability and maintainability, especially with complex types.
- Use auto wisely to balance between simplicity and code clarity.
