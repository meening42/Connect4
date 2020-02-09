#include "fourinrow.h"

FourInRow::FourInRow(QWidget* pParent) :
    QWidget(pParent)
{
    selectedRow = 0;
    playerOnMove = red;
    qDebug()<<"constructor called ";
}



void FourInRow::paintEvent(QPaintEvent *event){
    QPainter P(this);
    int multiplyer;

    // draw circle
    if (playerOnMove == red){
        P.setPen(QPen(Qt::darkRed, 2));
        P.setBrush(Qt::red);
    }
    else{
        P.setPen(QPen(Qt::darkYellow, 2));
        P.setBrush(Qt::yellow);
    }
    multiplyer = (width()-(2*MARGIN))/BOARD_WIDTH;
    int circleSize = SQUARE_SIZE- 2*MARGIN;
    P.drawEllipse((2*MARGIN)+selectedRow*multiplyer,2*MARGIN,circleSize,circleSize);

    //draw vertical lines
    P.setPen(QPen(Qt::blue, 10));
    multiplyer = (width()-(2*MARGIN))/BOARD_WIDTH;
    for(int i = 0; i<=BOARD_WIDTH;++i){
        P.drawLine(multiplyer*i+MARGIN,MARGIN+SQUARE_SIZE,multiplyer*i+MARGIN,height()-MARGIN);
    }
    // draw horizontal lines
    multiplyer = (height()-SQUARE_SIZE-(2*MARGIN))/BOARD_HEIGHT;
    for(int j = 0;j<=BOARD_HEIGHT;++j){
        P.drawLine(MARGIN,multiplyer*j+MARGIN+SQUARE_SIZE, width()-MARGIN ,multiplyer*j+MARGIN+SQUARE_SIZE);
    }

}

void FourInRow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Right)
    {
        qDebug()<<"Right Key pressed ";
        if(selectedRow < BOARD_WIDTH-1){
            selectedRow+=1;
            qDebug()<<selectedRow;
        }
    }
    if(event->key() == Qt::Key_Left)
    {
        qDebug()<<"Left Key pressed ";
        if(selectedRow >0){
            selectedRow-=1;
            qDebug()<<selectedRow;
        }
    }
    if((event->key() == Qt::Key_Space) || (event->key() == Qt::Key_Down))
    {
        qDebug()<<"Down Key pressed ";
    }

    update();
}




