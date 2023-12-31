#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../../common/text_file.h"

using namespace std;

int PART = 2;  // Part of the day challenge

map<string, string> WORD_TO_DIGIT{{"zero",  "0"},
                                  {"one",   "1"},
                                  {"two",   "2"},
                                  {"three", "3"},
                                  {"four",  "4"},
                                  {"five",  "5"},
                                  {"six",   "6"},
                                  {"seven", "7"},
                                  {"eight", "8"},
                                  {"nine",  "9"}};


vector<string> ALL_DIGITS{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                          "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


int transformWordToDigit(string &word) {
    if (WORD_TO_DIGIT.count(word)) {  // if it's a "one" or "two"
        return stoi(WORD_TO_DIGIT.at(word));
    } else {  // we suppose its "1" or "2"
        return stoi(word);
    }
}

int extractFirstNumericDigit(string &line) {
    for (char c: line) {
        if (isdigit(c)) {
            return ((int) c) - 48;
        }
    }
    return -1;
}

int extractLastNumericDigit(string &line) {
    for (int i = (int) line.size() - 1; i >= 0; i--) {
        char c = line[i];
        if (isdigit(c)) {
            return ((int) c) - 48;
        }
    }
    return -1;
}

int extractFirstDigit(string &line) {
    size_t pos_found = string::npos;
    string digit_found;
    for (const string &digit: ALL_DIGITS) {
        size_t current_pos_found = line.find(digit);

        if (current_pos_found < pos_found) {
            pos_found = current_pos_found;
            digit_found = digit;
        }
    }
    return transformWordToDigit(digit_found);
}

int extractLastDigit(string &line) {
    size_t pos_found = 0;
    string digit_found;
    for (const string &digit: ALL_DIGITS) {
        size_t current_pos_found = line.rfind(digit);

        if (current_pos_found >= pos_found and current_pos_found != string::npos) {
            pos_found = current_pos_found;
            digit_found = digit;
        }
    }
    return transformWordToDigit(digit_found);
}

int main() {
    string f_path = "/home/rmartinezdelacruz/Code/personal/advent_of_code_2023/days/day1/input1";
    TextFile f(f_path);
    int cum_sum = 0;

    while (true) {
        string line = f.next();

        if (line.empty()) {
            break;
        }

        int line_digit;

        if (PART == 1) {
            line_digit = extractFirstNumericDigit(line) * 10 + extractLastNumericDigit(line);
        }
        else if (PART == 2) {
            line_digit = extractFirstDigit(line) * 10 + extractLastDigit(line);
        }
        else {
            throw invalid_argument( "PART should be 1 or 2" );
        }
        cum_sum += line_digit;

    }
    cout << cum_sum;

    return 0;
}