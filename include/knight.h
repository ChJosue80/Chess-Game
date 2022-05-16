#ifndef KNIGHT_H
#define KNIGHT_H
#include "pieces.h"

class Knight: public Piece {
    public:
        Knight(const Pair &position, bool white);
        void setAvailableMoves() override;
};
#endif