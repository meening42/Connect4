#include "fourinrow.h"

FourInRow::FourInRow(QWidget* pParent) :
    QWidget(pParent)
{
    initialize();
    srand(time(NULL));
    qDebug()<<"constructor called ";

    ptimer = new QTimer(this);
    ptimer->setInterval(18);
    connect(ptimer, SIGNAL(timeout()), this, SLOT(control()));
}


void FourInRow::control(){
    if((playerOnMove ==  red) && (insertCoin) && (!coinFalling) && (board[selectedRow][0]==empty)){
        qDebug()<<"1";
        insertCoinInRow(selectedRow);
        coinFalling = true;
        insertCoin = false;
    }
    if (checkWinnerSignal && !coinFalling){
        qDebug()<<"2";
        checkWinner(board,false);
        checkWinnerSignal = false;
        ptimer->stop();
        switchPlayerOnMove();
    }
    update();
}

//void FourInRow::timerEvent(QTimerEvent *event){
//    qDebug()<<"timer called";
//    control();

//}


void FourInRow::paintEvent(QPaintEvent *event){
    QPainter P(this);
    int multiplyer = multiplyer = (width()-(2*MARGIN))/BOARD_WIDTH;
    int circleSize = SQUARE_SIZE-1.5*MARGIN;
    // draw selection circle
    if (coinFalling == false){
        if (playerOnMove == red){
            P.setPen(QPen(Qt::darkRed, 2));
            P.setBrush(Qt::red);
        }
        else{
            P.setPen(QPen(Qt::darkYellow, 2));
            P.setBrush(Qt::yellow);
        }
        P.drawEllipse((1.5*MARGIN)+selectedRow*multiplyer,2*MARGIN,circleSize,circleSize);
    }

    // draw falling circle
    int downPos = 0.95*fallingY*multiplyer+SQUARE_SIZE+MARGIN;
    if ((coinFalling == true) && (gameOver == false) ){
         //qDebug()<<"Coin falling routine called";
        if (playerOnMove == red){
            P.setPen(QPen(Qt::darkRed, 2));
            P.setBrush(Qt::red);
        }
        else{
            P.setPen(QPen(Qt::darkYellow, 2));
            P.setBrush(Qt::yellow);
        }
        P.drawEllipse((1.5*MARGIN)+fallingX*multiplyer,fallingYPos,circleSize,circleSize);
        fallingYPos+=10;
        if (fallingYPos >=downPos){
            qDebug()<<"Coin down";
            coinFalling = false;
            board[fallingX][fallingY]=playerOnMove;
            // check winner
            qDebug()<<"Calling check winner down";
            checkWinnerSignal = true;
            //checkWinner(board,false);
        }
    }

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
    // draw winning row
    if(gameOver){
        if(winner == red){
            for(int i = 0;i<winningPositionsRed.size();++i){
                P.setPen(QPen(Qt::black, 8));
                P.setBrush(Qt::red);
                P.drawEllipse(winningPositionsRed[i].x*multiplyerX+1.5*MARGIN,
                              winningPositionsRed[i].y*multiplyerY+1.5*MARGIN+SQUARE_SIZE,
                              circleSize,circleSize);
            }
        }
        else if(winner == yellow){
            for(int i = 0;i<winningPositionsYellow.size();++i){
                P.setPen(QPen(Qt::black, 8));
                P.setBrush(Qt::yellow);
                P.drawEllipse(winningPositionsYellow[i].x*multiplyerX+1.5*MARGIN,
                              winningPositionsYellow[i].y*multiplyerY+1.5*MARGIN+SQUARE_SIZE,
                              circleSize,circleSize);
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
        if((selectedRow < BOARD_WIDTH-1) && (playerOnMove == red)){
            selectedRow+=1;
            control();
            update();
        }
    }
    if(event->key() == Qt::Key_Left)
    {
        if((selectedRow >0) && (playerOnMove == red) ){
            selectedRow-=1;
            control();
            update();
        }
    }
    if((event->key() == Qt::Key_Space) || (event->key() == Qt::Key_Down))
    {
        if((playerOnMove == red) && !(coinFalling)){
            insertCoin = true;
            control();
            update();
        }
    }
}




void FourInRow::insertCoinInRow(int row){

    qDebug()<<"Insert coin in row: "<<row;
    for(int i = BOARD_HEIGHT-1;i>=0;--i){
        if(board[row][i]==empty){
            fallingY = i;
            ptimer->start();
            coinFalling = true;
            fallingX = row;
            fallingYPos = 2*MARGIN;
            qDebug()<<"Coin falling";
            break;
        }
    }
}



void FourInRow::switchPlayerOnMove(){
    qDebug()<<"Switch player";
    if(playerOnMove == red){
        playerOnMove =yellow;
        computerMove();
    }
    else{
        playerOnMove = red;
    }
}




void FourInRow::computerMove(){
     qDebug()<<"Computer move";
     int row;
     std::tuple <bool, int, int> winMoveYellow = std::make_tuple(0, 0, false);
     std::tuple <bool, int, int> winMoveRed = std::make_tuple(0, 0, false);
     // check if computer has winning move
     winMoveYellow = checkPossibleWin(yellow);
     winMoveRed = checkPossibleWin(red);
     if(std::get<0>(winMoveYellow)==true){
         insertCoinInRow(std::get<1>(winMoveYellow));
     }
     else if(std::get<0>(winMoveRed)==true){
         insertCoinInRow(std::get<1>(winMoveRed));
     }
     else{
         do{
         row = rand() % BOARD_WIDTH;
         }
         while(board[row][0]!=empty);
         insertCoinInRow(row);
     }
     update();
}





void FourInRow::initialize(){
    qDebug()<<"Initialze";
    for(int i = 0; i<BOARD_WIDTH;i++){
        for(int j = 0; j<BOARD_HEIGHT;j++){
            board[i][j]=empty;
        }
    }
    selectedRow = 3;
    playerOnMove = red;
    winningPositionsRed.clear();
    winningPositionsYellow.clear();
    playerOnMove = red;
    coinFalling = false;
    gameOver = false;
    insertCoin = false;
    checkWinnerSignal = false;
    winner = empty;
}

void FourInRow::copyBoradToVirtual(){
    for(int i = 0; i<BOARD_WIDTH; ++i){
        for(int j=0;j<BOARD_HEIGHT;++j){
            virtualBoard[i][j] = board[i][j];
        }
    }
}


std::tuple<bool,int,int>FourInRow::checkPossibleWin(player p){
    qDebug()<<"Check posible win for "<< ((p==red)? "red":"yellow");
    std::tuple <bool, int, int> temp = std::make_tuple(0, 0, false);

    //copy board to virtual board
    copyBoradToVirtual();
    //check move
    for(int i = 0; i<BOARD_WIDTH; ++i){
        for(int j = BOARD_HEIGHT-1;j>=0;--j){
            if(virtualBoard[i][j]==empty){
                virtualBoard[i][j]=p;
                if(p == checkWinner(virtualBoard, true)){
                    temp = std::make_tuple(true, i, j);
                    return temp;
                }
                virtualBoard[i][j]=empty;
                break;
            }
        }
    }
    return temp;
}



player FourInRow::checkWinner(player  pArr[BOARD_WIDTH][BOARD_HEIGHT],bool isVirtualArr){
    if(isVirtualArr == false){
        qDebug()<<"checking winner ";
    }
    // check horizontal:
    player checkResault =empty;
    int max = BOARD_WIDTH>BOARD_HEIGHT? BOARD_WIDTH:BOARD_HEIGHT;
    struct pos position;
    for(int k = 0;k<6;k++){
        for(int i=0;i<max;i++){
            int inRowRed=0;
            int inRowYellow=0;
            PositionsRed.clear();
            PositionsYellow.clear();
            for(int j=0;j<max;j++){
                player z = empty;
                switch (k) {
                    case 0: // check vertically
                        if(i<BOARD_WIDTH && (j<BOARD_HEIGHT)){
                            z = pArr[i][j];
                            position.x = i;
                            position.y = j;
                        }
                        break;
                    case 1: // check horizontally
                        if(j<BOARD_WIDTH && i<BOARD_HEIGHT){
                            z = pArr[j][i];
                            position.x = j;
                            position.y = i;
                        }
                        break;
                    case 2:
                        if(i+j<BOARD_WIDTH && j<BOARD_HEIGHT){
                            z =pArr[i+j][j];
                            position.x = i+j;
                            position.y = j;
                        }
                        else{
                            continue;
                        }
                        break;
                    case 3:
                        if((i+j-(max-1)>=0) && (i+j-(max-1)<BOARD_WIDTH)&& (j<BOARD_HEIGHT)){
                            z =pArr[i+j-(max-1)][j];
                            position.x = i+j-(max-1);
                            position.y = j;
                        }
                        else{
                            continue;
                        }
                        break;
                    case 4:
                        if((max-i-j>=0) && (max-i-j<BOARD_WIDTH)&& (j<BOARD_HEIGHT)){
                            z =pArr[max-j-i][j];
                            position.x = max-j-i;
                            position.y = j;
                        }
                        else{
                            continue;
                        }
                        break;
                    case 5:
                        if((2*max-2-j-i<BOARD_WIDTH) && (2*max-2-j-i>=0)&& (j<BOARD_HEIGHT)){
                            z =pArr[2*max-2-j-i][j];
                            position.x = 2*max-2-j-i;
                            position.y = j;
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
                        if(isVirtualArr==false){
                            PositionsYellow.push_back(position);
                            PositionsRed.clear();
                        }
                        break;
                    case red:
                        inRowRed +=1;
                        inRowYellow =0;
                        if(isVirtualArr==false){
                            PositionsRed.push_back(position);
                            PositionsYellow.clear();
                        }
                        break;
                    case empty:
                        inRowRed =0;
                        inRowYellow =0;
                        if(isVirtualArr==false){
                            PositionsRed.clear();
                            PositionsYellow.clear();
                        }
                        break;
                }
                if(inRowRed >= 4){
                    if(isVirtualArr == false){
                        qDebug()<<"_______WINNER is RED________";
                        checkResault = red;
                        winningPositionsRed = PositionsRed;
                    }
                    if(isVirtualArr == true){
                        qDebug()<<"_______FOUND Winning move for RED________";
                        checkResault = red;
                    }
                }
                if(inRowYellow >= 4){
                    if(isVirtualArr == false){
                        qDebug()<<"_______WINNER is YELLOW_____";
                        checkResault = yellow;
                        winningPositionsYellow = PositionsYellow;
                    }
                    if(isVirtualArr == true){
                        qDebug()<<"_______FOUND Winning move for Yellow________";
                        checkResault = yellow;
                    }
                }
            }
        }
    }
    if ((isVirtualArr == false) &&
            ((checkResault==red) ||
             (checkResault==yellow) ||  isDraw())){
        gameOver = true;
        winner = checkResault;
        update();
        QString text = "";
        if(checkResault == red){
            text = "WINNER IS RED";
            qDebug()<<"Winning pos = ";
            for(int i=0;i<4;i++){
                qDebug()<<winningPositionsRed[i].x<<","<<winningPositionsRed[i].y;
            }
        }
        else if(checkResault == yellow){
            text = "WINNERS IS YELLOW";
            qDebug()<<"Winning pos = ";
            for(int i=0;i<4;i++){
                qDebug()<<winningPositionsYellow[i].x<<","<<winningPositionsYellow[i].y;
            }
        }
        else if(isDraw() && checkResault == empty){
            text = "DRAW";
        }
        qDebug()<<"MessageBox";
        QMessageBox msgBox;
        msgBox.setText(text);
        msgBox.setInformativeText("Do you want to play another game?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Ok:
              initialize();
              qDebug()<<"calling init";
              break;
          case QMessageBox::Close:
            QApplication::instance()->quit();
            qDebug()<<"calling quit";
            break;
        }
    }
    if((gameOver == false) && (isVirtualArr == false)){
        //switchPlayerOnMove();
    }
    return checkResault;
}



bool FourInRow::isDraw(){
    for(int i = 0;i<BOARD_WIDTH;++i){
        if(board[i][0]==empty){
            return false;
        }
    }
    return true;
}









