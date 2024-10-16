# kagebunshin

[![CMake](https://github.com/adrianovaladar/kagebunshin/actions/workflows/cmake.yml/badge.svg)](https://github.com/adrianovaladar/kagebunshin/actions/workflows/cmake.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=adrianovaladar_kagebunshin&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=adrianovaladar_kagebunshin)

![31c708365aacd0c153d261dd56d5d30dc9323443v2_00](https://github.com/adrianovaladar/kagebunshin/assets/60299267/e4e67df4-c0b8-43b5-a356-166ad488bb08)

Kagebunshin is a C++ application for finding text occurrences within files in a directory. It provides a simple and
efficient way to search for specific words or phrases across multiple files.

## Features

* Search for words or phrases in text files within a specified directory and all its subdirectories;
* Multithreaded implementation for parallel searching, improving performance on multicore systems.

## Installation

Clone the repository:

    $ git clone https://github.com/adrianovaladar/kagebunshin.git

Compile the project, navigating to the root directory and executing the following commands:

    $ cmake .
    $ make

## Usage

Execute the following command:

    $ ./kagebunshin <directory_path> <word1> <word2> ...

* <directory_path>: The absolute path of the directory to search for text files;
* \<word1\> \<word2\> ...: The words to search.

### Example

    $ ./kagebunshin /path/to/directory word1 word2

## Creators

This project was created by [**Adriano Valadar**](https://github.com/adrianovaladar).
