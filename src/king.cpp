

#include "king.h"

King::King(const Pair &position, bool white) :
    Piece(position, white) {
    name = "King";

    kingSideRooke = nullptr;
    queenSideRooke = nullptr;
    std::unordered_set<Pair, Hash> opponentMoves;
    std::vector<Piece*> opponents;
}

void King::setAvailableMoves() {
    availableMoves.clear();

    Piece::setAvailableMoves(Pair(position.first + 1, position.second));
    Piece::setAvailableMoves(Pair(position.first - 1, position.second));
    Piece::setAvailableMoves(Pair(position.first, position.second + 1));
    Piece::setAvailableMoves(Pair(position.first, position.second - 1));
    Piece::setAvailableMoves(Pair(position.first + 1, position.second + 1));
    Piece::setAvailableMoves(Pair(position.first + 1, position.second - 1));
    Piece::setAvailableMoves(Pair(position.first - 1, position.second + 1));
    Piece::setAvailableMoves(Pair(position.first - 1, position.second - 1));
    availableMoves.insert(position); // can stay in current position, not in check

    setOpponents();
    setOpponentMoves();
    removeMoves();

    castle();
}

void King::setOpponents() {
    opponents.clear();
    for (const auto &piece : piecesInPlay) {
        if (piece.second->isWhite() != this->white)
            opponents.push_back(piece.second);
    }
}

void King::setOpponentMoves() {
    opponentMoves.clear();
    for (const auto &opponent : opponents) {
        if (opponent->getName() == "Pawn") {
            pawnMoves(opponent);
        } else if (opponent->getName() == "Knight") {
            knightMoves(opponent);
        } else if (opponent->getName() == "Bishop") {
            bishopMoves(opponent);
        } else if (opponent->getName() == "Rooke") {
            rookeMoves(opponent);
        } else if (opponent->getName() == "Queen") {
            queenMoves(opponent);
        } else if (opponent->getName() == "Knig") {
            kingMoves(opponent);
        } 
    }
}
void King::removeMoves() {
    auto itr = availableMoves.begin();
    while (itr != availableMoves.end()) {
        if (opponentMoves.find(*itr) != opponentMoves.end()) {
            availableMoves.erase(itr++);
        } else {
            itr++;
        }
    }
}

void King::pawnMoves(Piece* pawn) {
    int increment = (pawn->isWhite()) ? 1 : -1;
    Pair position = pawn->getPosition();
    position.second += increment;

    position.first += 1;
    setOpponentMove(position);
    position.first -=2;
    setOpponentMove(position);
}

void King::knightMoves(Piece* knight) {
    Pair position = knight->getPosition();

    setOpponentMove( Pair(position.first + 2, position.second + 1) );
    setOpponentMove( Pair(position.first + 2, position.second - 1) );
    setOpponentMove( Pair(position.first - 2, position.second + 1) );
    setOpponentMove( Pair(position.first - 2, position.second - 1) );
    setOpponentMove( Pair(position.first + 1, position.second + 2) );
    setOpponentMove( Pair(position.first - 1, position.second + 2) );
    setOpponentMove( Pair(position.first + 1, position.second - 2) );
    setOpponentMove( Pair(position.first - 1, position.second - 2) );
}

void King::kingMoves(Piece* king) {
    Pair position = king->getPosition();

    setOpponentMove(Pair(position.first + 1, position.second));
    setOpponentMove(Pair(position.first - 1, position.second));
    setOpponentMove(Pair(position.first, position.second + 1));
    setOpponentMove(Pair(position.first, position.second - 1));
    setOpponentMove(Pair(position.first + 1, position.second + 1));
    setOpponentMove(Pair(position.first + 1, position.second - 1));
    setOpponentMove(Pair(position.first - 1, position.second + 1));
    setOpponentMove(Pair(position.first - 1, position.second - 1));
}

void King::bishopMoves(Piece* bishop) {
    Pair position = bishop->getPosition();

    traverse(position, Pair(1, 1)); // up-right
    traverse(position, Pair(-1, -1)); // down-left
    traverse(position, Pair(1, -1)); // up-left
    traverse(position, Pair(-1, 1)); // down-right
}
void King::rookeMoves(Piece* rooke) {
    Pair position = rooke->getPosition();

    traverse(position, Pair(1, 0)); // up
    traverse(position, Pair(-1, 0)); // down
    traverse(position, Pair(0, 1)); // right
    traverse(position, Pair(0, -1)); // left
}

void King::queenMoves(Piece* queen) {
    rookeMoves(queen);
    bishopMoves(queen);
}

bool King::setOpponentMove(const Pair &position) {
    if (!onTheBoard(position))
        return false;
        
    opponentMoves.insert(position);
    return emptyBoardSquare(position);
}

void King::traverse(Pair position, const Pair &increment) {
    position.first += increment.first;
    position.second += increment.second;

    if (setOpponentMove(position)) {
        traverse(position, increment);
    }
}

void King::castle() {
    if (moved || kingInCheck())
        return;

    int rank = (white) ? 0 : 7;
    kingSideRooke = getPieceAt(Pair(7, rank));
    queenSideRooke = getPieceAt(Pair(0, rank));

    if (kingSideRooke != nullptr && !kingSideRooke->getMoved() &&
        kingSideRooke->getName() == "Rooke" && clearPath(2)) {
            availableMoves.insert(Pair(position.first + 2, rank));
        }

    if (queenSideRooke != nullptr &&  !queenSideRooke->getMoved() &&
        queenSideRooke->getName() == "Rooke" && clearPath(-3)) {
            availableMoves.insert(Pair(position.first - 2, rank));
        }
}

bool King::kingInCheck() {
    return availableMoves.find(position) == availableMoves.end();
}

bool King::clearPath(int count) {
    int rank = position.second, file = position.first;

    if (count == -3) {
        if (!emptyBoardSquare(Pair(file + count, rank))) {
            return false;
        }
        count++;
    }

    while (count != 0) {
        Pair tempPosition(file + count, rank);
        if (opponentMoves.find(tempPosition) != opponentMoves.end() ||
            !emptyBoardSquare(tempPosition)) {
            return false;
        }

        count += (count > 0) ? -1 : 1;
    }
    return true;
}

bool King::successfulMove(const Pair &position) {
    bool kingIsCastling = abs(this->position.first - position.first) == 2;

    if (Piece::successfulMove(position)) {
        if (kingIsCastling) {
            if (this->position.first == 6) {
                moveRookeTo(kingSideRooke, Pair(position.first - 1, position.second));
            } else {
                moveRookeTo(queenSideRooke, Pair(position.first + 1, position.second ));
            }   
        }
        return true;
    }
    return false;
}

void King::moveRookeTo(Piece* rooke, const Pair &position) {
    piecesInPlay[position] = rooke;
    piecesInPlay.erase(rooke->getPosition());
    rooke->setPosition(position);
    rooke->setMoved(true);
}