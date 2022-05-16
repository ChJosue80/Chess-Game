
#include "knight.h"

Knight::Knight(const Pair &position, bool white) :
    Piece(position, white) {
        name = "Knight";
    }

void Knight::setAvailableMoves() {
    availableMoves.clear();
    
    Piece::setAvailableMoves( Pair(position.first + 2, position.second + 1) );
    Piece::setAvailableMoves( Pair(position.first + 2, position.second - 1) );
    Piece::setAvailableMoves( Pair(position.first - 2, position.second + 1) );
    Piece::setAvailableMoves( Pair(position.first - 2, position.second - 1) );
    Piece::setAvailableMoves( Pair(position.first + 1, position.second + 2) );
    Piece::setAvailableMoves( Pair(position.first - 1, position.second + 2) );
    Piece::setAvailableMoves( Pair(position.first + 1, position.second - 2) );
    Piece::setAvailableMoves( Pair(position.first - 1, position.second - 2) );
}
