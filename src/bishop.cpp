
#include "bishop.h"

Bishop::Bishop(Pair position, bool white) : 
    Piece(position, white) {
        name = "Bishop";
    }

void Bishop::setAvailableMoves() {
    availableMoves.clear();
    traverse(position, Pair(1, 1));
    traverse(position, Pair(-1, -1));
    traverse(position, Pair(1, -1));
    traverse(position, Pair(-1, 1));
}

void Bishop::traverse(Pair position, const Pair &increment) {
    position.first += increment.first;
    position.second += increment.second;

    if (Piece::setAvailableMoves(position)) {
        traverse(position, increment);
    }
}