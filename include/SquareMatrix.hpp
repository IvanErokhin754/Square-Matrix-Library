#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include "Sequence.hpp"
#include "MutableArraySequence.hpp"
#include <stdexcept>
#include <cmath>

template <typename T>

class SquareMatrix {
private:
    size_t size;
    MutableArraySequence<T> data;

    size_t Index(size_t i, size_t j) const {
        return i * size + j;
    }

    void CheckBounds(size_t i, size_t j) const {
        if (i >= size || j >= size)
            throw std::out_of_range("Index out of range");
    }

public:
    SquareMatrix() : size(0), data() {}
    SquareMatrix(size_t n, const T& default_value = T()) : size(n), data() {
        for (size_t i = 0; i < size * size; i++) {
            data.Append(default_value);
        }
    }
    SquareMatrix(const SquareMatrix<T>& other) : size(other.size), data(other.data) {}

    SquareMatrix<T>& operator=(const SquareMatrix<T>& other) {
        if (this == &other)
            return *this; 

        size = other.size;
        data = other.data;
        return *this;
    }

    size_t GetSize() const {
        return size;
    }
    

    SquareMatrix<T> operator+(const SquareMatrix<T>& other) const {
        return Add(other);
    }

    SquareMatrix<T> operator*(const T& scalar) const {
        return MultiplyByScalar(scalar);
    }

    bool operator==(const SquareMatrix<T>& other) const {
        if (size != other.size)
            return false;
        
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                if (Get(i, j) != other.Get(i, j))
                    return false;
            }
        }

        return true;
    }

    bool operator!=(const SquareMatrix<T>& other) const {
        return !(*this == other);
    }

    T& operator()(size_t i, size_t j) {
        CheckBounds(i, j);
        return data[Index(i, j)];
    }

    const T& operator()(size_t i, size_t j) const {
        CheckBounds(i, j);
        return data[Index(i, j)];
    }

    const T& Get(size_t i, size_t j) const {
        return (*this)(i, j);
    }

    void Set(size_t i, size_t j, const T& value) {
        (*this)(i, j) = value;
    }  
    
    SquareMatrix<T> Add(const SquareMatrix<T>& other) const {
        if (other.size != size)
            throw std::invalid_argument("Matrix sizes must match");
        
        SquareMatrix<T> result(size);

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.Set(i, j, Get(i, j) + other.Get(i, j));
            }       
        }

        return result;
    }

    SquareMatrix<T> MultiplyByScalar(const T& scalar) const {
        SquareMatrix<T> result(size);

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.Set(i, j, Get(i, j) * scalar);
            }
        }

        return result;
    }

    SquareMatrix<T> Multiply(const SquareMatrix<T>& other) const {
        if (size != other.size)
            throw std::invalid_argument("Matrix sizes must match");
        
        SquareMatrix<T> result(size, T());

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                T sum = T();
                for (size_t k = 0; k < size; k++) {
                    sum += Get(i, k) * other.Get(k, j);
                }
                result.Set(i, j, sum);
            }
        }

        return result;
    }

    void SwapRows(size_t row1, size_t row2) {
        if (row1 == row2)
            return;
        if (row1 >= size || row2 >= size)
            throw std::out_of_range("Index out of range");
        
        for (size_t j = 0; j < size; j++) {
            T temp = Get(row1, j);
            Set(row1, j, Get(row2, j));
            Set(row2, j, temp);
        }
    }

    void SwapColumns(size_t column1, size_t column2) {
        if (column1 == column2)
            return;
        if (column1 >= size || column2 >= size)
            throw std::out_of_range("Index out of range");
        
        for (size_t i = 0; i < size; i++) {
            T temp = Get(i, column1);
            Set(i, column1, Get(i, column2));
            Set(i, column2, temp);
        }
    }

    double Norm() const {
        double sum = 0.0;

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                double value = static_cast<double>(Get(i, j));
                sum += value * value;
            }
        }

        return std::sqrt(sum);
    }

    SquareMatrix<T> Transpose() const {
        SquareMatrix<T> result(size);

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.Set(j, i, Get(i, j));
            }
        }

        return result;
    }

    double ResidualNorm(const SquareMatrix<double>& A, const MutableArraySequence<double>& x, const MutableArraySequence<double>& b) {
        size_t n = A.GetSize();
        double norm = 0.0;

        for (size_t i = 0; i < n; i++) {
            double sum = 0.0;
            for (size_t j = 0; j < n; j++) {
                sum += A(i, j) * x[j];
            }
            double diff = sum - b[i];
            norm += diff * diff;
        }

        return std::sqrt(norm);
    }
    
    void MultiplyRow(size_t row, const T& scalar) {
        if (row >= size)
            throw std::out_of_range("Index out of range");
        
        for (size_t j = 0; j < size; j++) {
            T value = Get(row, j) * scalar;
            Set(row, j, value);
        }
    }

    void MultiplyColumn(size_t column, const T& scalar) {
        if (column >= size)
            throw std::out_of_range("Index out of range");
        
        for (size_t i = 0; i < size; i++) {
            T value = Get(i, column) * scalar;
            Set(i, column, value);
        }
    }

    void AddRowMultiple(size_t target, size_t source, const T& scalar) {
        if (target >= size || source >= size)
            throw std::out_of_range("Index out of range");
        
        for (size_t j = 0; j < size; j++) {
            T value = Get(target, j) + Get(source, j) * scalar;
            Set(target, j, value);
        }
    }

    void AddColumnMultiple(size_t target, size_t source, const T& scalar) {
        if (target >= size || source >= size) 
            throw std::out_of_range("Index out of range");
        
        for (size_t i = 0; i < size; i++) {
            T value = Get(i, target) + Get(i, source) * scalar;
            Set(i, target, value);
        }
    }

    template<typename Func>
    SquareMatrix<T> Map(Func func) const {
        SquareMatrix<T> result(size, T());

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.Set(i, j, func(Get(i, j)));
            }
        }

        return result;
    }

    template<typename Func>
    T Reduce(Func func, T initial) const {
        T result = initial;

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result = func(result, Get(i, j));
            }
        }
        return result;
    }
 
    //iterator
    auto begin() {
        return data.begin();
    }

    auto end() {
        return data.end();
    }

    auto begin() const {
        return data.begin();
    }

    auto end() const {
        return data.end();
    }
};

#endif /* SQUARE_MATRIX_HPP */
