#include "file_utils.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <map>
#include <sstream>

struct Directory {
    bool isRoot = false;
    std::size_t parentId;
    std::map<std::string, std::size_t> directories { };
    std::size_t size = 0;
};

class FileSystem {
    std::vector<Directory> directories { Directory { .isRoot = true } };
    std::size_t root = 0;
    std::size_t current = root;

    auto addFile(std::size_t index, std::size_t size) -> void {
        directories[index].size += size;
        if (!directories[index].isRoot) addFile(directories[index].parentId, size);
    }

public:
    auto addDirectory(const std::string& name) {
        directories.push_back({ .parentId = current });
        getCurrentDirectory()->directories[name] = directories.size() - 1;
    }

    auto addFile(const std::size_t size) { addFile(current, size); }

    auto getDirectories() -> std::vector<Directory>& { return directories; }

    auto getRootDirectory() -> Directory* { return &directories[root]; }

    auto getCurrentDirectory() -> Directory* { return &directories[current]; }

    auto setDirectory(const std::string&& name) { current = getCurrentDirectory()->directories[name]; }

    auto goUp() { current = getCurrentDirectory()->parentId; }

    auto goToRoot() { current = root; }
};

auto generateFileSystem(std::vector<std::string>& commands) -> FileSystem {
    FileSystem fileSystem;
    for(const auto& command : commands) {
        if (command == ("$ cd /")) fileSystem.goToRoot();
        else if (command == ("$ cd ..")) fileSystem.goUp();
        else if (command.starts_with("$ ls")) continue;
        else if (command.starts_with("$ cd")) {
            fileSystem.setDirectory({ command.begin() + 4, command.end() });
        }
        else if (command.starts_with("dir")) {
            fileSystem.addDirectory({ command.begin() + 3, command.end() });
        } else {
            std::stringstream sstream { command };
            std::size_t size = 0;
            sstream >> size;
            fileSystem.addFile(size);
        }
    }
    return fileSystem;
}

constexpr auto toSize = [] (const auto& directory) { return directory.size; };

auto findMaxSizeOf(FileSystem& fileSystem) -> std::size_t {
    constexpr auto lessThan = [] (const auto size) { return size <= 100000; };
    auto filtered = fileSystem.getDirectories()
                    | std::views::transform(toSize)
                    | std::views::filter(lessThan);

    return std::reduce(filtered.begin(), filtered.end());
}

auto findDirectoryToDelete(FileSystem& fileSystem) -> std::size_t {
    const auto baseSize = fileSystem.getRootDirectory()->size;
    const auto freeSpace = [&] (const auto size) { return ((70000000 - baseSize) + size) >= 30000000; };

    auto sizes = fileSystem.getDirectories()
                 | std::views::transform(toSize)
                 | std::views::filter(freeSpace);

    return std::ranges::min(sizes);
}

auto main() -> int {
    auto commands = file::getLines("input.txt");
    auto fileSystem = generateFileSystem(commands);

    const auto partOne = findMaxSizeOf(fileSystem);
    const auto partTwo = findDirectoryToDelete(fileSystem);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;
    return 0;
}