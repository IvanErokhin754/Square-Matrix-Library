#ifndef GAUSS_SOLVER_HPP
#define GAUSS_SOLVER_HPP

#include <cmath>
#include <stdexcept>
#include "LinearSystemSolver.hpp"
#include "Utility.hpp"

template<typename T>
class GaussSolver : public LinearSystemSolver<T> {
public:
    MutableArraySequence<T> Solve(const SquareMatrix<T>& A, const MutableArraySequence<T>& b) const override {
        size_t n = A.GetSize();
        if (n == 0)
            throw std::invalid_argument("Matrix must not be empty");

        if (b.GetLength() != n)
            throw std::invalid_argument("Wrong right-hand side size");
        
        SquareMatrix<T> tempA(A);
        MutableArraySequence<T> tempB(b);

        for (size_t k = 0; k < n - 1; k++) {
            size_t pivotRow = k;

            for (size_t i = k + 1; i < n; i++) {
                if (std::fabs(static_cast<double>(tempA(i, k))) > std::fabs(static_cast<double>(tempA(pivotRow, k)))) {
                    pivotRow = i; 
                }
            }

            if (pivotRow != k) {
                tempA.SwapRows(k, pivotRow);
                T tmp = tempB[k];
                tempB[k] = tempB[pivotRow];
                tempB[pivotRow] = tmp;
            }

            T pivot = tempA(k, k);

            if (std::fabs(static_cast<double>(pivot)) < eps)
                throw std::runtime_error("Zero pivot in Gauss method");
            
            for (size_t i = k + 1; i < n; i++) {
                T factor = tempA(i, k) / pivot;

                tempA.AddRowMultiple(i, k, -factor);
                tempB[i] -= factor * tempB[k];
            }
        }

        return BackSubstitution(tempA, tempB);
    }

    const char* Name() const override {
        return "Gauss";
    }
};

#endif /* GAUSS_SOLVER_HPP */
