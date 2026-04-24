#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cmath>
#include <cstddef>
#include "SquareMatrix.hpp"
#include "MutableArraySequence.hpp"

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

#endif /* UTILITY_HPP */
