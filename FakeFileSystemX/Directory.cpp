#include "Directory.h"


Directory::Directory(path path, time_t time, Directory* parent)
    : FileSystemComponent(path, time), parentDirectory(parent) {}

string Directory::listContent() const {
    return TimeFormatter::formatTime(timeStamp) + "\t<DIR> \t" + name;
};

bool Directory::AllEntities() {
    try {
        int fileCount = 0;
        int sizeCount = 0;
        int dirCount = 0;

        for (const auto& item : content) {
            File* file = dynamic_cast<File* > (item.second.get());
            if (file != nullptr) {
                fileCount++;
                sizeCount = file->combinedFileSize(sizeCount, file);
            }
            else {
                dirCount++;
            }

            cout << item.second->listContent() << endl;
        }

        cout << "\t";
        cout << fileCount;
        cout << " Files(s)\t";
        cout << sizeCount;
        cout << " total bytes" << endl;

        cout << "\t";
        cout << dirCount;
        cout << " Dir(s) " << endl;
    }
    catch (exception e) {
        cout << "\n" << e.what() << "\n" << endl;
    }

    return 0;
}

bool Directory::addEntity(const path& itemPath, time_t time, int size) {
    try {
        if (containsEntity(itemPath.string())) {
            std::cerr << "Error in addEntity: Entity already exists." << std::endl;
            return false;
        }

        std::unique_ptr<FileSystemComponent> entity;
        if (size == -1) {
            entity = std::make_unique<Directory>(itemPath, time,  this);
        }
        else {
            entity = std::make_unique<File>(itemPath, time, size);
        }

        content.emplace_back(itemPath.filename().string(), std::move(entity));

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error in addEntity: " << e.what() << std::endl;
        return false;
    }
}

bool Directory::deleteEntity(const path& itemPath) {
    try {
        std::string entityName = itemPath.filename().string();
        auto it = std::remove_if(content.begin(), content.end(), [&entityName](const auto& item) {
            return item.first == entityName;
            });

        if (it != content.end()) {
            content.erase(it);
            return true;
        }
        else {
            throw std::runtime_error("No entity named " + entityName + " exists. please check if the entity exists.");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in deleteEntity: " << e.what() << std::endl;
        return false;
    }

    return false;
}

Directory* Directory::isValidDirectory(path itemPath) {
    string itemName = itemPath.filename().string();

    if (itemPath == "..") {
        return parentDirectory;
    }
    else {
        for (auto& item : content) {
            Directory* dir = dynamic_cast<Directory*>(item.second.get());

            if (dir != nullptr && item.first == itemName) {
                return dir;
            }
        }
    }
    return nullptr;
}


// Comparison functions
static bool alphabeticalCompare(const std::pair<std::string, std::unique_ptr<FileSystemComponent>>& a,
    const std::pair<std::string, std::unique_ptr<FileSystemComponent>>& b) {
    return a.first < b.first;
}

static bool sizeCompare(const std::pair<std::string, std::unique_ptr<FileSystemComponent>>& a,
    const std::pair<std::string, std::unique_ptr<FileSystemComponent>>& b) {
    const File* fileA = dynamic_cast<const File*>(a.second.get());
    const File* fileB = dynamic_cast<const File*>(b.second.get());

    if (fileA && fileB) {
        return fileA->isSmallerThan(*fileB);
    }
    else if (fileA) {
        return true;
    }
    else if (fileB) {
        return false;
    }

    return a.first < b.first;
}

void Directory::sortContentAlphabetically() {
    Sorter<std::pair<std::string, std::unique_ptr<FileSystemComponent>>>::sort(content, alphabeticalCompare);
}

void Directory::sortContentBySize() {
    Sorter<std::pair<std::string, std::unique_ptr<FileSystemComponent>>>::sort(content, sizeCompare);
}


bool Directory::containsEntity(const std::string& entityName) const {
    auto it = std::find_if(content.begin(), content.end(),
        [&entityName](const auto& item) {
            return item.first == entityName;
        });

    return it != content.end();
}