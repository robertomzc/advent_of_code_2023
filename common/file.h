#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class File {
private:
    std::ifstream f;

public:
    explicit File(std::string file_path);
    std::string next();
};