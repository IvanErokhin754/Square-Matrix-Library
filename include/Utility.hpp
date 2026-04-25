#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cmath>
#include <cstddef>
#include "SquareMatrix.hpp"
#include "MutableArraySequence.hpp"

static constexpr double eps = 1e-12;

template<typename T>
MutableArraySequence<T> ForwardSubstitution(const SquareMatrix<T>& L, const MutableArraySequence<T>& b) {
    size_t n = L.GetSize();

    if (n == 0)
        throw std::invalid_argument("Matrix must not be empty");

    if (b.GetLength() != n)
        throw std::invalid_argument("Wrong right-hand side size!");
    
    MutableArraySequence<T> y;

    for (size_t i = 0; i < n; i++) {
        y.Append(T());
    }

    for (size_t i = 0; i < n; i++) {
        T sum = T();

        for (size_t j = 0; j < i; j++) {
            sum += L(i, j) * y[j];
        }

        T diag = L(i, i);

        if (std::fabs(static_cast<double>(diag)) < eps)
            throw std::runtime_error("Zero diagonal during forward substitution");

        y[i] = (b[i] - sum) / diag;
    }
    
    return y;
}

template<typename T>
MutableArraySequence<T> BackSubstitution(const SquareMatrix<T>& U, const MutableArraySequence<T>& b) {
    size_t n = U.GetSize();
    if (n == 0)
        throw std::invalid_argument("Matrix must not be empty");

    if (b.GetLength() != n)
        throw std::invalid_argument("Wrong right-hand side size");
    
    MutableArraySequence<T> x;
    for (size_t i = 0; i < n; i++) {
        x.Append(T());
    } 

    for (int i = static_cast<int>(n) - 1; i >= 0; i--) {
        T sum = T();

        for (size_t j = i + 1; j < n; j++) {
            sum += U(i, j) * x[j];
        }

        T diag = U(i, i);

        if (std::fabs(static_cast<double>(diag)) < eps)
            throw std::runtime_error("Zero diagonal during back substitution");
        
        x[i] = (b[i] - sum) / diag;
    }
    
    return x;
}

template<typename T>
T ResidualNorm(const SquareMatrix<T>& A, const MutableArraySequence<T>& x, const MutableArraySequence<T>& b) {
    size_t n = A.GetSize();
    T norm = T();

    for (size_t i = 0; i < n; i++) {
        T sum = T();
        for (size_t j = 0; j < n; j++) {
            sum += A(i, j) * x[j];
        }
        T diff = sum - b[i];
        norm += diff * diff;
    }

    return std::sqrt(norm);
}

#endif /* UTILITY_HPP */
