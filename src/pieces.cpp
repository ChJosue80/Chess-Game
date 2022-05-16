
#include "pieces.h"

int Piece::numberOfPieces = 0;
std::unordered_map<Pair, Piece*, Hash> Piece::piecesInPlay;
std::tuple<std::string, Pair, Pair> 
    Piece::previousMove = std::make_tuple("", Pair(-1, -1), Pair(-1, -1));

Piece::Piece(const Pair &position, bool white) {
    moved = false;
    this->position = position;
    this->white = white;
    piecesInPlay[position] = this;
    numberOfPieces++;
}

Piece* Piece::getPieceAt(const Pair &position) { 
    if (piecesInPlay.find(position) != piecesInPlay.end()) {
        return piecesInPlay.find(position)->second;
    }
    return nullptr;
}

Piece* Piece::erasePiece(Piece* piece) {
    piecesInPlay.erase(piece->getPosition());     
    return piece;
}

bool Piece::successfulMove(const Pair &position) {
    if (validMove(position)) {
        setPreviousMove(position);
        moveTo(position);
        return true;
    }
    return false;
}
bool Piece::validMove(const Pair &position) const {
    return this->position != position &&
    availableMoves.find(position) != availableMoves.end();
}
void Piece::moveTo(const Pair &position) {
    piecesInPlay[position] = this;
    piecesInPlay.erase(this->position);
    this->position = position;
    moved = true;
}

void Piece::setPreviousMove(const Pair &position) {
    previousMove = 
        std::make_tuple(this->name, this->position, position);
}

/**
 * @return true if it is an empty square or a square that has a 
 * piece that can be captured else false
 */
bool Piece::setAvailableMoves(const Pair &position) {
    if (onTheBoard(position)) {
        if (emptyBoardSquare(position)) {
            availableMoves.insert(position);
            return true;
        } else if (captureBoardSquare(position)) {
            availableMoves.insert(position);
        }
    }

    return false;
}

bool Piece::onTheBoard(const Pair &position) const {
    return 0 <= position.first && position.first < 8 &&
           0 <= position.second && position.second < 8;
}

bool Piece::captureBoardSquare(const Pair &position) const {
    return piecesInPlay.find(position) != piecesInPlay.end() &&
           this->white != piecesInPlay[position]->isWhite();
}

bool Piece::emptyBoardSquare(const Pair &position) const {
    return piecesInPlay.find(position) == piecesInPlay.end();
}

Piece::~Piece() {
    numberOfPieces--;
    if (numberOfPieces == 0) {
        piecesInPlay.clear();
    }
}
