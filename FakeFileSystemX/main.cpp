
#include "FakeFileSystem.h"
#include "CommandLine.h"
#include <random>

int main() {

    FakeFileSystem fs("root");
    CommandLine command(fs);
    command.start();


    return 0;
}


