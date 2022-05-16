
#ifndef PAWN_H
#define PAWN_H
#include "pieces.h"

class Pawn: public Piece {
    public:
        Pawn(const Pair &position, bool white);
        void setAvailableMoves() override;
        void moveUp();
        void capture();
        void enpassantCapture();
        void setAvailableMoves(bool calledFromKing);
        bool successfulMove(const Pair &position) override;
        
    private:
        bool enpassant;
};
#endif
