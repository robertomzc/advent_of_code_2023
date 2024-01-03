#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../../common/pstring.h"
#include "../../common/text_file.h"

using namespace std;

class CardGame {
private:
    PString p_content;

    static vector<int> transformSpacedNumbersToIntVector (string spaced_numbers) {
        PString spaced_numbers_pstr(std::move(spaced_numbers));
        vector<string> number_vector_str = spaced_numbers_pstr.split(" ");
        vector<int> number_vector_int;
        number_vector_int.reserve(number_vector_str.size());
        for (const string& number : number_vector_str) {
            number_vector_int.push_back(stoi(number));
        }
        return number_vector_int;
    }
public:
    string content;
    int game_id;
    vector <int> win_numbers;
    vector <int> game_numbers;
    int points;

    CardGame(const string& content) : content(content), p_content(content){
    }

    void findGameID() {
        string game_id_str = p_content.split(":")[0];
        game_id = stoi(game_id_str.substr(4, string::npos));
    }

    void findWinNumbers() {
        int double_point_pos = (int) content.find(':');
        int bar_pos = (int) content.find('|');
        string win_numbers_str = content.substr(double_point_pos+1, bar_pos - double_point_pos - 1);
        win_numbers = transformSpacedNumbersToIntVector(win_numbers_str);
    }

    void findGameNumbers() {
        int bar_pos = (int) content.find('|');
        string game_numbers_str = content.substr(bar_pos+1, string::npos);
        game_numbers = transformSpacedNumbersToIntVector(game_numbers_str);
    }

    void countPoints() {
        findWinNumbers();
        findGameNumbers();

        int number_of_success = 0;
        for (int win_number : win_numbers) {
            if (find(game_numbers.begin(), game_numbers.end(), win_number) != game_numbers.end()) {
                number_of_success++;
            }

            if (number_of_success == 0) {
                points = 0;
            }
            else {
                points = (int) pow(2, number_of_success - 1);
            }
        }
    }
};

int main() {
    TextFile f("/home/rmartinezdelacruz/Code/personal/advent_of_code_2023/days/day4/input4");
    int total_points = 0;

    while (true) {
        string line = f.next();

        if (line.empty()) {
            break;
        }

        CardGame card_game(line);
        card_game.countPoints();
        total_points += card_game.points;

    }

    cout << total_points;
}