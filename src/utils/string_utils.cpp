#include "string_utils.h"
#include <charconv>

auto string::splitString(const std::string_view toSplit, const char delimiter) -> std::vector<std::string_view> {
    auto output = std::vector<std::string_view> { };
    for (const auto token : toSplit | std::views::split(delimiter)) {
        output.emplace_back(token);
    }
    return output;
}

auto string::toInt(std::string_view input) -> size_t {
    int output;
    std::from_chars(input.begin(), input.end(), output);
    return output;
}


