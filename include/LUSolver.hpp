#ifndef LU_SOLVER_HPP
#define LU_SOLVER_HPP

#include "LinearSystemSolver.hpp"
#include <cmath>
#include <stdexcept>

template<typename T>
class LUSolver : public LinearSystemSolver<T> {
private:
    static constexpr double eps = 1e-12;
    MutableArraySequence<T> ForwardSubstitution(const SquareMatrix<T>& L, const MutableArraySequence<T>& b) const {
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

    void LUDecomposition(const SquareMatrix<T>& A, SquareMatrix<T>& L, SquareMatrix<T>& U) const {
        size_t n = A.GetSize();

        if (n == 0)
            throw std::invalid_argument("Matrix must not be empty");

        L = SquareMatrix<T>(n, T());
        U = A;

        for (size_t i = 0; i < n; i++) {
            L(i, i) = T(1);
        }

        for (size_t k = 0; k < n - 1; k++) {
            T pivot = U(k, k);

            if (std::fabs(static_cast<double>(pivot)) < eps)
                throw std::runtime_error("Zero pivot in LU decomposition");

            for (size_t i = k + 1; i < n; i++) {
                T factor = U(i, k) / pivot;

                L(i, k) = factor;
                U.AddRowMultiple(i, k, -factor);
            }
        }
    }

    MutableArraySequence<T> LUSolve(const SquareMatrix<T>& A, const MutableArraySequence<T>& b) const {
        SquareMatrix<T> L, U;
        LUDecomposition(A, L, U);

        MutableArraySequence<T> y = ForwardSubstitution(L, b);
        MutableArraySequence<T> x = BackSubstitution(U, y);

        return x;
    }

public: 
    MutableArraySequence<T> Solve(const SquareMatrix<T>& A, const MutableArraySequence<T>& b) const override {
        return LUSolve(A, b);
    }

    const char* Name() const override {
        return "LU";
    }
};

#endif /* LU_SOLVER_HPP */
