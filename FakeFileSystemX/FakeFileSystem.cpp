#include "FakeFileSystem.h"


FakeFileSystem::FakeFileSystem(string rootPath) : root(Directory(rootPath, std::time(nullptr))) {
    currentDirectory = &root;
    initialize();
}

FakeFileSystem::~FakeFileSystem() {
    delete& root;
}

void FakeFileSystem::display() const {
    if (currentDirectory != nullptr) {
        currentDirectory->AllEntities();
    }
    else {
        std::cerr << "No current directory to display." << std::endl;
    }
}

bool FakeFileSystem::changeDirectory(const path& newPath) {
    if (currentDirectory == nullptr) {
        std::cerr << "Current directory is null." << std::endl;
        return false;
    }

    Directory* newDir = currentDirectory->isValidDirectory(newPath);
    if (newDir != nullptr) {
        currentDirectory = newDir;
        currentPath = currentDirectory->entityPath;

        return true;
    }
    else if (newPath == "..") {
        cout << currentDirectory->entityPath << endl;;
        cout << currentPath.parent_path() << endl;

        Directory* parent = currentDirectory->isValidDirectory(newPath);

        if (parent != nullptr) {
            currentDirectory = parent;
            cout << currentDirectory->entityPath << endl;
            cout << "aaa" << endl;

            return true;
        }
    }
    else {
        std::cerr << "Directory not found: " << newPath << std::endl;
        return false;
    }
}


bool FakeFileSystem::createDirectory(const path& directoryPath, time_t time, bool isVirtual) {
    bool status;
    if (!isVirtual) {
        status = currentDirectory->addEntity(directoryPath, time);
    }
    else {
        path fullPath = currentPath / directoryPath;
        status = currentDirectory->addEntity(fullPath, time);
    }
    return status;
};

bool FakeFileSystem::createFile(const path& filePath, time_t time, int filesize, bool isVirtual) {
    if (filesize == -1) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 3000);
        filesize = distrib(gen);
    }

    bool status;
    if (!isVirtual) {
        status = currentDirectory->addEntity(filePath, time, filesize);
    }
    else {
        path fullPath = currentPath / filePath;
        status = currentDirectory->addEntity(fullPath, time, filesize);
    }
    return status;
};

bool FakeFileSystem::deleteEntity(path& entityPath) {
    currentDirectory->deleteEntity(entityPath);
    return false;
};

bool FakeFileSystem::sortByName() {
    currentDirectory->sortContentAlphabetically();
    return false;
};
bool FakeFileSystem::sortBySize() {
    currentDirectory->sortContentBySize();
    return false;
};


void FakeFileSystem::initialize(path current) {
    for (const filesystem::directory_entry& item : filesystem::directory_iterator(current))
    {
        tm convertedToTM = TimeFormatter::convertTime(item.last_write_time());
        time_t convertedTime = TimeFormatter::convertTimeToTimeT(convertedToTM);

        if (item.is_directory())
        {          
            createDirectory(item.path(), convertedTime);
        }
        else
        {
            createFile(item.path(), convertedTime, item.file_size());
        }
    }
}