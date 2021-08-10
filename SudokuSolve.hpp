#include <array>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iosfwd>

class SudokuSolve {
public:
    using Map = std::array<std::array<int, 9>, 9>;
    //using CharMap = std::array<std::array<char, 9>, 9>;

    using Pos = std::pair<int, int>;
    constexpr static int UNFILLED = -1;

private:
    Map data;
    std::vector<Pos> blanks;
    bool finished = false;

    std::array<std::array<bool, 9>, 9> numers_used_in_box;
    std::array<std::array<bool, 9>, 9> numers_used_in_row;
    std::array<std::array<bool, 9>, 9> numers_used_in_col;

    auto & used_in_row(int row) { return numers_used_in_row[row]; }
    auto & used_in_col(int col) { return numers_used_in_col[col]; }
    auto & used_in_box(int row, int col) {
        auto box_no = ((row / 3) * 3) + col / 3;
        return numers_used_in_box[box_no];
    }
    auto fill_in(int row, int col, int val) {
        used_in_row(row)[val - 1] = true;
        used_in_col(col)[val - 1] = true;
        used_in_box(row, col)[val - 1] = true;
        data[row][col] = val;
    }
    auto unfill(int row, int col) {
        auto val = data[row][col] - 1;
        data[row][col] = UNFILLED;
        used_in_row(row)[val] = false;
        used_in_col(col)[val] = false;
        used_in_box(row, col)[val] = false;
    }
    auto legal(int row, int col, int val) {
        val -= 1;
        return !used_in_row(row)[val] && !used_in_col(col)[val] && !used_in_box(row, col)[val];
    }
    auto DFS_Solve_(std::vector<Pos>::iterator i) {
        if (i == end(blanks)) {
            finished = true;
            return;
        }
        auto [row, col] = *i;
        for (int num = 1; num <= 9; ++num) {
            if (legal(row, col, num)) {
                fill_in(row, col, num);
                DFS_Solve_(i + 1);
                if (finished) break;
                unfill(row, col);
            }
        }
    }
public:
    auto initial(Map const & a) {
        blanks.clear();
        for (int i = 0; i < a.size(); ++i) {
            numers_used_in_box[i].fill(false);
            numers_used_in_row[i].fill(false);
            numers_used_in_col[i].fill(false);
            for (int j = 0; j < a[i].size(); ++j) {
                if (a[i][j] < 1 || a[i][j] > 9) {
                    blanks.push_back({i, j});
                    data[i][j] = UNFILLED;
                } else {
                    fill_in(i, j, a[i][j]);
                }
            }
        }
        finished = false;
    }
    SudokuSolve(Map const & a) {
        initial(a);
    }
    auto reset() {
        if (finished) {
            for (auto pos : blanks) {
                auto [r,c] = pos;
                unfill(r, c);
            }
            finished = false;
        }
    }
    auto get_status() { return data; }
    auto DFS_solve() {
        DFS_Solve_(begin(blanks));
    }

    static auto to_string(Map const & a) {
        std::string out;
        for (auto const & row : a) {
            for (auto const & val : row) {
                out += std::to_string(val) + " ";
            }
            out += "\n";
        }
        return out;
    }

    friend std::ostream & operator<<(std::ostream & os, SudokuSolve s) {
        os << to_string(s.get_status());
        return os;
    }
};
