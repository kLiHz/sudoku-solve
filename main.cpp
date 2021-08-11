#include <iostream>
#include "SudokuSolve.hpp"

int main() {
    SudokuSolve::Map m;
    for (auto & row : m) {
        for (auto & n : row) {
            std::cin >> n;
        }
    }
    SudokuSolve inst(m);
    inst.DFS_solve();
    std::cout << "\n";
    std::cout << inst;
}
