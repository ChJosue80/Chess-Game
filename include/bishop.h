

#ifndef BISHOP_H
#define BISHOP_H
#include "pieces.h"

class Bishop: public Piece {
    public:
        Bishop(Pair position, bool white);
        void setAvailableMoves() override;
    private:
        void traverse(Pair position, const Pair &increment);
};
#endif
