
#include "chessWindow.h"
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLayout>

class mainWindow:public QWidget {
    public:
        mainWindow():QWidget() {
            game = new ChessWindow(this);
            layout = new QGridLayout(this);
            exit = new QPushButton(this);
            restart = new QPushButton(this);

            exit->setText("Exit");
            restart->setText("Restart");
            layout->addWidget(game, 1, 1);
            layout->addWidget(restart, 2, 1);
            layout->addWidget(exit, 3, 1);

            connect(restart, &QPushButton::clicked, [this]{ clicked(); } );
            connect(exit, &QPushButton::clicked, [this]{ QApplication::quit(); });
        }
        
        ~mainWindow() {
            delete game;
            delete layout;
            delete exit;
            delete restart;
        }

    signals:
        void clicked() {
            delete this->game;
            game = new ChessWindow(this);
            layout->addWidget(game, 1, 1);
        }

    private:
        ChessWindow* game;
        QGridLayout* layout;
        QPushButton* exit;
        QPushButton* restart;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow* w = new mainWindow();
    w->show();
    return a.exec();
}
