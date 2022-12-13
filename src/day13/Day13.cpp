#include "Day13.h"
#include "string_utils.h"
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

enum Result { EQUAL, A, B };

auto distanceToListEnd(const std::string_view input) -> auto {
    const auto index = std::ranges::find_if(input, [count = 0] (const auto value) mutable {
        const auto isFound = value == ']' && count == 0;
        count += (value == '[') - (value == ']');
        return isFound;
    });
    return index - input.begin();
}

auto getValueEnd(const auto start, const auto end) -> decltype(start) {
    const auto comma = std::find_if(start, end, [] (const auto value) { return value == ','; });
    return (comma != end) ? comma : std::find_if(start, end, [] (const auto value) { return value == ']'; });
}

auto checkValues(const auto viewA, const auto viewB) -> Result {
    const auto valueEndA = getValueEnd(viewA.begin(), viewA.end());
    const auto valueA = string::toInt({ viewA.begin(), valueEndA });

    const auto valueEndB = getValueEnd(viewB.begin(), viewB.end());
    const auto valueB = string::toInt({ viewB.begin(), valueEndB });

    if (valueA > valueB) return Result::B;
    if (valueA < valueB) return Result::A;
    return Result::EQUAL;
}

// todo: would be nicer to do this with stringviews?
// potentially instead of adding brackets, could always ignore them?
// todo: could just set an end condition which is either end of string, or ], and return index of ] ?
auto comparePackets(std::string packetA, std::string packetB) -> Result {
    for (long aIndex = 1, bIndex = 1; aIndex < packetA.size(); ++aIndex, ++bIndex) {
        aIndex += packetA[aIndex] == ',';
        bIndex += packetB[bIndex] == ',';

        if (packetA[aIndex] == ']' && packetB[bIndex] == ']') return Result::EQUAL;
        if (packetA[aIndex] == ']') return Result::A;
        if (packetB[bIndex] == ']') return Result::B;

        if (packetA[aIndex] == '[' || packetB[bIndex] == '[') {

            if (packetA[aIndex] != '[') {
                const auto aEnd = getValueEnd(packetA.begin() + aIndex, packetA.end());
                packetA.insert(aEnd, ']');
                packetA.insert(packetA.begin() + aIndex, '[');
            }

            if (packetB[bIndex] != '[') {
                const auto bEnd = getValueEnd(packetB.begin() + bIndex, packetB.end());
                packetB.insert(bEnd, ']');
                packetB.insert(packetB.begin() + bIndex, '[');
            }

            const auto aLength = distanceToListEnd({ packetA.begin() + aIndex + 1, packetA.end() });
            const auto bLength = distanceToListEnd({ packetB.begin() + bIndex + 1, packetB.end() });
            const auto result = comparePackets(
                    std::string { packetA.begin() + aIndex, packetA.begin() + aIndex + aLength + 2 },
                    std::string { packetB.begin() + bIndex, packetB.begin() + bIndex + bLength + 2 }
            );

            if (result == Result::A) return Result::A;
            if (result == Result::B) return Result::B;

            aIndex += aLength + 1;
            bIndex += bLength + 1;
            continue;
        }

        const auto result = checkValues(
            std::string_view { packetA.begin() + aIndex, packetA.end() },
            std::string_view { packetB.begin() + bIndex, packetB.end() }
        );
        if (result != Result::EQUAL) return result;
    }
    return Result::A;
}

auto Day13::partOne(const std::vector<std::string>& lines) -> size_t {
    long sum = 0;
    for (long index = 0, packetIndex = 1; index < lines.size(); index += 3, ++packetIndex) {
        const auto isCorrect = comparePackets(lines[index], lines[index + 1]);
        sum += packetIndex * (isCorrect == Result::A || isCorrect == Result::EQUAL);
    }
    return sum;
}

auto Day13::partTwo(const std::vector<std::string>& lines) -> size_t {
    std::vector<std::string> packets { };
    std::ranges::copy_if(lines, std::back_inserter(packets), [] (const auto& line) { return line != ""; });

    packets.emplace_back("[[6]]");
    packets.emplace_back("[[2]]");

    std::sort(packets.begin(), packets.end(), [] (const auto& a, const auto& b) {
        return comparePackets(a, b) == Result::A;
    });

    const auto packetSix = std::find(packets.begin(), packets.end(), "[[6]]");
    const auto packetTwo = std::find(packets.begin(), packets.end(), "[[2]]");
    return (packetSix - packets.begin() + 1) * (packetTwo - packets.begin() + 1);
}