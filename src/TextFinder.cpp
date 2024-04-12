#include "TextFinder.h"

TextFinder::TextFinder(std::filesystem::path &&directoryToSearch, std::vector<std::string> &&wordsToSearch) : directory(std::move(directoryToSearch)), words(std::move(wordsToSearch)) {}

void TextFinder::find() {}
