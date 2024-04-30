#pragma once
#include "FakeFileSystem.h"

/**
 * @class CommandLine
 * @brief This is the class th euser interacts with, which promts the user as well as takes the users input. 
 */
class CommandLine {
public:
    explicit CommandLine(FakeFileSystem& fileSystem);
    void start();

private:
    FakeFileSystem& fs;

    std::string removeAfterLastSlash(std::string str);
};
