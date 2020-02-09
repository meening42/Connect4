#ifndef WIDGETCENTRAL_H
#define WIDGETCENTRAL_H

#include <QWidget>
#include <QTextEdit>
#include <QPainter>
#include <QPushButton>
#include <QSpinBox>
#include <QKeyEvent>
#include <QDebug>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define SQUARE_SIZE 60
#define MARGIN 10

enum player{
    yellow,
    red,
    empty
};

class FourInRow : public QWidget
{
    Q_OBJECT

public:
    FourInRow(QWidget* pParent = nullptr);
    void showBoard();
    void insertCoinInRow(int row);
    void switchPlayerOnMove();
    void makeMove();
    player checkWinner();
    void initialize();

public slots:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    int selectedRow;
    int margin;
    int squareSize;
    player playerOnMove;
    player board[BOARD_WIDTH][BOARD_HEIGHT];
};

#endif // WIDGETCENTRAL_H
