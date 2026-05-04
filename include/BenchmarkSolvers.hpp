#ifndef BENCHMARK_SOLVERS_HPP
#define BENCHMARK_SOLVERS_HPP

#include <iostream>
#include <chrono>
#include "SquareMatrix.hpp"
#include "Vector.hpp"
#include "GaussSolver.hpp"
#include "LUSolver.hpp"

SquareMatrix<double> CreateTestMatrix(size_t n) {
    SquareMatrix<double> A(n, 0.0);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i == j)
                A(i, j) = static_cast<double>(n * 2);
            else
                A(i, j) = 1.0;
        }
    }

    return A;
}

Vector<double> CreateTestVector(size_t n) {
    Vector<double> b;

    for (size_t i = 0; i < n; i++) {
        b.Append(static_cast<double>(i + 1));
    }
    
    return b;

}


template<typename Solver>
long long MeasureTime(const Solver& solver, const SquareMatrix<double>& A, const Vector<double>& b, size_t repeat_count) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < repeat_count; i++) {
        volatile auto x = solver.Solve(A, b);
    }

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

 
void RunSolverBenchMark() {
    size_t n = 50;
    size_t repeat_count = 100;

    SquareMatrix<double> A = CreateTestMatrix(n);
    Vector<double> b = CreateTestVector(n);

    GaussSolver<double> gauss;
    LUSolver<double> lu;

    long long gauss_time = MeasureTime(gauss, A, b, repeat_count);
    long long lu_time = MeasureTime(lu, A, b, repeat_count);
    long long diff = gauss_time - lu_time;

    double gauss_seconds = gauss_time / 1'000'000.0;
    double lu_seconds = lu_time / 1'000'000.0;
    double diff_seconds = diff / 1'000'000.0;
    

    std::cout << "Matrix size: " << n << "x" << n << std::endl;
    std::cout << "Repeat count: " << repeat_count << std::endl;

    std::cout << "Gauss time: " << gauss_time << " us" << " (" << gauss_seconds << "s) \n";
    std::cout << "LU time: " << lu_time << " us" << " (" << lu_seconds << "s) \n";
    std::cout << "Difference: " << diff << " us" << " (" << diff_seconds << " s)\n";

    if (lu_time < gauss_time) {
        double speedup = static_cast<double>(gauss_time) / lu_time;
        std::cout << "LU is faster by " << speedup << "x\n";
    } 
    else if (gauss_time < lu_time) {
        double speedup = static_cast<double>(lu_time) / gauss_time;
        std::cout << "Gauss is faster by " << speedup << "x\n";
    } 
    else {
        std::cout << "Times are equal\n";
    }
}

#endif /* BENCHMARK_SOLVERS_HPP */