#include <iostream>
#include <chrono>
#include "SudokuSolve.hpp"

int main() {
    SudokuSolve::Map m;
    for (auto & row : m) {
        for (auto & n : row) {
            std::cin >> n;
        }
    }

    std::chrono::steady_clock sc;

    auto start = sc.now();
    auto result = SudokuSolve::DFS_solve(m);
    auto end = sc.now();

    auto time_span = static_cast<std::chrono::duration<double>>(end - start);
    std::cout << "operation took: " << time_span.count() << " seconds." << std::endl;

    std::cout << "\n" << SudokuSolve::to_string(result);
}
