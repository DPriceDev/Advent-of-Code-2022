#include "file_utils.h"
#include <iostream>
#include <vector>
#include <ranges>

auto findHiddenTreesSimp(const std::vector<std::string>& forest) -> size_t {
    auto count = 0;
    auto rowIndex = 1;
    for (const auto& row : std::ranges::subrange(forest.begin() + 1, forest.end() - 1)) {

        auto columnIndex = 1;
        for (const auto tree: std::ranges::subrange(row.begin() + 1, row.end() - 1)) {

            const auto height = tree - 48;

            auto top = false;
            for (int i = 0; i < rowIndex; ++i) {
                if (forest[i][columnIndex] - 48 >= height) top = true;
            }

            auto bottom = false;
            auto s = row.size();
            for (int i = rowIndex + 1; i < (forest.size()); ++i) {
                auto sdf = forest[i];
                auto test = forest[i][columnIndex] - 48;
                if (forest[i][columnIndex] - 48 >= height) bottom = true;
            }

            auto left = false;
            for (int i = 0; i < columnIndex; ++i) {
                auto test = forest[rowIndex][i] - 48;
                if (forest[rowIndex][i] - 48 >= height) left = true;
            }

            auto right = false;
            for (int i = columnIndex + 1; i < row.size(); ++i) {
                auto test = forest[rowIndex][i] - 48;
                if (forest[rowIndex][i] - 48 >= height) right = true;
            }

            if (top && bottom && left && right) {
                ++count;
                //std::cout << 't';
            } else {
               // std::cout << 'f';
            }


            ++columnIndex;
        }
      //  std::cout << '\n';

        ++rowIndex;
    }
    return (forest.size() * forest.front().size()) - count;
}


auto findTreeViewScore(const std::vector<std::string>& forest) -> size_t {
    auto max = 0;
    auto rowIndex = 1;
    for (const auto& row : std::ranges::subrange(forest.begin() + 1, forest.end() - 1)) {

        auto columnIndex = 1;
        for (const auto tree: std::ranges::subrange(row.begin() + 1, row.end() - 1)) {

            const auto height = tree - 48;

            auto score = 1;
            auto run = 0;
            auto top = false;
            for (int i = rowIndex - 1; i >= 0; --i) {
                auto a = forest[i][columnIndex];
                auto v = forest[i][columnIndex] - 48;
                if (!top) run += 1;
                if (forest[i][columnIndex] - 48 >= height) top = true;
            }

            score *= run;
            run = 0;

            auto bottom = false;
            for (int i = rowIndex + 1; i < (forest.size()); ++i) {
                auto a = forest[i][columnIndex];
                auto v = forest[i][columnIndex] - 48;
                if (!bottom) run += 1;
                if (forest[i][columnIndex] - 48 >= height) bottom = true;
            }

            score *= run;
            run = 0;

            auto left = false;
            for (int i = columnIndex - 1; i >= 0; --i) {
                auto a = forest[rowIndex][i];
                auto v = forest[rowIndex][i] - 48;
                if (!left) run += 1;
                if (forest[rowIndex][i] - 48 >= height) left = true;
            }

            score *= run;
            run = 0;

            auto right = false;
            for (int i = columnIndex + 1; i < row.size(); ++i) {
                auto a = forest[rowIndex][i];
                auto v = forest[rowIndex][i] - 48;
                if (!right) run += 1;
                if (forest[rowIndex][i] - 48 >= height) right = true;
            }

            score *= run;

            if (score > max) max = score;

            ++columnIndex;
        }
//        std::cout << '\n';

        ++rowIndex;
    }
    return max;
}

auto main() -> int {
    auto trees = file::getLines("input.txt");

    const auto partOne = findHiddenTreesSimp(trees);
    const auto partTwo = findTreeViewScore(trees);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;
    return 0;
}