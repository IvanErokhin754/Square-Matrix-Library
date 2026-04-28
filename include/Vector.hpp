#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include "MutableArraySequence.hpp"

template<typename T>
class Vector{
private:
    MutableArraySequence<T> data;

public:
    Vector() : data() {}

    explicit Vector(size_t size, const T& default_value = T()) : data() {
        for (size_t i = 0; i < size; i++) {
            data.Append(default_value);
        }
    }
    
    Vector(const Vector<T>& other) : data(other.data) {}

    Vector<T>& operator=(const Vector<T>& other) {
        if (this == &other) {
            return *this;
        }

        data = other.data;
        return *this;
    }

    size_t GetSize() const {
        return data.GetLength();
    }

    void Append(const T& value) {
        data.Append(value);
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    const T& Get(size_t index) const {
        return data[index];
    }

    void Set(size_t index, const T& value) {
        data[index] = value;
    }
    
};

#endif /* VECTOR_HPP */
