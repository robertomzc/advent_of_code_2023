#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../../common/text_file.h"

using namespace std;

int PART = 2;

class machineNumber {
public:
    int value;
    int row; // line where the character is stored
    int start_column;  // Position in the line where the number starts
    int end_column;  // Position in the line where the number finishes
    int length; // number of digits
    string surrounding; // frame around the number
};

class Gear {
public:
    int row;
    int column;
    vector<machineNumber*> adjacent_machine_numbers;

    void updateAdjacentMachineNumbers(const vector<machineNumber*>& machine_numbers) {
        for (machineNumber* machine_number : machine_numbers) {

            if (machine_number->row > this->row + 1) {  // Ordered by row
                break;
            }

            for (int i=0; i<machine_number->surrounding.length(); i++) {
                if (machine_number->surrounding[i] == '*') {
                    int found_gear_row;
                    int found_gear_column;

                    if (i <= machine_number->length + 1) {  //The asterisk is in the upper row
                        found_gear_row = machine_number->row - 1;
                        found_gear_column = machine_number->start_column + i - 1;
                    }
                    else if (i == machine_number->length + 2)  {  // The asterisk is in front of the number
                        found_gear_row = machine_number->row;
                        found_gear_column = machine_number->start_column - 1;
                    }
                    else if (i == machine_number->length + 3)  {  // The asterisk is in front of the number
                        found_gear_row = machine_number->row;
                        found_gear_column = machine_number->end_column + 1;
                    }
                    else {  // The asterisk is on the lower row
                        found_gear_row = machine_number->row + 1;
                        found_gear_column = machine_number->start_column + (i - machine_number->length - 5);
                    }

                    if (found_gear_column == this->column and found_gear_row == this->row) {  // Bingo
                        this->adjacent_machine_numbers.push_back(machine_number);
                    }
                }
            }
        }
    }
};

vector<machineNumber*> findMachineNumbersInLine (string &line) {
    // Initialize new_number
    string new_number;
    bool reading_new_number = false;

    vector<machineNumber*> line_machine_numbers;
    machineNumber * machine_number;

    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (isdigit(c)) {
            if (reading_new_number) {
                new_number.push_back(c);
            }
            else {
                machine_number = new machineNumber{};
                new_number = &c;
                machine_number->start_column = i;
                reading_new_number = true;
            }
        }
        else {
            if (reading_new_number) { // We finished reading the new number, we append it and write its coordinates
                reading_new_number = false;
                machine_number->value = stoi(new_number);
                machine_number->end_column = i - 1;
                machine_number->length = machine_number->end_column - machine_number->start_column + 1;
                line_machine_numbers.push_back(machine_number);
            }
        }
    }
    return line_machine_numbers;
}

void updateRowInLineMachineNumbers(const vector<machineNumber*>& line_machine_numbers, int line_number) {
    for (machineNumber *machine_number : line_machine_numbers) {
        machine_number->row = line_number;
    }
}

void getMachineNumberSurrounding(machineNumber* machine_number, const vector<string> &text) {

    machine_number->surrounding += text[machine_number->row - 1].substr(machine_number->start_column - 1, machine_number->length + 2) +
            text[machine_number->row][machine_number->start_column - 1] +
            text[machine_number->row][machine_number->end_column + 1] +
            text[machine_number->row + 1].substr(machine_number->start_column - 1, machine_number->length + 2);

}

bool isMachineNumberPartNumber (machineNumber* machine_number) {

    for (char& c : machine_number->surrounding) {
        if (!isdigit(c) and c != '.') {
            return true;
        }
    }
    return false;
}

vector<Gear*> findPossibleGears(const vector<string>& text) {
    vector<Gear*> all_gears;

    for (int row = 0; row < text.size(); row++) {
        string line = text[row];
        for (int col = 0; col < line.length(); col++) {
            if (line[col] == '*') {
                auto* gear = new(Gear);
                gear->row = row;
                gear->column = col;
                all_gears.push_back(gear);
            }
        }
    }
    return all_gears;
}
int main () {
    string input_file_path = "/home/rmartinezdelacruz/Code/personal/advent_of_code_2023/days/day3/input3";
    TextFile f(input_file_path);

    vector<string> text = f.readWithFrame('.');
    vector<machineNumber*> machine_numbers;
    int line_number = 0;

    // Extract all numbers from the text
    for (string& line : text) {
        vector<machineNumber*> new_machine_numbers = findMachineNumbersInLine(line);
        updateRowInLineMachineNumbers(new_machine_numbers, line_number);
        machine_numbers.insert(machine_numbers.end(), new_machine_numbers.begin(), new_machine_numbers.end());
        line_number++;
    }

    if (PART == 1) {
        int part_numbers_sum = 0;
        for (machineNumber *machine_number: machine_numbers) {
            getMachineNumberSurrounding(machine_number, text);
            if (isMachineNumberPartNumber(machine_number)) {
                part_numbers_sum += machine_number->value;
            }
        }
        cout << part_numbers_sum;
    }

    if (PART == 2) {
        int gear_number_sum = 0;
        vector<Gear*> all_gears = findPossibleGears(text);

        for (machineNumber *machine_number: machine_numbers) {
            getMachineNumberSurrounding(machine_number, text);
        }

        for (Gear* gear : all_gears) {
            gear->updateAdjacentMachineNumbers(machine_numbers);
            if (gear->adjacent_machine_numbers.size() == 2) {
                gear_number_sum += gear->adjacent_machine_numbers[0]->value * gear->adjacent_machine_numbers[1]->value;
            }
        }
        cout << gear_number_sum;
    }

    return 0;
}