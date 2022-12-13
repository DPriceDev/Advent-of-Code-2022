#include "file_utils.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <charconv>

// too low 3112

// not correct 3318

// maybe? 4894

// too high 5509

// too high 10986

enum Res {
    EQUAL,
    A,
    B
};

auto toInt(std::string_view input) -> int {
    int output;
    std::from_chars(input.begin(), input.end(), output);
    return output;
}

auto getClosingBracketIndex(const std::string_view input) -> int {
    auto count = 0;
    auto index = 0;
    for (const auto& item: input) {
        if (item == ']' && count == 0) {
            return index;
        }
        if (item == '[') count++;
        if (item == ']') count--;
        index++;
    }
    return index;
}

auto comparePackets(std::string packetA, std::string packetB) -> Res {
    auto bIndex = 1;
    for (int aIndex = 1; aIndex < packetA.size(); ++aIndex, ++bIndex) {

        if (packetA[aIndex] == ',') aIndex++;
        if (packetB[bIndex] == ',') bIndex++;

        if (packetA[aIndex] == ']' && packetB[bIndex] == ']') return Res::EQUAL;
        if (packetA[aIndex] == ']') return Res::A;
        if (packetB[bIndex] == ']') return Res::B;

        if (packetA[aIndex] == '[' || packetB[bIndex] == '[') {

            if (packetA[aIndex] != '[') {
                auto comma = std::find_if(packetA.begin() + aIndex, packetA.end(), [] (const auto value) { return value == ','; });
                auto closing = std::find_if(packetA.begin() + aIndex, packetA.end(), [] (const auto value) { return value == ']'; });

                auto aEnd = (comma != packetA.end()) ? comma : closing;

                packetA.insert(aEnd, ']');
               packetA.insert(packetA.begin() + aIndex, '[');
            }

            if (packetB[bIndex] != '[') {
                auto comma = std::find_if(packetB.begin() + bIndex, packetB.end(), [] (const auto value) { return value == ','; });
                auto closing = std::find_if(packetB.begin() + bIndex, packetB.end(), [] (const auto value) { return value == ']'; });

                auto bEnd = (comma != packetB.end()) ? comma : closing;

                packetB.insert(bEnd, ']');
                packetB.insert(packetB.begin() + bIndex, '[');
            }

            auto aClosing = getClosingBracketIndex({ packetA.begin() + aIndex + 1, packetA.end() });
            auto bClosing = getClosingBracketIndex({ packetB.begin() + bIndex + 1, packetB.end() });

            auto av = std::string_view { packetA.begin() + aIndex, packetA.begin() + aIndex + aClosing + 1 };
            auto bv = std::string_view { packetB.begin() + bIndex, packetB.begin() + bIndex + bClosing + 1  };

            auto a = std::string { packetA.begin() + aIndex, packetA.begin() + aIndex + aClosing + 2 };
            auto b = std::string { packetB.begin() + bIndex, packetB.begin() + bIndex + bClosing + 2  };

            const auto result = comparePackets(a, b);

            if (result == Res::A) return Res::A;
            if (result == Res::B) return Res::B;

            aIndex += aClosing + 1;
            bIndex += bClosing + 1;
            auto test = 2;
            continue;
        }

        auto comma = std::find_if(packetA.begin() + aIndex, packetA.end(), [] (const auto value) { return value == ','; });
        auto closing = std::find_if(packetA.begin() + aIndex, packetA.end(), [] (const auto value) { return value == ']'; });

        auto aEnd = (comma != packetA.end()) ? comma : closing;

        auto vA = toInt({ packetA.begin() + aIndex, aEnd });

        comma = std::find_if(packetB.begin() + bIndex, packetB.end(), [] (const auto value) { return value == ','; });
        closing = std::find_if(packetB.begin() + bIndex, packetB.end(), [] (const auto value) { return value == ']'; });

        auto bEnd = (comma != packetB.end()) ? comma : closing;

        auto vB = toInt({ packetB.begin() + bIndex, bEnd });

        // if integers are higher or lower check
        if (vA > vB) return Res::B;
        if (vA < vB) return Res::A;
    }
    return Res::A;
}

auto checkInputs(const std::vector<std::string>& lines) -> size_t {
    auto sum = 0;
    auto packetIndex = 1;
    for (int index = 0; index < lines.size(); index += 3) {
        const auto isCorrect = comparePackets(lines[index], lines[index + 1]);

        if (isCorrect == Res::A || isCorrect == Res::EQUAL) sum += packetIndex;

        if (isCorrect == Res::A || isCorrect == Res::EQUAL) std::cout << packetIndex << " ";
        ++packetIndex;
    }
    return sum;
}

auto sortPackets(const std::vector<std::string>& lines) {
    std::vector<std::string> noSpace;

    for (const auto &item: lines) {
        if (item != "") noSpace.push_back(item);
    }

    noSpace.emplace_back("[[6]]");
    noSpace.emplace_back("[[2]]");

    std::sort(noSpace.begin(), noSpace.end(), [] (const auto& a, const auto& b) {
        return comparePackets(a, b) == Res::A;
    });

    auto six = std::find(noSpace.begin(), noSpace.end(), "[[6]]");
    auto two = std::find(noSpace.begin(), noSpace.end(), "[[2]]");

    auto ain = six - noSpace.begin();
    auto bun = two - noSpace.begin();

    return (six - noSpace.begin() + 1) * (two - noSpace.begin() + 1);
}

auto main() -> int {
    const auto lines = file::getLines("input.txt");

    const auto partOne = checkInputs(lines);
    const auto partTwo = sortPackets(lines);;

    std::cout << "\npart 1: " << partOne << "\npart 2: " << partTwo;
    return 0;
}