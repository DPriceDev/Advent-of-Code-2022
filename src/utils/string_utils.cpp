#include "string_utils.h"
#include <charconv>

auto string::splitString(const std::string_view toSplit, const char delimiter) -> std::vector<std::string_view> {
    auto output = std::vector<std::string_view> { };
    for (const auto token : toSplit | std::views::split(delimiter)) {
        output.emplace_back(token);
    }
    return output;
}

auto string::toInt(const std::string_view input) -> long {
    long output;
    std::from_chars(input.begin(), input.end(), output);
    return output;
}

auto string::trimLeft(const std::string_view value) -> std::string_view {
    const auto find = std::ranges::find_if(value, [] (const auto letter) {
        return letter != ' ';
    });
    return std::string_view { find, value.end() };
}

