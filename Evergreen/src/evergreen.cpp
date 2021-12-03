#include <iostream>
#include <regex>
#include <string>
#include <tuple>
#include <vector>
#include <stdio.h>
#include "ansi_escapes.h"
#include "eval.hpp"
#include "Pugs-vs-Bears/board.h"

void print_board(ChessBoard* board) {
	Colour white = Colour::White;

	setupConsole();
	for (int i = 0; i < 8; i++) { 
		for (int j = 0; j < 8; j++) {
			if (board->squares[j][i] != NULL) {
				if (board->squares[j][i]->colour == white) {
					if (((((j+1) % 2) != 0) && (((i+1) % 2) == 0)) || ((((j+1) % 2) == 0) && (((i+1) % 2) != 0))) {
						printf("\x1b[97m\x1b[44m %c ", board->squares[j][i]->getSymbol());
					}
					else {
						printf("\x1b[97m\x1b[41m %c ", board->squares[j][i]->getSymbol());
					}
				}
				else {
					if (((((j+1) % 2) != 0) && (((i+1) % 2) == 0)) || ((((j+1) % 2) == 0) && (((i+1) % 2) != 0))) {
						printf("\x1b[30m\x1b[44m %c ", board->squares[j][i]->getSymbol());
					}
					else {
						printf("\x1b[30m\x1b[41m %c ", board->squares[j][i]->getSymbol());
					}
				}
			}
			else {
				if (((((j+1) % 2) != 0) && (((i+1) % 2) == 0)) || ((((j+1) % 2) == 0) && (((i+1) % 2) != 0))) {
					printf("\x1b[30m\x1b[44m   ");
				}
				else {
					printf("\x1b[30m\x1b[41m   ");
				}
			}
		}
		printf("\x1b[40m\n");
	}
	restoreConsole();
}

std::vector<std::string> split(std::string str, std::string token){
    std::vector<std::string>result;
    while(str.size()){
        int index = str.find(token);
        if (index!=std::string::npos) {
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if (str.size()==0) {
				result.push_back(str);
			}
        }
		else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

int main() {
	ChessBoard board = ChessBoard();
	std::string user_input;
	std::regex regex("^[0-7], [0-7], [0-7], [0-7]$");
	std::cmatch match;
	MoveData move;
	std::vector<std::string> coords;

	while (true) {
		print_board(&board);
		std::cout << "Please make a move or run a command:" << std::endl;
		std::getline(std::cin, user_input);

		if (user_input == "RESET") {
                        board.resetBoard();
			continue;
                }

		else if (user_input == "EVAL") {
                        std::cout << eval(&board) << std::endl;
			continue;
                }

		else if (std::regex_match(user_input, regex)) {
			coords = split(user_input, ", ");
			move = board.moveTo(std::tuple<char, char>(std::stoi(coords[0]), std::stoi(coords[1])), std::tuple<char, char>(std::stoi(coords[2]), std::stoi(coords[3])));
			std::cout << std::endl;
			if (move.validMove == false) {
				std::cout << "Invalid move" << std::endl;
				coords.clear();
				continue;
			}
			else {
				coords.clear();
			}
		}

		else {
			std::cout << user_input << std::endl;
			std::cout << "Invalid input" << std::endl;
			continue;
		}
	}
}
