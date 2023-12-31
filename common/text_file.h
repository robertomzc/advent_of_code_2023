#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class TextFile {
private:
    std::ifstream f;

public:
    explicit TextFile(std::string file_path);
    std::string next();
};