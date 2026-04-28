#ifndef LU_SOLVER_HPP
#define LU_SOLVER_HPP

#include "LinearSystemSolver.hpp"
#include "Utility.hpp"
#include <cmath>
#include <stdexcept>

template<typename T>
class LUSolver : public LinearSystemSolver<T> {
private:
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

    Vector<T> LUSolve(const SquareMatrix<T>& A, const Vector<T>& b) const {
        SquareMatrix<T> L, U;
        LUDecomposition(A, L, U);

        Vector<T> y = ForwardSubstitution(L, b);
        Vector<T> x = BackSubstitution(U, y);

        return x;
    }

public: 
    Vector<T> Solve(const SquareMatrix<T>& A, const Vector<T>& b) const override {
        return LUSolve(A, b);
    }

    const char* Name() const override {
        return "LU";
    }
};

#endif /* LU_SOLVER_HPP */
