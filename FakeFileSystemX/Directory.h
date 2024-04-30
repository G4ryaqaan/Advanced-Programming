#pragma once
#include <iostream>
#include "File.h"
#include "Sorter.h"
#include "TimeFormatter.h"
#include <vector>
#include <stdexcept> 


using namespace std;

/**
 * @class Directory
 * @brief This class is a child class of fileSystemComponents. this class handles and manipulates the directories of the applcaition.
 */
class Directory : public FileSystemComponent {
public:
    explicit Directory(path path, time_t time,Directory* parent = nullptr);


    friend std::ostream& operator<<(std::ostream& os, const Directory& directory);
    friend std::istream& operator>>(std::istream& is, Directory& directory);

    string listContent() const override;

    bool AllEntities();
    bool addEntity(const path& itemPath, time_t time, int size = -1);
    bool deleteEntity(const path& itemPath);
    Directory* EntityCast(const path& itemPath);
    Directory* isValidDirectory(path itemPath);

    void sortContentAlphabetically();
    void sortContentBySize();

private:
    std::vector<std::pair<std::string, std::unique_ptr<FileSystemComponent>>> content;
    Directory* parentDirectory;

    bool containsEntity(const std::string& entityName) const;
    std::string removeBeforeFirstSlash(const std::string& str) const;

};