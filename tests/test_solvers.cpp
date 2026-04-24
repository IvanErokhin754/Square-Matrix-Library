#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "SquareMatrix.hpp"
#include "GaussSolver.hpp"
#include "LUSolver.hpp"
#include "Utility.hpp"

TEST(GaussSolverTest, SolvesSimple2x2System) {
    SquareMatrix<double> A(2, 0.0);
    MutableArraySequence<double> b;

    b.Append(5.0);
    b.Append(7.0);

    A(0, 0) = 2.0; A(0, 1) = 1.0;
    A(1, 0) = 1.0; A(1, 1) = 3.0;

    GaussSolver<double> solver;
    MutableArraySequence<double> x = solver.Solve(A, b);

    EXPECT_NEAR(x[0], 1.6, 1e-9);
    EXPECT_NEAR(x[1], 1.8, 1e-9);
}

TEST(LUSolverTest, SolvesSimple2x2System) {
    SquareMatrix<double> A(2, 0.0);
    MutableArraySequence<double> b;

    b.Append(5.0);
    b.Append(7.0);

    A(0, 0) = 2.0; A(0, 1) = 1.0;
    A(1, 0) = 1.0; A(1, 1) = 3.0;

    LUSolver<double> solver;
    MutableArraySequence<double> x = solver.Solve(A, b);

    EXPECT_NEAR(x[0], 1.6, 1e-9);
    EXPECT_NEAR(x[1], 1.8, 1e-9);
}

TEST(SolverComparisonTest, GaussAndLUGiveSameResult) {
    SquareMatrix<double> A(3, 0.0);
    MutableArraySequence<double> b;
    
    A(0, 0) = 2.0; A(0, 1) = 1.0; A(0, 2) = -1.0;
    A(1, 0) = -3.0; A(1, 1) = -1.0; A(1, 2) = 2.0;
    A(2, 0) = -2.0; A(2, 1) = 1.0; A(2, 2) = 2.0;

    b.Append(8.0);
    b.Append(-11.0);
    b.Append(-3.0);

    GaussSolver<double> gauss;
    LUSolver<double> lu;

    auto xGauss = gauss.Solve(A, b);
    auto xLU = lu.Solve(A, b);

    EXPECT_NEAR(xGauss[0], xLU[0], 1e-9);
    EXPECT_NEAR(xGauss[1], xLU[1], 1e-9);
    EXPECT_NEAR(xGauss[2], xLU[2], 1e-9);
    
    EXPECT_NEAR(xGauss[0], 2.0, 1e-9);
    EXPECT_NEAR(xGauss[1], 3.0, 1e-9);
    EXPECT_NEAR(xGauss[2], -1.0, 1e-9);
}

TEST(SolverTest, SingularMatrixThrows) {
    SquareMatrix<double> A(2, 0.0);
    MutableArraySequence<double> b;

    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 2; A(1, 1) = 4;

    b.Append(3);
    b.Append(6);

    GaussSolver<double> gauss;
    LUSolver<double> lu;

    EXPECT_THROW(gauss.Solve(A, b), std::runtime_error);
    EXPECT_THROW(lu.Solve(A, b), std::runtime_error);
}

TEST(SolverTest, WrongSizeThrows) {
    SquareMatrix<double> A(2, 0.0);
    MutableArraySequence<double> b;

    b.Append(1.0);

    GaussSolver<double> gauss;

    EXPECT_THROW(gauss.Solve(A, b), std::invalid_argument);
}

TEST(SolverTest, ResidualIsSmall) {
    SquareMatrix<double> A(3, 0.0);
    MutableArraySequence<double> b;

    A(0, 0) = 2; A(0, 1) = 1; A(0, 2) = -1;
    A(1, 0) = -3; A(1, 1) = -1; A(1, 2) = 2;
    A(2, 0) = -2; A(2, 1) = 1; A(2, 2) = 2;

    b.Append(8);
    b.Append(-11);
    b.Append(-3);

    GaussSolver<double> solver;
    auto x = solver.Solve(A, b);
    double r = ResidualNorm(A, x, b);

    EXPECT_NEAR(r, 0.0, 1e-9);
}