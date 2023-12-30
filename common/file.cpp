#include "file.h"
#include <string>

File::File(std::string file_path) : f(file_path) {
}

std::string File::next() {
    std::string line;
    if (std::getline(f, line)) {
        return line;
    } else {
        return ""; // Return an empty string when there are no more lines
    }
}
