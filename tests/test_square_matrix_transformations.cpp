#include <gtest/gtest.h>
#include "SquareMatrix.hpp"

TEST(SquareMatrixTest, SwapRowsWorksCorrectly) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 0, 1);
    matrix.Set(0, 1, 2);
    matrix.Set(1, 0, 3);
    matrix.Set(1, 1, 4);
    
    matrix.SwapRows(0, 1);

    EXPECT_EQ(matrix.Get(0, 0), 3);
    EXPECT_EQ(matrix.Get(0, 1), 4);
    EXPECT_EQ(matrix.Get(1, 0), 1);
    EXPECT_EQ(matrix.Get(1, 1), 2);
}

TEST(SquareMatrixTest, SwapRowsThrowsOnInvalidIndex) {
    SquareMatrix<int> matrix(2, 0);

    EXPECT_THROW(matrix.SwapRows(0, 5), std::out_of_range);
}

TEST(SquareMatrixTest, SwapColumnsWorksCorrectly) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 0, 1);
    matrix.Set(0, 1, 2);
    matrix.Set(1, 0, 3);
    matrix.Set(1, 1, 4);

    matrix.SwapColumns(0, 1);

    EXPECT_EQ(matrix.Get(0, 0), 2);
    EXPECT_EQ(matrix.Get(0, 1), 1);
    EXPECT_EQ(matrix.Get(1, 0), 4);
    EXPECT_EQ(matrix.Get(1, 1), 3);
}

TEST(SquareMatrixTest, MultiplyRowWorksCorrectly) {
    SquareMatrix<int> matrix(2, 1);

    matrix.MultiplyRow(0, 5);

    EXPECT_EQ(matrix.Get(0, 0), 5);
    EXPECT_EQ(matrix.Get(0, 1), 5);
    EXPECT_EQ(matrix.Get(1, 0), 1);
    EXPECT_EQ(matrix.Get(1, 1), 1);
}

TEST(SquareMatrixTest, MultiplyColumnWorksCorrectly) {
    SquareMatrix<int> matrix(2, 1);

    matrix.MultiplyColumn(1, 3);

    EXPECT_EQ(matrix.Get(0, 0), 1);
    EXPECT_EQ(matrix.Get(0, 1), 3);
    EXPECT_EQ(matrix.Get(1, 0), 1);
    EXPECT_EQ(matrix.Get(1, 1), 3);
}

TEST(SquareMatrixTest, AddRowMultipleWorksCorrectly) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 0, 1);
    matrix.Set(0, 1, 3);
    matrix.Set(1, 0, 2);
    matrix.Set(1, 1, 4);

    matrix.AddRowMultiple(0, 1, 2);

    EXPECT_EQ(matrix.Get(0, 0), 5);
    EXPECT_EQ(matrix.Get(0, 1), 11);
    EXPECT_EQ(matrix.Get(1, 0), 2);
    EXPECT_EQ(matrix.Get(1, 1), 4);
}

TEST(SquareMatrixTest, AddColumnMultipleWorksCorrectly) {
    SquareMatrix<int> matrix(2, 0);

    matrix.Set(0, 0, 1);
    matrix.Set(0, 1, 2);
    matrix.Set(1, 0, 3);
    matrix.Set(1, 1, 4);

    matrix.AddColumnMultiple(0, 1, 3);

    EXPECT_EQ(matrix.Get(0, 0), 7);
    EXPECT_EQ(matrix.Get(0, 1), 2);
    EXPECT_EQ(matrix.Get(1, 0), 15);
    EXPECT_EQ(matrix.Get(1, 1), 4);
}

TEST(SquareMatrixTest, SwapColumnsThrowsOnInvalidIndex) {
    SquareMatrix<int> matrix(2, 0);

    EXPECT_THROW(matrix.SwapColumns(0, 5), std::out_of_range);
}

TEST(SquareMatrixTest, SwapRowsSameIndexDoesNothing) {
    SquareMatrix<int> matrix(2, 1);

    matrix.SwapRows(0, 0);

    EXPECT_EQ(matrix.Get(0, 0), 1);
    EXPECT_EQ(matrix.Get(0, 1), 1);
    EXPECT_EQ(matrix.Get(1, 0), 1);
    EXPECT_EQ(matrix.Get(1, 1), 1);
}

TEST(SquareMatrixTest, SwapColumnsSameIndexDoesNothing) {
    SquareMatrix<int> matrix(2, 1);

    matrix.SwapColumns(1, 1);

    EXPECT_EQ(matrix.Get(0, 0), 1);
    EXPECT_EQ(matrix.Get(0, 1), 1);
    EXPECT_EQ(matrix.Get(1, 0), 1);
    EXPECT_EQ(matrix.Get(1, 1), 1);
}

TEST(SquareMatrixTest, MultiplyRowThrowsOnInvalidIndex) {
    SquareMatrix<int> matrix(2, 0);

    EXPECT_THROW(matrix.MultiplyRow(5, 2), std::out_of_range);
}

TEST(SquareMatrixTest, MultiplyColumnThrowsOnInvalidIndex) {
    SquareMatrix<int> matrix(2, 0);

    EXPECT_THROW(matrix.MultiplyColumn(5, 2), std::out_of_range);
}

TEST(SquareMatrixTest, AddRowMultipleThrowsOnInvalidIndex) {
    SquareMatrix<int> matrix(2, 0);

    EXPECT_THROW(matrix.AddRowMultiple(0, 5, 2), std::out_of_range);
    EXPECT_THROW(matrix.AddRowMultiple(5, 0, 2), std::out_of_range);
}

TEST(SquareMatrixTest, AddColumnMultipleThrowsOnInvalidIndex) {
    SquareMatrix<int> matrix(2, 0);

    EXPECT_THROW(matrix.AddColumnMultiple(0, 5, 2), std::out_of_range);
    EXPECT_THROW(matrix.AddColumnMultiple(5, 0, 2), std::out_of_range);
}

