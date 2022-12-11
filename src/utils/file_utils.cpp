#include "file_utils.h"

auto file::getLines(const std::string& filename) -> std::vector<std::string> {
    std::ifstream input { filename };
    std::string line;
    std::vector<std::string> lines { };

    while (getline(input, line)) {
        lines.push_back(line);
    }
    return lines;
}

auto file::readText(const std::string& filename) -> std::string {
    std::ifstream input { filename };
    std::string line;
    std::string output;

    while (getline(input, line)) {
        output += line;
    }
    return output;
}