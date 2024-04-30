#include "File.h"

File::File(path path, time_t time, int filesize) : FileSystemComponent(std::move(path), time), size(filesize) {}

string File::listContent() const {
    return   TimeFormatter::formatTime(timeStamp) + "\t" + to_string(size) + " \t" + name;
};

int File::combinedFileSize(int currentTotal, File* file) {
    return currentTotal + file->size;
};

bool File::isSmallerThan(const File& otherFile) const {
    return size < otherFile.size;
}
