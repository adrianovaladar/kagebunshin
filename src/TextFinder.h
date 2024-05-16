#ifndef KAGEBUNSHIN_TEXTFINDER_H
#define KAGEBUNSHIN_TEXTFINDER_H

#include <filesystem>
#include <stack>
#include <vector>
#include <mutex>
/**
 * @brief Class for finding text occurrences within files in a directory.
 */
class TextFinder {
    std::filesystem::path directory;/**< Directory to search.*/
    std::vector<std::string> words;/**< Words to search.*/
    std::stack <std::filesystem::path> foundFiles;/**< Stack that contains the files where the words were found.*/
    std::mutex filesMutex {};/**< Mutex to synchronize access to the files stack. */
    std::mutex foundFilesMutex {};/**< Mutex to synchronize access to the foundFiles stack. */
    /** @brief Find the words in the directory.
     */
    void find();
    /** @brief Find the words in a given file.
    *   @param files Stack that contains the files to search.
    */
    void findInFile(std::stack<std::filesystem::path> &files);

public:
    /**
     * Default constructor.
     */
    explicit TextFinder() = default;
    /**
     * Getter of the found files.
     * @return Stack that contains the found files.
     */
    [[nodiscard]] std::stack<std::filesystem::path> getFoundFiles() const { return foundFiles; }
    /**
     * @brief Find the words in the directory.
     * @param directoryToSearch directory to search.
     * @param wordsToSearch words to search.
     */
    void find(std::filesystem::path &&directoryToSearch, std::vector<std::string> &&wordsToSearch);
};

#endif//KAGEBUNSHIN_TEXTFINDER_H

