


#include "windowmain.h"


WindowMain::WindowMain(QWidget *parent)
    : QMainWindow(parent)
{   
    setFixedSize(SQUARE_SIZE*BOARD_WIDTH, SQUARE_SIZE*(BOARD_HEIGHT+1));

    QMenu* pMenu = new QMenu("File");
    pMenu->addAction("Quit", this, SLOT(quit()));
    menuBar()->addMenu(pMenu);

    FourInRow* game = new FourInRow(this);
    setCentralWidget(game);
    game->setFocus(Qt::OtherFocusReason);

}

WindowMain::~WindowMain()
{
}

void WindowMain::quit()
{
    //qDebug() << "Quit!";
    QApplication::instance()->quit();
}
