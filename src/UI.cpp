#include <iostream>
#include <string>
#include <limits>
#include "SquareMatrix.hpp"
#include "UI.hpp"

namespace {
    void ClearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    size_t ReadSize(const std::string& text) {
        size_t value;
        while (true) {
            std::cout << text;
            if (std::cin >> value && value > 0) {
                return value;
            }
            std::cout << "Input error. Enter a positive integer\n";
            ClearInput();
        }
    }

    double ReadDouble(const std::string& text) {
        double value;
        while (true) {
            std::cout << text;
            if (std::cin >> value) {
                return value;
            }
            std::cout << "Input error. Enter a number\n";
            ClearInput();
        }
    }

    size_t ReadIndex(const std::string& text) {
        size_t value;
        while (true) {
            std::cout << text;
            if (std::cin >> value) {
                return value;
            }
            std::cout << "Input error. Enter a non-negative integer\n";
            ClearInput();
        }
    }

    void PrintMenu() {
        std::cout << "\n-----Square Matrix UI-----\n";
        std::cout << '\n';
        std::cout << "1) Create Matrix A\n";
        std::cout << "2) Create Matrix B\n";
        std::cout << "3) Fill matrix A\n";
        std::cout << "4) Fill matrix B\n";
        std::cout << "5) Print matrix A\n";
        std::cout << "6) Print matrix B\n";
        std::cout << "7) Add matrices (A + B)\n";
        std::cout << "8) Multiply matrix A by scalar\n";
        std::cout << "9) Multiply matrices (A * B)\n";
        std::cout << "10) Transpose matrix A\n";
        std::cout << "11) Swap rows in matrix A\n";
        std::cout << "12) Swap columns in matrix A\n";
        std::cout << "13) Compute norm of matrix A\n";
        std::cout << "14) Auto demo\n";
        std::cout << "15) Multiply row in matrix A by scalar\n";
        std::cout << "16) Multiply column in matrix A by scalar\n";
        std::cout << "17) Add row multiple in matrix A\n";
        std::cout << "18) Add column multiple in matrix A\n";
        std::cout << "0) Exit\n";
    }

    void PrintMatrix(const SquareMatrix<double>& matrix) {
        size_t n = matrix.GetSize();
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                std::cout << matrix.Get(i, j) << ' ';
            }
            std::cout << std::endl;
        }
    }

    void FillMatrix(SquareMatrix<double>& matrix) {
        size_t n = matrix.GetSize();
        double value;
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                value = ReadDouble("Enter element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");
                matrix.Set(i, j, value);
            }
        }
    }

    void AutoDemo() {
        std::cout << "\nAuto Demo\n";

        SquareMatrix<double> a(2, 0.0);
        SquareMatrix<double> b(2, 0.0);

        a.Set(0, 0, 1);
        a.Set(0, 1, 2);
        a.Set(1, 0, 3);
        a.Set(1, 1, 4);

        b.Set(0, 0, 5);
        b.Set(0, 1, 6);
        b.Set(1, 0, 7);
        b.Set(1, 1, 8);

        std::cout << "\nMatrix A:\n";
        PrintMatrix(a);

        std::cout << "\nMatrix B:\n";
        PrintMatrix(b);

        SquareMatrix<double> sum = a + b;
        std::cout << "\nA + B:\n";
        PrintMatrix(sum);

        SquareMatrix<double> product = a.Multiply(b);
        std::cout << "\nA * B:\n";
        PrintMatrix(product);

        SquareMatrix<double> transposed = a.Transpose();
        std::cout << "\nTranspose(A):\n";
        PrintMatrix(transposed);

        a.SwapRows(0, 1);
        std::cout << "\nA after SwapRows(0, 1):\n";
        PrintMatrix(a);

        a.MultiplyColumn(1, 2.0);
        std::cout << "\nA after MultiplyColumn(1, 2):\n";
        PrintMatrix(a);

        std::cout << "\nNorm(A): " << a.Norm() << '\n';

        std::cout << "\nEnd of Demo\n";
    }

} //namespace

void StartUi() {
    SquareMatrix<double> matrixA; 
    SquareMatrix<double> matrixB;
    
    bool hasA = false;
    bool hasB = false;

    int command = -1;

    while (true) {
        PrintMenu();
        std::cout << "Choose command: ";
    
        if (!(std::cin >> command)) {
            std::cout << "Input error\n";
            ClearInput();
            continue;
        }
        try {
            switch (command) {
                case 1: {
                    size_t n = ReadSize("Enter size of Matrix A: ");
                    matrixA = SquareMatrix<double>(n, 0.0);
                    hasA = true;
                    std::cout << "Matrix A created\n";
                    break;
                } 

                case 2: {
                    size_t n = ReadSize("Enter size of Matrix B: ");
                    matrixB = SquareMatrix<double>(n, 0.0);
                    hasB = true;
                    std::cout << "Matrix B created\n";
                    break;
                }

                case 3: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    FillMatrix(matrixA);
                    std::cout << "Matrix A filled\n";
                    break;
                }

                case 4: {
                    if (!hasB) {
                        std::cout << "Matrix B is not created\n";
                        break;
                    }
                    FillMatrix(matrixB);
                    std::cout << "Matrix B filled\n";
                    break;
                }

                case 5: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    std::cout << "Matrix A:\n";
                    PrintMatrix(matrixA);
                    break;
                }

                case 6: {
                    if (!hasB) {
                        std::cout << "Matrix B is not created\n";
                        break;
                    }
                    std::cout << "Matrix B:\n";
                    PrintMatrix(matrixB);
                    break;
                }

                case 7: {
                    if (!hasA || !hasB) {
                        std::cout << "Both matrices must be created\n";
                        break;
                    }

                    SquareMatrix<double> result = matrixA + matrixB;
                    std::cout << "Result A + B:\n";
                    PrintMatrix(result);
                    break;
                }

                case 8: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    double scalar = ReadDouble("Enter scalar: ");
                    SquareMatrix<double> result = matrixA * scalar;
                    std::cout << "Result A * scalar:\n";
                    PrintMatrix(result);
                    break;
                }

                case 9: {
                    if (!hasA || !hasB) {
                        std::cout << "Both matrices must be created\n";
                        break;
                    }
                    SquareMatrix<double> result = matrixA.Multiply(matrixB);
                    std::cout << "Result A * B:\n";
                    PrintMatrix(result);
                    break;
                }

                case 10: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    SquareMatrix<double> result = matrixA.Transpose();
                    std::cout << "Transpose(A):\n";
                    PrintMatrix(result);
                    break;
                }
                
                case 11: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    size_t row1 = ReadIndex("Enter first row index: ");
                    size_t row2 = ReadIndex("Enter second row index: ");
                    matrixA.SwapRows(row1, row2);
                    std::cout << "Rows swapped. Matrix A:\n";
                    PrintMatrix(matrixA);
                    break;
                }

                case 12: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    size_t col1 = ReadIndex("Enter first column index: ");
                    size_t col2 = ReadIndex("Enter second column index: ");
                    matrixA.SwapColumns(col1, col2);
                    std::cout << "Columns swapped. Matrix A:\n";
                    PrintMatrix(matrixA);
                    break;
                }

                case 13: {
                    if (!hasA) { 
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    std::cout << "Norm(A): " << matrixA.Norm() << '\n';
                    break;
                }

                case 14: {
                    AutoDemo();
                    break;
                }

                case 15: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    size_t row = ReadIndex("Enter row index: ");
                    double scalar = ReadDouble("Enter scalar: ");
                    matrixA.MultiplyRow(row, scalar);
                    std::cout << "Row multiplied. Matrix A:\n";
                    PrintMatrix(matrixA);
                    break;
                }

                case 16: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    size_t column = ReadIndex("Enter column index: ");
                    double scalar = ReadDouble("Enter scalar: ");
                    matrixA.MultiplyColumn(column, scalar);
                    std::cout << "Column multiplied. Matrix A:\n";
                    PrintMatrix(matrixA);
                    break;
                }

                case 17: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    size_t target = ReadIndex("Enter target row index: ");
                    size_t source = ReadIndex("Enter source row index: ");
                    double scalar = ReadDouble("Enter scalar: ");
                    matrixA.AddRowMultiple(target, source, scalar);
                    std::cout << "Row combination added. Matrix A:\n";
                    PrintMatrix(matrixA);
                    break;
                }

                case 18: {
                    if (!hasA) {
                        std::cout << "Matrix A is not created\n";
                        break;
                    }
                    size_t target = ReadIndex("Enter target column index: ");
                    size_t source = ReadIndex("Enter source column index: ");
                    double scalar = ReadDouble("Enter scalar: ");
                    matrixA.AddColumnMultiple(target, source, scalar);
                    std::cout << "Column combination added. Matrix A:\n";
                    PrintMatrix(matrixA);
                    break;
                }

                case 0: 
                    std::cout << "Exit\n";
                    return;
                
                default: 
                    std::cout << "Unknown command\n";
                    break;
            }
        } // try

        catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << '\n';
        }
    }
}