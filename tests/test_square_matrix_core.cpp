#include <gtest/gtest.h>
#include "SquareMatrix.hpp"

TEST(SquareMatrixTest, ConstructorFillsMatrixWithDefaultValue) {
    SquareMatrix<int> matrix(2, 7);

    EXPECT_EQ(matrix.Get(0, 0), 7);
    EXPECT_EQ(matrix.Get(0, 1), 7);
    EXPECT_EQ(matrix.Get(1, 0), 7);
    EXPECT_EQ(matrix.Get(1, 1), 7);
}

TEST(SquareMatrixTest, SetAndGetWorkCorrectly) {
    SquareMatrix<int> matrix(3, 0);

    matrix.Set(1, 2, 5);

    EXPECT_EQ(matrix.Get(1, 2), 5);
    EXPECT_EQ(matrix.Get(0, 1), 0);
    EXPECT_EQ(matrix.Get(1, 0), 0);
    EXPECT_EQ(matrix.Get(0, 0), 0);
}

TEST(SquareMatrixTest, SetThrowsOnInvalidIndex) {
    SquareMatrix<int> matrix(2, 0);

    EXPECT_THROW(matrix.Set(2, 0, 1), std::out_of_range);
    EXPECT_THROW(matrix.Set(0, 2, 1), std::out_of_range);
}

TEST(SquareMatrixTest, GetThrowsOnInvalidIndex) {
    SquareMatrix<int> matrix(2, 0);

    EXPECT_THROW(matrix.Get(2, 0), std::out_of_range);
    EXPECT_THROW(matrix.Get(0, 2), std::out_of_range);
}

TEST(SquareMatrixTest, CopyConstructorCreatesIndependentCopy) {
    SquareMatrix<int> matrix1(2, 1);
    matrix1.Set(0, 1, 9);

    SquareMatrix<int> matrix2(matrix1);
    matrix2.Set(0, 1, 100);

    EXPECT_EQ(matrix1.Get(0, 1), 9);
    EXPECT_EQ(matrix2.Get(0, 1), 100);
}

TEST(SquareMatrixTest, AssignmentOperatorCreatesIndependentCopy) {
    SquareMatrix<int> matrix1(2, 3);
    matrix1.Set(1, 1, 8);

    SquareMatrix<int> matrix2(2, 0);
    matrix2 = matrix1;
    matrix2.Set(1, 1, 50);

    EXPECT_EQ(matrix1.Get(1, 1), 8);
    EXPECT_EQ(matrix2.Get(1, 1), 50);
}

TEST(SquareMatrixTest, SelfAssignmentDoesNotBreakMatrix) {
    SquareMatrix<int> matrix(2, 1);
    matrix.Set(0, 1, 5);

    matrix = matrix;

    EXPECT_EQ(matrix.Get(0, 0), 1);
    EXPECT_EQ(matrix.Get(0, 1), 5);
    EXPECT_EQ(matrix.Get(1, 0), 1);
    EXPECT_EQ(matrix.Get(1, 1), 1);
}