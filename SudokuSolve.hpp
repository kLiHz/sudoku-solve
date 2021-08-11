#include <array>
#include <vector>
#include <string>
#include <iosfwd>

class SudokuSolve {
public:
    using Map = std::array<std::array<int, 9>, 9>;
    //using CharMap = std::array<std::array<char, 9>, 9>;

    using Pos = std::pair<int, int>;
    constexpr static int UNFILLED = 0;

private:
    Map data;
    std::vector<Pos> blanks;
    bool finished = false;

    std::array<std::array<bool, 10>, 9> used_nums_in_row;
    std::array<std::array<bool, 10>, 9> used_nums_in_col;
    std::array<std::array<bool, 10>, 9> used_nums_in_box;

    auto mark_as_used(int row, int col, int val) {
        used_nums_in_row[row][val] = true;
        used_nums_in_col[col][val] = true;
        auto box_no = ((row / 3) * 3) + (col / 3);
        used_nums_in_box[box_no][val] = true;
    }
    auto unmark_used(int row, int col, int val) {
        used_nums_in_row[row][val] = false;
        used_nums_in_col[col][val] = false;
        auto box_no = ((row / 3) * 3) + (col / 3);
        used_nums_in_box[box_no][val] = false;
    }
    auto legal(int row, int col, int val) {
        auto box_no = ((row / 3) * 3) + (col / 3);
        return !(used_nums_in_row[row][val] || used_nums_in_col[col][val] || used_nums_in_box[box_no][val]);
    }

    auto DFS_(std::vector<Pos>::iterator i) {
        if (i == end(blanks)) {
            finished = true;
            return;
        }
        auto [row, col] = *i;
        for (int num = 1; num <= 9; ++num) {
            if (legal(row, col, num)) {
                data[row][col] = num;
                mark_as_used(row, col, num);
                DFS_(i + 1);
                if (finished) break;
                unmark_used(row, col, num);
            }
        }
    }
public:
    auto initial(Map const & a) {
        blanks.clear();
        for (int i = 0; i < a.size(); ++i) {
            used_nums_in_box[i].fill(false);
            used_nums_in_row[i].fill(false);
            used_nums_in_col[i].fill(false);
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
        finished = false;
    }
    SudokuSolve(Map const & a) {
        initial(a);
    }
    auto reset() {
        if (finished) {
            for (auto pos : blanks) {
                auto [r,c] = pos;
                unmark_used(r, c, data[r][c]);
                data[r][c] = UNFILLED;
            }
            finished = false;
        }
    }
    auto get_status() { return data; }
    auto DFS_solve() { if (!finished) DFS_(begin(blanks)); }

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
