#include <gtest/gtest.h>
#include "SquareMatrix.hpp"

TEST(SquareMatrixTest, AddWorksCorrectly) {
    SquareMatrix<int> a(2, 0);
    SquareMatrix<int> b(2, 0);

    a.Set(0, 0, 1);
    a.Set(0, 1, 2);
    a.Set(1, 0, 3);
    a.Set(1, 1, 4);

    b.Set(0, 0, 10);
    b.Set(0, 1, 20);
    b.Set(1, 0, 30);
    b.Set(1, 1, 40);

    SquareMatrix<int> result = a.Add(b);
    EXPECT_EQ(result.Get(0, 0), 11);
    EXPECT_EQ(result.Get(0, 1), 22);
    EXPECT_EQ(result.Get(1, 0), 33);
    EXPECT_EQ(result.Get(1, 1), 44);
}

TEST(SquareMatrixTest, AddThrowsWhenSizesDoNotMatch) {
    SquareMatrix<int> a(2, 1);
    SquareMatrix<int> b(3, 1);

    EXPECT_THROW(a.Add(b), std::invalid_argument);
}

TEST(SquareMatrixTest, MultiplyByScalarWorksCorrectly) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 0, 1);
    matrix.Set(0, 1, 2);
    matrix.Set(1, 0, 3);
    matrix.Set(1, 1, 4);

    SquareMatrix<int> result = matrix.MultiplyByScalar(3);

    EXPECT_EQ(result.Get(0, 0), 3);
    EXPECT_EQ(result.Get(0, 1), 6);
    EXPECT_EQ(result.Get(1, 0), 9);
    EXPECT_EQ(result.Get(1, 1), 12);
}

TEST(SquareMatrixTest, MultiplyByScalarZero) {
    SquareMatrix<int> matrix(2, 5);

    SquareMatrix<int> result = matrix.MultiplyByScalar(0);

    EXPECT_EQ(result.Get(0, 0), 0);
    EXPECT_EQ(result.Get(0, 1), 0);
    EXPECT_EQ(result.Get(1, 0), 0);
    EXPECT_EQ(result.Get(1, 1), 0);
}

TEST(SquareMatrixTest, MultiplyByScalarNegative) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 0, -1);
    matrix.Set(0, 1, 2);
    matrix.Set(1, 0, 3);
    matrix.Set(1, 1, -4);
    SquareMatrix<int> result = matrix.MultiplyByScalar(-2);

    EXPECT_EQ(result.Get(0, 0), 2);
    EXPECT_EQ(result.Get(0, 1), -4);
    EXPECT_EQ(result.Get(1, 0), -6);
    EXPECT_EQ(result.Get(1, 1), 8);
}

TEST(SquareMatrixTest, MultiplyWorksCorrectly) {
    SquareMatrix<int> a(2, 0);
    SquareMatrix<int> b(2, 0);

    a.Set(0, 0, 1);
    a.Set(0, 1, 2);
    a.Set(1, 0, 3);
    a.Set(1, 1, 4);

    b.Set(0, 0, 5);
    b.Set(0, 1, 6);
    b.Set(1, 0, 7);
    b.Set(1, 1, 8);

    SquareMatrix<int> result = a.Multiply(b);

    EXPECT_EQ(result.Get(0, 0), 19);
    EXPECT_EQ(result.Get(0, 1), 22);
    EXPECT_EQ(result.Get(1, 0), 43);
    EXPECT_EQ(result.Get(1, 1), 50);
}

TEST(SquareMatrixTest, MultiplyThrowsWhenSizesDoNotMatch) {
    SquareMatrix<int> a(2, 0);
    SquareMatrix<int> b(3, 0);

    EXPECT_THROW(a.Multiply(b), std::invalid_argument);
}

TEST(SquareMatrixTest, TransposeWorksCorrectly) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 0, 1);
    matrix.Set(0, 1, 5);
    matrix.Set(1, 0, 7);
    matrix.Set(1, 1, 2);

    SquareMatrix<int> transpose_matrix = matrix.Transpose();

    EXPECT_EQ(transpose_matrix.Get(0, 0), 1);
    EXPECT_EQ(transpose_matrix.Get(0, 1), 7);
    EXPECT_EQ(transpose_matrix.Get(1, 0), 5);
    EXPECT_EQ(transpose_matrix.Get(1, 1), 2);
}

TEST(SquareMatrixTest, NormWorksCorrectly) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 0, 3);
    matrix.Set(1, 1, 4);

    double norm = matrix.Norm();

    EXPECT_NEAR(norm, 5.0, 1e-9);
}

TEST(SquareMatrixTest, OperatorPlusWorksCorrectly) {
    SquareMatrix<int> a(2, 1);
    SquareMatrix<int> b(2, 2);

    SquareMatrix<int> result = a + b;
    
    EXPECT_EQ(result.Get(0, 0), 3);
    EXPECT_EQ(result.Get(0, 1), 3);
    EXPECT_EQ(result.Get(1, 0), 3);
    EXPECT_EQ(result.Get(1, 1), 3);
}

TEST(SquareMatrixTest, OperatorMultiplyByScalarWorksCorrectly) {
    SquareMatrix<int> matrix(2, 2);

    SquareMatrix<int> result = matrix * 3;

    EXPECT_EQ(result.Get(0, 0), 6);
    EXPECT_EQ(result.Get(0, 1), 6);
    EXPECT_EQ(result.Get(1, 0), 6);
    EXPECT_EQ(result.Get(1, 1), 6);
}

TEST(SquareMatrixTest, OperatorEqualityWorksCorrectly) {
    SquareMatrix<int> a(2, 5);
    SquareMatrix<int> b(2, 5);

    EXPECT_TRUE(a == b);

    b.Set(0, 0, 10);

    EXPECT_FALSE(a == b);
}

TEST(SquareMatrixTest, OperatorEqualityReturnsFalseForDifferentSizes) {
    SquareMatrix<int> a(2, 1);
    SquareMatrix<int> b(3, 1);

    EXPECT_FALSE(a == b);
}

TEST(SquareMatrixTest, TransposeTwiceReturnsOriginal) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 1, 5);
    matrix.Set(1, 0, 7);

    SquareMatrix<int> result = matrix.Transpose().Transpose();

    EXPECT_TRUE(matrix == result);
}

