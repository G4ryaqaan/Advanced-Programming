#pragma once
#include <string>
#include <filesystem>
#include "TimeFormatter.h"


/**
 * @class FilesystemComponent
 * @brief This class is used to ecapsulate and apply advanced OOP concepts suchas inheritance. thisbis the parent class of file and directory.
 */
using namespace std;
using namespace filesystem;

class FileSystemComponent {
public:
    FileSystemComponent(path path, time_t time) : entityPath(path), name(path.filename().string()), timeStamp(time) {}
    virtual ~FileSystemComponent() = default;
    virtual string listContent() const = 0;

    friend ostream& operator<<(ostream& os, const FileSystemComponent& fsComponent) {
        os << "Time: " << TimeFormatter::formatTime(fsComponent.timeStamp) << " Path: " << fsComponent.entityPath;
        return os;
    }

    path entityPath;
    string name;
    time_t timeStamp;
};
