//eval.cpp (for evaluating chess positions)

#include "eval.hpp"

int some_number(char symbol, Colour colour, ChessBoard* board) {
	int num = 0;
	
	for (int i = 0; i < 8; i++) { 
		for (int j = 0; j < 8; j++) {
			if (board->squares[j][i] != NULL) {
				if ((board->squares[j][i]->getSymbol() == symbol) and (board->squares[j][i]->colour == colour)) {
					num++;
				}
			}
		}
	}
	
	return num;
}

int quarintined_pawns(Colour colour, ChessBoard* board) {
	int isolated_pawns = 0;
	bool files[] = {false, false, false, false, false, false, false, false, false, false};
	
	for (int i = 0; i < 8; i++) { 
		for (int j = 0; j < 8; j++) {
			if (board->squares[i][j] != NULL) {
				if ((board->squares[i][j]->getSymbol() == 'p') and (board->squares[i][j]->colour == colour)) {
					files[i+1] = true;
					break;
				}
			}
		}
	}
	
	for (int i = 1; i < 9; i++) {
		if ((files[i]) and (!(files[i-1])) and (!(files[i+1]))) {
			isolated_pawns++;
		}
	}
	
	return isolated_pawns;
}

int duplo(Colour colour, ChessBoard* board) {
	int doubled_pawns = 0;
	bool file[] = {false, false, false, false, false, false, false, false};
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board->squares[i][j] != NULL) {
				if ((board->squares[i][j]->getSymbol() == 'p') and (board->squares[i][j]->colour == colour)) {
					file[j] = true;
				}
			}
		}
		
		for (int i = 0; i < 7; i++) {
			if ((file[i]) and (file[i+1])) {
				doubled_pawns++;
				file[i] = false;
			}
			else {
				file[i] = false;
			}
		}
	}
	
	return doubled_pawns;
}

double eval(ChessBoard* board) {
	Colour white = Colour::White;
	Colour black = Colour::Black;
	
	int wK = some_number('K', white, board);
	int bK = some_number('K', black, board);
	int wQ = some_number('Q', white, board);
	int bQ = some_number('Q', black, board);
	int wR = some_number('R', white, board);
	int bR = some_number('R', black, board);
	int wB = some_number('B', white, board);
	int bB = some_number('B', black, board);
	int wN = some_number('N', white, board);
	int bN = some_number('N', black, board);
	int wP = some_number('p', white, board);
	int bP = some_number('p', black, board);
	
	int wD = duplo(white, board);
	int bD = duplo(black, board);
	int wI = quarintined_pawns(white, board);
	int bI = quarintined_pawns(black, board);
	
	int wM = board->getPossibleMoves(white).size();
	int bM = board->getPossibleMoves(black).size();

	return ((200 * (wK-bK)) + (9 * (wQ-bQ)) + (5 * (wR-bR)) + (3 * ((wB-bB)+(wN-bN))) + (1 * (wP-bP)) + (0.5 * ((bD-wD)+(bI-wI))) + (0.1 * (wM-bM)));
}
