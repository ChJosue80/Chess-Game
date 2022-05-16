
#ifndef PIECES_H
#define PIECES_H

#include <string>
#include <tuple>
#include <utility>
#include <unordered_set>
#include <unordered_map>

class Hash {
    public:
        size_t operator()(const std::pair<int, int> &p) const {
            std::hash<int> hash1;
            return hash1(p.first * 10 + p.second);
        }
};

class Piece;
typedef std::pair<int, int> Pair;
typedef std::unordered_set<Pair, Hash> Set;
typedef std::unordered_map<Pair, Piece*, Hash> Map;

class Piece {
    public:
        Piece(const Pair &position, bool white);

        bool isWhite() const { return white; }
        Pair getPosition() const { return position; }
        std::string getName() const { return name;}
        int getMoved() const { return moved; }
        Set getAvailableMoves() const { return availableMoves; }

        static Piece* getPieceAt(const Pair &position);
        static Piece* erasePiece(Piece* piece);

        virtual void setAvailableMoves()=0;
        virtual bool successfulMove(const Pair &position);
        void setPosition(const Pair &position) { this->position = position; }
        void setMoved(bool moved) { this->moved = moved; }

        virtual ~Piece();

    protected:
        static int numberOfPieces;
        static Map piecesInPlay;
        // piece name, from position, to position
        static std::tuple<std::string, Pair, Pair> previousMove;

        Pair position;
        bool white;
        bool moved;
        std::string name;
        Set availableMoves;

        bool validMove(const Pair &position) const;
        void moveTo(const Pair &position);
        void setPreviousMove(const Pair &position);
        bool setAvailableMoves(const Pair &position);
        bool onTheBoard(const Pair &position) const;
        bool emptyBoardSquare(const Pair &positon) const;
        bool captureBoardSquare(const Pair &position) const;
};
#endif