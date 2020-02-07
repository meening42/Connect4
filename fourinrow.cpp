#include "fourinrow.h"

FourInRow::FourInRow(QWidget* pParent) :
    QWidget(pParent)
{

}

void FourInRow::paintEvent(QPaintEvent *event){
    QPainter P(this);
    P.setPen(QPen(Qt::blue, 4));
    int multiplyer;
    // draw vertical lines
    multiplyer = width()/BOARD_WIDTH;
    for(int i = 0; i<=BOARD_WIDTH;++i){
        P.drawLine(multiplyer*i,0,multiplyer*i,height());
    }
    // draw horizontal lines
    multiplyer = height()/BOARD_HEIGHT;
    for(int j = 0;j<=BOARD_HEIGHT;++j){
        P.drawLine(0,multiplyer*j, width() ,multiplyer*j);
    }
}


