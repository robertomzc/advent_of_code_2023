#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class TextFile {
private:
    ifstream f;

public:
    explicit TextFile(string file_path);
    string next();
    vector<string> read();
    vector<string> readWithFrame(char c);
};