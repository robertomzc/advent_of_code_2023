#include <string>
#include <vector>

using namespace std;

class PString {
private:
    string str;

public:
    explicit PString(string str);
    vector<string> split(string delim);
};