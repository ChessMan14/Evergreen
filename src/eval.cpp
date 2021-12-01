//eval.cpp (for evaluating chess positions)

#include "eval.hpp"

int piece_num(char symbol, Colour colour, ChessBoard* board) {
	int num = 0;
	
	for (int i = 0; i < 8; i++) { 
		for (int j = 0; j < 8; j++) {
			if (board->squares[j][i] != NULL) {
				if ((board->squares[j][i]->getSymbol() == symbol) && (board->squares[j][i]->colour == colour)) {
					num++;
				}
			}
		}
	}
	
	return num;
}

int num_isolated_pawns(Colour colour, ChessBoard* board) {
	int isolated_pawns = 0;
	bool files[] = {false, false, false, false, false, false, false, false, false, false};
	
	for (int i = 0; i < 8; i++) { 
		for (int j = 0; j < 8; j++) {
			if (board->squares[i][j] != NULL) {
				if ((board->squares[i][j]->getSymbol() == 'p') && (board->squares[i][j]->colour == colour)) {
					files[i+1] = true;
					break;
				}
			}
		}
	}
	
	for (int i = 1; i < 9; i++) {
		if ((files[i]) && (!(files[i-1])) && (!(files[i+1]))) {
			isolated_pawns++;
		}
	}
	
	return isolated_pawns;
}

int num_doubled_pawns(Colour colour, ChessBoard* board) {
	int doubled_pawns = 0;
	bool file[] = {false, false, false, false, false, false, false, false};
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board->squares[i][j] != NULL) {
				if ((board->squares[i][j]->getSymbol() == 'p') && (board->squares[i][j]->colour == colour)) {
					file[j] = true;
				}
			}
		}
		
		for (int i = 0; i < 7; i++) {
			if ((file[i]) && (file[i+1])) {
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
	
	int wK = piece_num('K', white, board);
	int bK = piece_num('K', black, board);
	int wQ = piece_num('Q', white, board);
	int bQ = piece_num('Q', black, board);
	int wR = piece_num('R', white, board);
	int bR = piece_num('R', black, board);
	int wB = piece_num('B', white, board);
	int bB = piece_num('B', black, board);
	int wN = piece_num('N', white, board);
	int bN = piece_num('N', black, board);
	int wP = piece_num('p', white, board);
	int bP = piece_num('p', black, board);
	
	int wD = num_doubled_pawns(white, board);
	int bD = num_doubled_pawns(black, board);
	int wI = num_isolated_pawns(white, board);
	int bI = num_isolated_pawns(black, board);
	
	int wM = board->getPossibleMoves(white).size();
	int bM = board->getPossibleMoves(black).size();

	return ((200 * (wK-bK)) + (9 * (wQ-bQ)) + (5 * (wR-bR)) + (3 * ((wB-bB)+(wN-bN))) + (1 * (wP-bP)) + (0.5 * ((bD-wD)+(bI-wI))) + (0.1 * (wM-bM)));
}