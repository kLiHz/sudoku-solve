#include "SudokuSolve.hpp"

SudokuSolve::Map SudokuSolve::DFS_solve(const SudokuSolve::Map &a) {
    std::array<std::array<bool, 10>, 9> used_nums_in_row = {{false}};
    std::array<std::array<bool, 10>, 9> used_nums_in_col = {{false}};
    std::array<std::array<bool, 10>, 9> used_nums_in_box = {{false}};

    Map data = {{UNFILLED}};
    PosArray blanks;
    bool finished = false;

    for (int i = 0; i < a.size(); ++i) {
        used_nums_in_box[i].fill(false);
        used_nums_in_row[i].fill(false);
        used_nums_in_col[i].fill(false);
    }

    auto box_no = [](int row, int col) { return ((row / 3) * 3) + (col / 3); };
    auto mark_as_used = [&](int row, int col, int val) {
        used_nums_in_row[row][val] = true;
        used_nums_in_col[col][val] = true;
        used_nums_in_box[box_no(row,col)][val] = true;
    };
    auto unmark_used = [&](int row, int col, int val) {
        used_nums_in_row[row][val] = false;
        used_nums_in_col[col][val] = false;
        used_nums_in_box[box_no(row,col)][val] = false;
    };
    auto legal = [&](int row, int col, int val) {
        return !(used_nums_in_row[row][val] || used_nums_in_col[col][val] || used_nums_in_box[box_no(row,col)][val]);
    };

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            if (a[i][j] < 1 || a[i][j] > 9) {
                blanks.push_back({i, j});
                data[i][j] = UNFILLED;
            } else {
                mark_as_used(i, j, a[i][j]);
                data[i][j] = a[i][j];
            }
        }
    }

    std::function<void(PosArray::iterator)> dfs = [&](PosArray::iterator i){
        if (i == end(blanks)) {
            finished = true;
            return;
        }
        auto [row, col] = *i;
        for (int num = 1; num <= 9; ++num) {
            if (legal(row, col, num)) {
                data[row][col] = num;
                mark_as_used(row, col, num);
                dfs(i + 1);
                if (finished) break;
                unmark_used(row, col, num);
            }
        }
    };

    dfs(begin(blanks));

    return data;
}

std::string SudokuSolve::to_string(const SudokuSolve::Map &a) {
    std::string out;
    for (auto const & row : a) {
        for (auto const & val : row) {
            out += std::to_string(val) + " ";
        }
        out += "\n";
    }
    return out;
}
