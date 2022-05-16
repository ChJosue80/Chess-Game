
#ifndef QUEEN_H
#define QUEEN_H
#include "pieces.h"

class Queen: public Piece {
    public:
        Queen(const Pair &position, bool white);
        void setAvailableMoves() override;
        
    private:
        void traverse(Pair position, const Pair &increment);
};
#endif
