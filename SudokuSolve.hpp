#include <array>
#include <vector>
#include <string>
#include <functional>

class SudokuSolve {
private:
    using Pos = std::pair<int, int>;
    using PosArray = std::vector<Pos>;
public:
    using Map = std::array<std::array<int, 9>, 9>;
    using CharMap = std::array<std::array<char, 9>, 9>;

    constexpr static int UNFILLED = 0;

    [[nodiscard]] static Map DFS_solve(Map const & a);

    [[nodiscard]] static auto solve(Map const & a) {
        return DFS_solve(a);
    }

    [[nodiscard]] static auto solve(CharMap const & a) {
        Map m;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                m[i][j] = (a[i][j] - '0');
            }
        }
        return solve(m);
    }

    static std::string to_string(Map const & a);
};
