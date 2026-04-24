#ifndef GAUSS_SOLVER_HPP
#define GAUSS_SOLVER_HPP

#include <cmath>
#include <stdexcept>
#include "LinearSystemSolver.hpp"

template<typename T>
class GaussSolver : public LinearSystemSolver<T> {
private:
    static constexpr double eps = 1e-12;
    MutableArraySequence<T> BackSubstitution(const SquareMatrix<T>& U, const MutableArraySequence<T>& b) const {
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
