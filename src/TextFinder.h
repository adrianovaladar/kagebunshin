#ifndef KAGEBUNSHIN_TEXTFINDER_H
#define KAGEBUNSHIN_TEXTFINDER_H

#include <filesystem>
#include <stack>
#include <vector>

class TextFinder {
    std::filesystem::path directory;
    std::vector<std::string> words;

public:
    explicit TextFinder(std::filesystem::path &&directoryToSearch, std::vector <std::string> &&wordsToSearch);
    void find();
    void findInFile(std::stack<std::filesystem::path> &files);
};

#endif//KAGEBUNSHIN_TEXTFINDER_H
