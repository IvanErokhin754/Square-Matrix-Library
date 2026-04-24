#ifndef LINEAR_SYSTEM_SOLVER_HPP
#define LINEAR_SYSTEM_SOLVER_HPP

#include "SquareMatrix.hpp"
#include "MutableArraySequence.hpp"

template<typename T>
class LinearSystemSolver {
public:
    virtual MutableArraySequence<T> Solve(const SquareMatrix<T>& A, const MutableArraySequence<T>& b) const = 0;
    
    virtual const char* Name() const = 0;

    virtual ~LinearSystemSolver() = default;
};



#endif /* LINEAR_SYSTEM_SOLVER_HPP */
