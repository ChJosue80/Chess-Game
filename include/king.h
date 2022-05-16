
#ifndef KING_H
#define KING_H
#include <stack>
#include <vector>
#include <unordered_set>
#include "rooke.h"
#include "pieces.h"


class King: public Piece {
    public:
        King(const Pair &position, bool white);
        void setAvailableMoves() override;
        bool successfulMove(const Pair &position) override;

    private:
        std::unordered_set<Pair, Hash> opponentMoves;
        std::vector<Piece*> opponents;
        Piece* kingSideRooke;
        Piece* queenSideRooke;

        void setOpponents();
        void setOpponentMoves();
        void removeMoves();
        void pawnMoves(Piece* pawn);
        void knightMoves(Piece *knight);
        void kingMoves(Piece* king);
        void bishopMoves(Piece* bishop);
        void rookeMoves(Piece* rooke);
        void queenMoves(Piece* queen);
        bool setOpponentMove(const Pair &position);
        void traverse(Pair position, const Pair &increment);

        void castle();
        bool kingInCheck();
        bool clearPath(int);

        void moveRookeTo(Piece* rooke, const Pair &position);

};
#endif
