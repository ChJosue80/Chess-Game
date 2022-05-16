
#include "pawn.h"
#include <cmath>

Pawn::Pawn(const Pair &position, bool white) :
    Piece(position, white) {
        name = "Pawn";
        enpassant = false;
    }

void Pawn::setAvailableMoves() {
    availableMoves.clear();

    moveUp();
    capture();
    enpassantCapture();
}

void Pawn::moveUp() {
    int increment = (white) ? 1 : -1;
    Pair tempPosition = position;
    tempPosition.second += increment;

    if (onTheBoard(tempPosition) && emptyBoardSquare(tempPosition)) {
        availableMoves.insert(tempPosition);
        tempPosition.second += increment;

        if (!moved && emptyBoardSquare(tempPosition)) {
            availableMoves.insert(tempPosition);
        }
    }
}

void Pawn::capture() {
    int increment = (white) ? 1 : -1;
    Pair tempPosition(position.first + 1, position.second + increment);

    if (onTheBoard(tempPosition) && captureBoardSquare(tempPosition)){
        availableMoves.insert(tempPosition);
    }
    
    tempPosition.first -= 2;
    if (onTheBoard(tempPosition) && captureBoardSquare(tempPosition)) {
        availableMoves.insert(tempPosition);
    }
}

void Pawn::enpassantCapture() {
    enpassant = false;
    Pair toPosition = std::get<2> (previousMove);
    Pair fromPosition = std::get<1> (previousMove);
    if (std::get<0> (previousMove) == "Pawn" && 
        abs(fromPosition.second - toPosition.second) == 2) {
        if (this->white && this->position.second == 4) { // white is in rank 5
            enpassant = true;
            toPosition.second += 1;
            availableMoves.insert(toPosition);
        }
        if (!this->white && this->position.second == 3) { // black is in rank 4
            enpassant = true;
            toPosition.second -= 1;
            availableMoves.insert(toPosition);
        }
    }
}

bool Pawn::successfulMove(const Pair &position) {

    Pair toPosition = std::get<2> (previousMove);

    if (Piece::successfulMove(position)) {
        if (enpassant && abs(toPosition.second - position.second) == 1 &&
            toPosition.first == position.first) {
            piecesInPlay.erase(toPosition);
        }
        return true;
    }
    return false;
}
