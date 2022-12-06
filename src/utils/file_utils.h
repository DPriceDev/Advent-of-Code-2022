#ifndef ADVENT_OF_CODE_2022_CPP_FILE_UTILS_H
#define ADVENT_OF_CODE_2022_CPP_FILE_UTILS_H

#include <fstream>
#include <vector>

namespace file {

    auto getLines(const std::string& filename) -> std::vector<std::string> {
        std::ifstream input { filename };
        std::string line;
        std::vector<std::string> lines { };

        while (getline(input, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    auto readText(const std::string& filename) -> std::string {
        std::ifstream input { filename };
        std::string line;
        std::string output;

        while (getline(input, line)) {
            output += line;
        }
        return output;
    }

}

#endif // ADVENT_OF_CODE_2022_CPP_FILE_UTILS_H
