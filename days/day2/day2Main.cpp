#include <iostream>
#include <string>
#include <vector>
#include "../../common/text_file.h"
#include "../../common/pstring.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> BAG_COLOR_CONFIG = {12, 13, 14};  // no of cubes in the bag. red, green, blue (RGB)
int PART = 2;

int getGameNumber(string &line) {
    stringstream ss(line);
    string word;
    ss >> word;
    ss >> word;
    return stoi(word.replace(word.end() - 1, word.end(), ""));
}

vector<string> getGameHands(const string& line) {
    PString line_no_game(line.substr(line.find(':') + 1, line.size() - 1));
    return line_no_game.split(";");
}

vector<int> getRGBHandVector(const string& game_hand_) {
    int r = 0;
    int g = 0;
    int b = 0;
    PString game_hand(game_hand_);

    for (string& cube_ : game_hand.split(",")) {
        PString cube(cube_);
        vector<string> cube_vector = cube.split(" ");

        if (cube_vector[1] == "red") {
           r = stoi(cube_vector[0]);
        }
        else if (cube_vector[1] == "green") {
            g = stoi(cube_vector[0]);
        }
        else if (cube_vector[1] == "blue") {
            b = stoi(cube_vector[0]);
        }
    }
    return vector<int> {r, g, b};
}

bool isHandPossible (const vector<int>& hand_rgb, const vector<int>& bag_rgb_config = BAG_COLOR_CONFIG) {
    for (int i=0; i<hand_rgb.size(); i++) {
        if (hand_rgb[i] > bag_rgb_config[i]) {
            return false;
        }
    }
    return true;
}

void updateMinNumberOfCubesInBag(vector<int> hand_rgb, vector<int>& current_minimum_number_of_cubes) {
    for (int i=0; i<hand_rgb.size(); i++) {
        if (hand_rgb[i] > current_minimum_number_of_cubes[i]) {
            current_minimum_number_of_cubes[i] = hand_rgb[i];
        }
    }
}

int main() {

    TextFile f("days/day2/input2");
    int sum_game_numbers = 0;
    int sum_minimum_cubes_powers = 0;

    while (true) {
        string line = f.next();
        if (line.empty()) {
            break;
        }

        if (PART == 1) {
            bool game_possible = true;
            for (const string &hand: getGameHands(line)) {
                if (!isHandPossible(getRGBHandVector(hand))) {
                    game_possible = false;
                    break;
                }
            }
            if (game_possible) {
                sum_game_numbers += getGameNumber(line);
            }
        }

        if (PART == 2) {
            vector<int> current_minimum_number_of_cubes = {0, 0, 0};
            for (const string &hand: getGameHands(line)) {
                updateMinNumberOfCubesInBag(getRGBHandVector(hand), current_minimum_number_of_cubes);
            }
            sum_minimum_cubes_powers += current_minimum_number_of_cubes[0]*
                                        current_minimum_number_of_cubes[1]*
                                        current_minimum_number_of_cubes[2];
        }
    }

    switch (PART) {
        case 1:
            cout << sum_game_numbers;
            break;
        case 2:
            cout << sum_minimum_cubes_powers;
            break;
        default:
            cout << "Part not valid. Choose 1 or 2";
    }
}