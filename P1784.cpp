#include <iostream>
#include "SudokuSolve.hpp"

int main() {
    SudokuSolve::Map m;
    for (auto & row : m) {
        for (auto & n : row) {
            std::cin >> n;
        }
    }
    auto result = SudokuSolve::DFS_solve(m);
    std::cout << "\n" << SudokuSolve::to_string(result);
}
