#include <iostream>
#include "SquareMatrix.hpp"

int main()
{
    SquareMatrix<int> A(2, 10);
    int scalar = 5;
    auto B = A.MultiplyByScalar(scalar);
    std::cout << B.Get(0, 0);
    return 0;
}