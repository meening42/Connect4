#ifndef WIDGETCENTRAL_H
#define WIDGETCENTRAL_H

#include <QWidget>
#include <QTextEdit>
#include <QPainter>
#include <QPushButton>
#include <QSpinBox>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <tuple>
#include <vector>
#include <QApplication>
#include <QTimer>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define SQUARE_SIZE 60
#define MARGIN 10

enum player{
    yellow,
    red,
    empty
};

struct pos{
    int x;
    int y;
};
class FourInRow : public QWidget
{
    Q_OBJECT

public:
    FourInRow(QWidget* pParent = nullptr);
    void showBoard();
    void insertCoinInRow(int row);
    void switchPlayerOnMove();
    void computerMove();
    player checkWinner(player  Arr[BOARD_WIDTH][BOARD_HEIGHT],bool isVirtualArr);
    void initialize();

public slots:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void control();
private:
    QTimer *ptimer;
    bool checkWinnerSignal;
    bool insertCoin;
    bool gameOver;
    player winner;
    int margin;
    int selectedRow;
    int squareSize;
    bool coinFalling;
    int fallingX;
    int fallingYPos;
    int fallingY;
    int timerId;
    void copyBoradToVirtual();
    std::tuple<bool,int,int> checkPossibleWin(player p);
    player playerOnMove;
    std::vector<struct pos> PositionsYellow;
    std::vector<struct pos> PositionsRed;
    std::vector<struct pos> winningPositionsYellow;
    std::vector<struct pos> winningPositionsRed;
    player board[BOARD_WIDTH][BOARD_HEIGHT];
    player virtualBoard[BOARD_WIDTH][BOARD_HEIGHT];
    bool isDraw();
};

#endif // WIDGETCENTRAL_H
