#include "queen.h"

Queen::Queen(const Pair &position, bool white) : 
    Piece(position, white) {
        name = "Queen";
    }

void Queen::setAvailableMoves() {
    availableMoves.clear();
    traverse(position, Pair(1, 0));
    traverse(position, Pair(-1, 0));
    traverse(position, Pair(0, 1));
    traverse(position, Pair(0, -1));
    traverse(position, Pair(1, 1));
    traverse(position, Pair(-1, -1));
    traverse(position, Pair(1, -1));
    traverse(position, Pair(-1, 1));
}

void Queen::traverse(Pair position, const Pair &increment) {
    position.first += increment.first;
    position.second += increment.second;

    if (Piece::setAvailableMoves(position)) {
        traverse(position, increment);
    }
}