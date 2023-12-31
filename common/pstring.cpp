#include "pstring.h"
#include <string>
#include <cstring>
#include <vector>

PString::PString(string str) : str(str) {}

vector<string> PString::split(string delim) {
    vector<string> split_string;
    char *delim_ptr = const_cast<char *> (delim.c_str());
    char *line_without_game_number = const_cast<char *> (str.c_str());
    char *ptr; // declare a ptr pointer

    ptr = strtok(line_without_game_number, delim_ptr);
    // use while loop to check ptr is not null
    while (ptr != nullptr)
    {
        split_string.emplace_back(ptr);
        ptr = strtok (nullptr, delim_ptr);
    }
    return split_string;
}


