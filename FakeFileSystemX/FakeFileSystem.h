#pragma once
#include "Directory.h"
#include <random>
#include <filesystem>

#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include "TimeFormatter.h"

using namespace filesystem;
using namespace std;

/**
 * @class FakeFileSystem
 * @brief This class is the main class as it is the class that amkes the fake file system work. 
 */
class FakeFileSystem {
public:
    explicit FakeFileSystem(string rootPath);

    ~FakeFileSystem();

    void display() const;

    bool changeDirectory(const path& newPath);

    bool createDirectory(const path& directoryPath, time_t time, bool isVirtual = false);

    bool createFile(const path& filePath, time_t time, int filesize = 0, bool isVirtual = false);

    bool deleteEntity(path& entityPath);

    bool sortByName();

    bool sortBySize();


private:
    Directory* currentDirectory;
    Directory root;
    path currentPath;

    void initialize(path current = current_path());
};