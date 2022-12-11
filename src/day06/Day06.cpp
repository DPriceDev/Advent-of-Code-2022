#include "Day06.h"
#include <ranges>
#include <algorithm>
#include <expected>

// hand rolling this duplicate check is turned out to be faster than using a set or set insert
constexpr auto isUnique(const std::string_view message) -> std::expected<void, int> {
    for (std::size_t first = 0; first < message.length() - 1; ++first) {
        const auto isMatching = [&] (const auto value) { return message[first] == value; };
        const auto foundMatch = std::find_if(message.begin() + first + 1, message.end(), isMatching);
        if (foundMatch != message.end()) return std::unexpected { first };
    }
    return std::expected<void, int> { };
}

// if c++23 was complete here, it would be good to swap this with std::views::slide
constexpr auto indexOfUniqueString(const std::string_view message, const std::size_t uniqueLength) -> std::size_t {
    for (auto slice = message.begin(); slice != message.end() - uniqueLength; ++slice) {
        const auto found = isUnique({ slice, slice + uniqueLength });
        if (found) return (slice - message.begin()) + uniqueLength; else slice += found.error();
    }
}


auto Day06::partOne(std::string& input) -> size_t {
    return indexOfUniqueString(input, 4);
}

auto Day06::partTwo(std::string& input) -> size_t {
    return indexOfUniqueString(input, 14);
}