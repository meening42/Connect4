

#include "fourinrow.h"
#include "windowmain.h"

WindowMain::WindowMain(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(500, 300);

    QMenu* pMenu = new QMenu("File");
    pMenu->addAction("Quit", this, SLOT(quit()));
    menuBar()->addMenu(pMenu);

    QPushButton * btn = new QPushButton("hej",this);

    FourInRow* pwc = new FourInRow(this);
    setCentralWidget(pwc);

    QHBoxLayout * layout = new QHBoxLayout;


}

WindowMain::~WindowMain()
{
}

void WindowMain::quit()
{
    //qDebug() << "Quit!";
    QApplication::instance()->quit();
}
