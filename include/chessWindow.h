#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QPushButton>
#include <QGridLayout>
#include <QRadioButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QtWidgets>

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <utility>
#include "pieces.h"
#include "knight.h"
#include "rooke.h"
#include "pawn.h"
#include "queen.h"
#include "bishop.h"
#include "king.h"

typedef std::pair<int, int> Pair;

class ChessWindow: public QWidget {
    public:
        explicit ChessWindow(QWidget* parent = nullptr);
        void setUpBoardSquares();
        void setStartingPieces();
        void setColor();
        void setImage();
        void highLightAvailableMoves(Piece* piece);
        void movePieceFrom(Pair position);
        bool movePieceTo(Pair position);
        bool kingInCheck();
        void pawnPromotion();
        ~ChessWindow();

    signals:
        void clicked(Pair position);

    private:
        QString getImagePath(Piece* piece);

        bool started;
        bool whiteTurn;
        bool correctColorPiece;
        bool whiteKingInCheck;
        bool blackKingInCheck;
        Piece* piece;
        King* whiteKing;
        King* blackKing;
        QGridLayout *grid;
        std::unordered_set<Piece*> startingPieces;
        std::unordered_map<Pair, QPushButton*, Hash> chessBoard;
};
#endif
