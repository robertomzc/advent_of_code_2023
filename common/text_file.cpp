#include "text_file.h"
#include <string>

TextFile::TextFile(std::string file_path) : f(file_path) {
}

std::string TextFile::next() {
    std::string line;
    if (std::getline(f, line)) {
        return line;
    } else {
        return ""; // Return an empty string when there are no more lines
    }
}
