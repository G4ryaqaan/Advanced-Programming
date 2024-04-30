#include "pch.h"
#include "../FakeFileSystem/File.h"
#include "../FakeFileSystem/Directory.h"
#include "../FakeFileSystem/FakeFileSystem.h"

/*
This is my unit testings.
*/

TEST(FileTest, ListContentTest) {
    File file("test.txt", 100);
    string content = file.listContent();

    EXPECT_FALSE(content.empty());
    EXPECT_EQ(content, "Content of the file");
}

TEST(FileTest, IsSmallerThanTest) {
    File file1("file1.txt", 50);
    File file2("file2.txt", 75);

    EXPECT_TRUE(file1.isSmallerThan(file2));
    EXPECT_FALSE(file2.isSmallerThan(file1));
}

TEST(DirectoryTest, AddEntityTest) {
    Directory directory("testDirectory", nullptr);
    bool result = directory.addEntity("file1.txt", 100);

    EXPECT_TRUE(result);
}

TEST(DirectoryTest, DeleteEntityTest) {
    Directory directory("testDirectory", nullptr);
    directory.addEntity("file1.txt", 100);
    bool result = directory.deleteEntity("file1.txt");

    EXPECT_TRUE(result);
}

/* 
This is my system testings. 
It covers three of the compopnents of the fake file system compeonets
*/

TEST(FakeFileSystemTest, ChangeDirectoryTest) {
    FakeFileSystem fs("root");
    bool result = fs.changeDirectory("subdir");

    EXPECT_TRUE(result);
}

TEST(FakeFileSystemTest, CreateDirectoryTest) {
    FakeFileSystem fs("root");
    bool result = fs.createDirectory("newdir");

    EXPECT_TRUE(result);
}

TEST(FakeFileSystemTest, CreateFileTest) {
    FakeFileSystem fs("root");
    bool result = fs.createFile("newfile.txt", 100);

    EXPECT_TRUE(result);
}