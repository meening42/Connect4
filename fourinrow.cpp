#include "fourinrow.h"

FourInRow::FourInRow(QWidget* pParent) :
    QWidget(pParent)
{
    selectedRow = 0;
    playerOnMove = red;
    initialize();
    srand(time(NULL));
    qDebug()<<"constructor called ";
}



void FourInRow::paintEvent(QPaintEvent *event){
    QPainter P(this);
    int multiplyer;

    // draw selection circle
    if (playerOnMove == red){
        P.setPen(QPen(Qt::darkRed, 2));
        P.setBrush(Qt::red);
    }
    else{
        P.setPen(QPen(Qt::darkYellow, 2));
        P.setBrush(Qt::yellow);
    }
    multiplyer = (width()-(2*MARGIN))/BOARD_WIDTH;
    int circleSize = SQUARE_SIZE-1.5*MARGIN;
    P.drawEllipse((1.5*MARGIN)+selectedRow*multiplyer,2*MARGIN,circleSize,circleSize);

    // draw circles on borad
    int multiplyerX = (width()-(2*MARGIN))/BOARD_WIDTH;
    int multiplyerY = (width()-SQUARE_SIZE -(4*MARGIN))/BOARD_HEIGHT;
    for(int i= 0;i<BOARD_WIDTH;i++){
        for(int j=0;j<BOARD_HEIGHT;j++){
            if(board[i][j] == red){
                P.setPen(QPen(Qt::darkRed, 3));
                P.setBrush(Qt::red);
                P.drawEllipse(i*multiplyerX+1.5*MARGIN,j*multiplyerY+1.5*MARGIN+SQUARE_SIZE,circleSize,circleSize);
            }
            else if(board[i][j] == yellow){
                P.setPen(QPen(Qt::darkYellow, 3));
                P.setBrush(Qt::yellow);
                P.drawEllipse(i*multiplyerX+1.5*MARGIN,j*multiplyerY+1.5*MARGIN+SQUARE_SIZE,circleSize,circleSize);
            }
        }
    }

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
            qDebug()<<"Sellected row: "<<selectedRow;
        }
    }
    if(event->key() == Qt::Key_Left)
    {
        qDebug()<<"Left Key pressed ";
        if(selectedRow >0){
            selectedRow-=1;
            qDebug()<<"Sellected row: "<<selectedRow;
        }
    }
    if((event->key() == Qt::Key_Space) || (event->key() == Qt::Key_Down))
    {
        qDebug()<<"Down Key pressed ";
        if(playerOnMove == red){
            insertCoinInRow(selectedRow);
            checkWinner();
        }
    }

    update();
}


void FourInRow::insertCoinInRow(int row){
    qDebug()<<"Insert coin in row: "<<row;
    for(int i = BOARD_HEIGHT-1;i>=0;i--){
        if(board[row][i]==empty){
            board[row][i]=playerOnMove;
            break;
        }
    }
    switchPlayerOnMove();
}

void FourInRow::switchPlayerOnMove(){
    if(playerOnMove == red){
        playerOnMove =yellow;
        computerMove();
    }
    else{
        playerOnMove = red;
    }
};


void FourInRow::computerMove(){
     int row;
     row = rand() % BOARD_WIDTH;
     insertCoinInRow(row);
     update();
}
//void FourInRow::makeMove(){
//    int row;
//    if(playerOnMove==red){
//        do{
//            //cout<<endl<<"Select row to insert the coin: " ;
//            //cin>>row;
//            if(board[row-1][0]!=empty){
//                //cout<<endl<<"Selected row is already full";
//            }
//        }
//        while(board[row-1][0]!=empty);

//        insertCoinInRow(row-1);
//    }
//    if(playerOnMove==yellow){
//        row = rand() % BOARD_WIDTH;
//        insertCoinInRow(row);
//    }
//    switchPlayerOnMove();
//}

void FourInRow::initialize(){
    for(int i = 0; i<BOARD_WIDTH;i++){
        for(int j = 0; j<BOARD_HEIGHT;j++){
            board[i][j]=empty;
        }
    }
};





player FourInRow::checkWinner(){
    qDebug()<<"checking winner ";
    // check horizontal:
    player checkResault =empty;
    int max = BOARD_WIDTH>BOARD_HEIGHT? BOARD_WIDTH:BOARD_HEIGHT;

    for(int k = 0;k<6;k++){
        for(int i=0;i<max;i++){
            int inRowRed=0;
            int inRowYellow=0;
            for(int j=0;j<max;j++){
                player z = empty;
                switch (k) {
                    case 0: // check vertically
                        if(i<BOARD_WIDTH && j<BOARD_HEIGHT){
                                z = board[i][j];
                        }
                        break;
                    case 1: // check horizontally
                        if(j<BOARD_WIDTH && i<BOARD_HEIGHT){
                            z = board[j][i];
                        }
                        break;
                    case 2:
                        if(i+j<BOARD_WIDTH && j<BOARD_HEIGHT){
                            z =board[i+j][j];
                        }
                        else{
                            continue;
                        }
                        break;
                    case 3:
                        if((i+j-(max-1)>=0) && (i+j-(max-1)<BOARD_WIDTH)){
                            z =board[i+j-(max-1)][j];
                        }
                        else{
                            continue;
                        }
                        break;
                    case 4:
                        if((max-i-j>=0) && (max-i-j<BOARD_WIDTH)){
                            z =board[max-j-i][j];
                        }
                        else{
                            continue;
                        }
                        break;
                    case 5:
                        if((2*max-2-j-i<BOARD_WIDTH) && (2*max-2-j-i>=0)){
                            z =board[2*max-2-j-i][j];
                        }
                        else{
                            continue;
                        }
                        break;

                }
                switch(z){
                    case yellow:
                        inRowYellow +=1;
                        inRowRed =0;
                        break;
                    case red:
                        inRowRed +=1;
                        inRowYellow =0;
                        break;
                    case empty:
                        inRowRed =0;
                        inRowYellow =0;
                        break;
                }
                if(inRowRed >= 4){
                    qDebug()<<"_______WINNER is RED________";
                    checkResault = red;
                }
                if(inRowYellow >= 4){
                    qDebug()<<"_______WINNER is YELLOW_____";
                    checkResault = yellow;
                }
            }
        }
    }
    if ((checkResault==red) || (checkResault==yellow)){
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
    }
    return checkResault;
}








