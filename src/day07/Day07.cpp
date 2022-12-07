#include <iostream>
#include "file_utils.h"
#include <utility>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <map>

struct File {
    std::string name;
    std::size_t size;

    File(std::string name, std::size_t size) : name(name), size(size) { }
};

// todo: if adding a file, call add size of parent and current directory?

struct Directory {
    Directory* parent;
    std::vector<File> files;
    std::map<std::string, Directory> directories;

    [[nodiscard]]
    std::size_t getSize() const {
        const auto getFileSize = [] (const auto total, const auto& next) { return total + next.size; };
        const auto fileSize = std::accumulate(files.begin(), files.end(), 0, getFileSize);

        const auto getDirSize = [] (const auto total, auto& next) { return total + next.second.getSize(); };
        const auto dirSize = std::accumulate(directories.begin(), directories.end(), 0, getDirSize);

        return fileSize + dirSize;
    }

    [[nodiscard]]
    std::vector<std::size_t> getAllSizes() const {
        std::vector<std::size_t> sizes;

        sizes.push_back(getSize());

        for (const auto& directory : directories) {
            for (const auto & size : directory.second.getAllSizes()) {
                sizes.push_back(size);
            }
        }

        return sizes;
    }

    auto getDirectory(std::string name) -> Directory& {
        auto directory = std::find_if(directories.begin(), directories.end(), [&] (auto& directory) {
            return directory.first == name;
        });

        if (directory == directories.end()) {
            directories[name] = Directory { .parent = this };
            return directories[name];
        }

        return directory->second;
    }

    auto addDirectory(std::string name) {
        getDirectory(name);
    }

    auto addFile(std::string& name, std::size_t size) {
        files.emplace_back(name, size);
    }
};


auto findMaxSizeOf(const Directory& directory) -> std::size_t {
    auto sizes = directory.getAllSizes();

    auto lowest = [] (const auto& size) { return size <= 100000; };
//    std::ranges::sort(sizes);
    auto count = 0;
    for(const auto& size : sizes) {
        if (size <= 100000) {
            count += size;
        }
    }

    return count;
}

auto parseCommands(std::vector<std::string>& commands) -> Directory {
    Directory base { };
    Directory* current = &base;

    for(const auto& command : commands) {

        if (command == ("$ cd /")) { current = &base; }
        else if (command == ("$ cd ..")) { current = current->parent; }
        else if (command.starts_with("$ cd")) {
            current = &current->getDirectory(std::string { command.begin() + 4, command.end() });
        }
        else if (command.starts_with("$ ls")) { /* no - op*/ }
        else if (command.starts_with("dir")) {
            current->addDirectory(std::string { command.begin() + 3, command.end() });
        }
        else {
            std::stringstream sstream { command };
            std::size_t size = 0;
            std::string name;
            sstream >> size;
            sstream >> name;
            current->addFile(name, size);
        }
    }

    return base;
}

auto main() -> int {
    auto commands = file::getLines("input.txt");

    const auto baseDirectory = parseCommands(commands);

    const auto partOne = findMaxSizeOf(baseDirectory);

    auto sizes = baseDirectory.getAllSizes();
    const auto baseSize = baseDirectory.getSize();
    std::ranges::sort(sizes);
    auto test = std::find_if(sizes.begin(), sizes.end(), [&baseSize] (const auto& size) {
        auto test = ((70000000 - baseSize) + size);
        return test >= 30000000;
    });

    std::cout << "part 1: " << partOne << "\npart 2: " << *test;

    return 0;
}