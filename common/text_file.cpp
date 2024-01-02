#include "text_file.h"
#include <string>
#include <vector>

TextFile::TextFile(string file_path) : f(file_path) {
}

string TextFile::next() {
    string line;
    if (getline(f, line)) {
        return line;
    } else {
        return ""; // Return an empty string when there are no more lines
    }
}

vector<string> TextFile::read() {
    /* Returns a list with each element being a line of the file */

    vector<string> text;
    while (true) {
        string line = next();
        if (line.empty()) {
            break;
        }
        text.push_back(line);
    }
    return text;
}

vector<string> TextFile::readWithFrame(char c) {
    /* Returns a list with each element being a line of the file with a frame around with the character 'c' */

    string first_line = next();
    int size_of_line = first_line.size() + 2;  // +2 because of the right and left frames

    string line_frame = string(size_of_line, c);

    vector<string> text;
    text.push_back(line_frame);
    text.push_back(c + first_line + c);

    while (true) {
        string line = next();
        if (line.empty()) {
            break;
        }
        text.push_back(c + line + c);
    }

    text.push_back(line_frame);
    return text;
}