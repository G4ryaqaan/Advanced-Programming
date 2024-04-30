#include "CommandLine.h"

CommandLine::CommandLine(FakeFileSystem& fileSystem) : fs(fileSystem) {}

void CommandLine::start() {
    std::string input;
    string currentDirectory = "";

    std::cout << "Initialisation complete..." << endl;
    while (true) {
        //std::cout << "Enter a command ('dir', 'cd name', 'sortsize', 'sortname', 'mkdir name', 'mkfile name', del name, 'exit'): ";
        if(currentDirectory == "")
            std::cout << "\\ :> ";
        else 
            std::cout << currentDirectory + " :> ";

        std::getline(std::cin, input);

        if (input == "dir") {
            fs.display();
        }
        else if (input.substr(0, 3) == "cd ") {
            std::string newDir = input.substr(3);
            if (!fs.changeDirectory(newDir)) {
                std::cerr << "Invalid directory path. please enter directory path." << std::endl;
            }
            else {
                if(newDir == "..")
                    currentDirectory = removeAfterLastSlash(currentDirectory); 
                else
                    currentDirectory += "\\" + newDir;
            }

        }
        else if (input == "sortsize") {
            fs.sortBySize();
        }
        else if (input == "sortname") {
            fs.sortByName();
        }
        else if (input.substr(0, 6) == "mkdir ") {
            path newDir = input.substr(6);
            fs.createDirectory(newDir, true);
        }
        else if (input.substr(0, 7) == "mkfile ") {
            path newFile = input.substr(7);
            fs.createFile(newFile, true);
        }
        else if (input.substr(0, 4) == "del ") {
            path entity = input.substr(4);
            fs.deleteEntity(entity);
        }
        else if (input == "exit") {
            break;
        }
        else {
            std::cerr << "Invalid command. Please try again." << std::endl;
        }
    }
}


std::string CommandLine::removeAfterLastSlash(std::string str) {
    size_t lastSlashPos = str.find_last_of('\\');
    if (lastSlashPos != std::string::npos) {
        str = str.substr(0, lastSlashPos);
    }
    return str;
}
