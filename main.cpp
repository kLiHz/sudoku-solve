#include <iostream>
#include "SudokuSolve.hpp"

class Solution {
public:
    void solveSudoku(std::vector<std::vector<char>>& board) {
        SudokuSolver::Map m;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                m[i][j] = (board[i][j] - '0');
            }
        }
        SudokuSolver inst(m);
        inst.DFS_solve();
        m = inst.get_status();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = (m[i][j] + '0');
            }
        }
    }
};

int main() {
    SudokuSolver::Map m;
    for (auto & row : m) {
        for (auto & n : row) {
            std::cin >> n;
        }
    }
    SudokuSolver inst(m);
    inst.DFS_solve();
    std::cout << "\n";
    std::cout << inst;
}
