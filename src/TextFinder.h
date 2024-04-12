#ifndef KAGEBUNSHIN_TEXTFINDER_H
#define KAGEBUNSHIN_TEXTFINDER_H

#include <filesystem>
#include <vector>

class TextFinder {
    std::filesystem::path directory;
    std::vector<std::string> words;

public:
    explicit TextFinder(std::filesystem::path &&directoryToSearch, std::vector<std::string> &&wordsToSearch);
    void find();
};

#endif//KAGEBUNSHIN_TEXTFINDER_H
