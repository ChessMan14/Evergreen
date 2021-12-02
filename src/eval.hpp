//eval.hpp (for evaluating chess positions)

#include <vector>
#include "Pugs-vs-Bears/board.h"

int some_number(char symbol, Colour colour, ChessBoard* board);							//Get the number of time a certain piece is on the board for a ceratain color

int quarintined_pawns(Colour colour, ChessBoard* board);								//Get the number of isolated pawns a certain color has

int duplo(Colour colour, ChessBoard* board);								//Get the number of doubled pawns a ceratin color has

double eval(ChessBoard* board);															//Returns the advantage (not planning ahead) that a certain color has given a board position (positive = white advantage, negative = black advantage)