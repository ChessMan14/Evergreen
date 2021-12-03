#include <stdio.h>
#include <tuple>
#include <iostream>
#include <chrono>
#include <numeric>
#include "eval.hpp"
#include "ansi_escapes.h"

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

int main(void) {
    ChessBoard board = ChessBoard();
	board.moveTo(std::tuple<char, char>(3, 1), std::tuple<char, char>(3, 3));
	board.moveTo(std::tuple<char, char>(4, 6), std::tuple<char, char>(4, 5));
	board.moveTo(std::tuple<char, char>(2, 1), std::tuple<char, char>(2, 3));
	board.moveTo(std::tuple<char, char>(6, 7), std::tuple<char, char>(5, 5));
	board.moveTo(std::tuple<char, char>(6, 0), std::tuple<char, char>(5, 2));
	board.moveTo(std::tuple<char, char>(3, 6), std::tuple<char, char>(3, 4));
	board.moveTo(std::tuple<char, char>(1, 0), std::tuple<char, char>(2, 2));
	board.moveTo(std::tuple<char, char>(3, 4), std::tuple<char, char>(2, 3));
	board.moveTo(std::tuple<char, char>(4, 1), std::tuple<char, char>(4, 2));
	board.moveTo(std::tuple<char, char>(2, 1), std::tuple<char, char>(2, 4));
	board.moveTo(std::tuple<char, char>(5, 0), std::tuple<char, char>(2, 3));
	board.moveTo(std::tuple<char, char>(0, 6), std::tuple<char, char>(0, 5));
	
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
	
	std::vector<double> times;
	
	for (int i = 0; i < 100000; i++) {
		auto t1 = high_resolution_clock::now();
		eval(&board);
		auto t2 = high_resolution_clock::now();

		/* Getting number of milliseconds as a double. */
		duration<double, std::milli> ms_double = t2 - t1;

		times.push_back(ms_double.count());
	}
	
	std::cout << (std::accumulate(times.begin(), times.end(), 0.0 ) / 100000) << " milliseconds" << std::endl;;
	
	print_board(&board);
	
	return 0;
}