#include <iostream>
#include "SudokuSolve.hpp"

int main() {
    while (true) {
        std::string s;
        std::cin >> s;
        if (s == "end") break;
        SudokuSolve::CharMap char_map;
        auto i = begin(s);
        for (auto & row : char_map) {
            for (auto & ch : row) {
                ch = *i; ++i;
            }
        }
        auto result = SudokuSolve::to_CharMap(SudokuSolve::DFS_solve(SudokuSolve::to_Map(char_map)));
        for (auto const & r : result) {
            std::cout << std::string_view(r.data(), r.size());
        }
        std::cout << "\n";
    }
}
