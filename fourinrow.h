#ifndef WIDGETCENTRAL_H
#define WIDGETCENTRAL_H

#include <QWidget>
#include <QTextEdit>
#include <QPainter>
#include <QPushButton>
#include <QSpinBox>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6

class FourInRow : public QWidget
{
    Q_OBJECT

public:
    FourInRow(QWidget* pParent = nullptr);

public slots:
    void paintEvent(QPaintEvent *event);
private:

};

#endif // WIDGETCENTRAL_H
