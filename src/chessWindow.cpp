
#include "chessWindow.h"

ChessWindow::ChessWindow(QWidget* parent): QWidget(parent) {
    grid = new QGridLayout(this);

    whiteTurn = true;
    correctColorPiece = false;
    piece = nullptr;
    started = false;

    whiteKing = nullptr;
    blackKing = nullptr;
    whiteKingInCheck = false;
    blackKingInCheck = false;

    this->setUpBoardSquares();
    this->setStartingPieces();
    this->setImage();
    this->setColor();
}

void ChessWindow::setUpBoardSquares() {
    for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {
            Pair position(file, rank);

            QPushButton* button = new QPushButton(this);
            int width = 75, height = 75;
            button ->resize(QSize(width, height));
            button ->setMinimumWidth(width);
            button ->setMinimumHeight(height);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            
            connect(button, &QPushButton::clicked, [this, position] { clicked(position); });
            grid->addWidget(button, 8 - rank, file);
            chessBoard[position] = button;
        }
    }
}

void ChessWindow::setStartingPieces() {
    for (int file = 0; file < 8; file++) {
        bool white = true;

        Pair blackPawnPosition(file, 6);
        Pair whitePawnPosition(file, 1);
        startingPieces.insert(new Pawn(whitePawnPosition, white));
        startingPieces.insert(new Pawn(blackPawnPosition, !white));

        Pair whitePosition(file, 0);
        Pair blackPosition(file, 7);
        if (file == 0 || file == 7) {
            startingPieces.insert(new Rooke(whitePosition, white));
            startingPieces.insert(new Rooke(blackPosition, !white));
        } else if (file == 1 || file == 6) {
            startingPieces.insert(new Knight(whitePosition, white));
            startingPieces.insert(new Knight(blackPosition, !white));
        } else if (file == 2 || file == 5) {
            startingPieces.insert(new Bishop(whitePosition, white));
            startingPieces.insert(new Bishop(blackPosition, !white));
        } else if (file == 3) {
            startingPieces.insert(new Queen(whitePosition, white));
            startingPieces.insert(new Queen(blackPosition, !white));
        } else {
            whiteKing = new King(whitePosition, white);
            blackKing = new King(blackPosition, !white);
            startingPieces.insert(whiteKing);
            startingPieces.insert(blackKing);
        }
    }
}

void ChessWindow::setColor() {
    QString color1 = "background-color: rgb(160, 82, 45)";
    QString color2 = "background-color: rgb(234, 221, 202)";

    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            Pair position(file, rank);
            if ( (rank % 2 == 0 && file% 2 == 0) ||
                 (rank % 2 != 0 && file % 2 != 0) ) {
                chessBoard[position]->setStyleSheet(color1);
            } else {
                chessBoard[position]->setStyleSheet(color2);
            }
        }
    }
}

void ChessWindow::setImage() {
    for(auto itr = chessBoard.begin(); itr != chessBoard.end(); itr++) {
        Piece* chessPiece = Piece::getPieceAt(itr->first);
        QPushButton* button = itr->second;

        if (chessPiece != nullptr ) {
            QString imagePath = this->getImagePath(chessPiece);
            button->setIcon(QIcon(QPixmap(imagePath)));
            button->setIconSize(QSize(50, 40));
        } else {
            button->setIcon(QIcon());
        }
    }
}

void ChessWindow::highLightAvailableMoves(Piece* piece) {
    piece->setAvailableMoves();
    for (auto position : piece->getAvailableMoves()) {
        if (piece->getPosition() != position) {
            chessBoard[position]->setStyleSheet("background-color: rgb(173,216,230)");
        }
    }
}

void ChessWindow::movePieceFrom(Pair position) {
    piece = Piece::getPieceAt(position);
    if (piece == nullptr) {
        correctColorPiece = false;
        return;
    }

    if (this->whiteTurn && piece->isWhite() ||
        !this->whiteTurn && !piece->isWhite() ) {
        highLightAvailableMoves(piece);
        correctColorPiece = true;
    } else {
        correctColorPiece = false;
    }
}

bool ChessWindow::movePieceTo(Pair position) {
    if (correctColorPiece && piece->successfulMove(position)) {
        whiteTurn = !whiteTurn;
        correctColorPiece = false;
        pawnPromotion();
        setImage();
        kingInCheck();
        return true;
    }
    return false;
}

bool ChessWindow::kingInCheck() {
    Piece* king = (whiteTurn) ? whiteKing : king = blackKing;
    king->setAvailableMoves();

    std::unordered_set<Pair, Hash> moves = king->getAvailableMoves();
    Pair position = king->getPosition();

    if (moves.find(position) == moves.end()) {
        chessBoard[position]->setStyleSheet("background-color: rgb(204, 0, 0)");
        return true;
    }
    return false;
}

void ChessWindow::pawnPromotion() {
    if (piece->getName() != "Pawn")
        return;

    if (piece->getPosition().second != 7 && 
        piece->getPosition().second != 0) {
            return;
        }

    QDialog promote(this);
    promote.setModal(true);
    promote.resize(300, 300);
    Piece* piece = Piece::erasePiece(this->piece);

    QVBoxLayout box(&promote);
    QRadioButton bishop(tr("Bishop"));
    QRadioButton rooke(tr("rooke"));
    QRadioButton knight(tr("knight"));
    QRadioButton queen(tr("queen"));
    QPushButton button("Correct", &promote);
    int test = 1;
    connect(&button, &QPushButton::clicked,
        [&promote, &bishop, &rooke, &knight, &queen, &test] () {
        if (bishop.isChecked() || rooke.isChecked() ||
            knight.isChecked() || queen.isChecked()) {
                promote.close();
        } });

    box.addWidget(&bishop);
    box.addWidget(&rooke);
    box.addWidget(&knight);
    box.addWidget(&queen);
    box.addWidget(&button);
    promote.exec();

    if (bishop.isChecked()) {
        startingPieces.insert(new Bishop(piece->getPosition(), piece->isWhite()));
    } else if (rooke.isChecked()) {
        startingPieces.insert(new Rooke(piece->getPosition(), piece->isWhite()));
    } else if (knight.isChecked()) {
        startingPieces.insert(new Knight(piece->getPosition(), piece->isWhite()));
    } else if (queen.isChecked()) {
        startingPieces.insert(new Queen(piece->getPosition(), piece->isWhite()));
    }
}


void ChessWindow::clicked(Pair position) {
    this->setColor();
    if (!movePieceTo(position)) {
        movePieceFrom(position);
    }
}

ChessWindow::~ChessWindow() {
    delete grid;
    grid = nullptr;
    piece = nullptr;
    whiteKing = nullptr;
    blackKing = nullptr;

    for(auto itr = startingPieces.begin(); itr != startingPieces.end(); itr++) {
        delete *itr;
    }
    for(auto itr = chessBoard.begin(); itr != chessBoard.end(); itr++) {
        delete itr->second;
        itr->second = nullptr;
    }
}

QString ChessWindow::getImagePath(Piece* piece) {
    QString color = piece->isWhite() ? "white" : "black";
    QString name =  QString::fromStdString(piece->getName());

    return ":/img/" + color + name + ".png";
}
