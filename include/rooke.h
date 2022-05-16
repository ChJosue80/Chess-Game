
#ifndef ROOKE_H
#define ROOKE_H
#include "pieces.h"

class Rooke: public Piece {
    public:
        Rooke(const Pair &position, bool white);
        void setAvailableMoves() override;
        
    private:
        void traverse(Pair position, const Pair &increment);
};
#endif
