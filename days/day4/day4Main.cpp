#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
#include <array>
#include <numeric>
#include "../../common/pstring.h"
#include "../../common/text_file.h"

using namespace std;

int PART = 2;

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
    int successes;
    int points;

    explicit CardGame(const string& content) : content(content), p_content(content){
        findGameID();
        findWinNumbers();
        findGameNumbers();
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

    void countNumberOfSuccesses() {
        // Count how many of your game numbers are in the win numbers
        successes = 0;
        for (int win_number : win_numbers) {
            if (find(game_numbers.begin(), game_numbers.end(), win_number) != game_numbers.end()) {
                successes++;
            }
        }
    }

    void countPoints() {

        countNumberOfSuccesses();

        if (successes == 0) {
            points = 0;
        }
        else {
            points = (int) pow(2, successes - 1);
        }
    }
};

int main() {
    TextFile f("/home/rmartinezdelacruz/Code/personal/advent_of_code_2023/days/day4/input4");
    int total_points = 0;


    if (PART == 1) {
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

    else if (PART == 2) {
        vector<CardGame> all_cards;
        while (true) {
            string line = f.next();

            if (line.empty()) {
                break;
            }
            CardGame card_game(line);
            card_game.countNumberOfSuccesses();
            all_cards.push_back(card_game);
        }

        vector<int> number_of_each_card(all_cards.size(), 1);
        for (int i=0; i<all_cards.size(); i++) {
            for (int j=1; j<=all_cards[i].successes; j++) {
                // Add 1*number_of_i_cards to the next i+j card
                number_of_each_card[i+j] += 1*number_of_each_card[i];
            }
        }
        cout << accumulate(number_of_each_card.begin(), number_of_each_card.end(), 0);
    }
}