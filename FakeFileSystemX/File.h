#pragma once
#include <iostream>
#include "FileSystemComponent.h"
#include "TimeFormatter.h"

/**
 * @class File
 * @brief This class is a child class of fileSystemComponents. this class handles and manipulate sthe files of the applcaition.
 */
struct File : public FileSystemComponent {
public:
    File(path path, time_t time, int filesize);

    [[nodiscard]] string listContent() const override;

    int combinedFileSize (int currentTotal, File* file);
    bool isSmallerThan(const File& otherFile) const;

private:
    int size;
};