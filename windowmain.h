#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QMainWindow>
#include <QMenu>
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QDebug>
#include <QHBoxLayout>

class WindowMain : public QMainWindow
{
    Q_OBJECT

public:
    WindowMain(QWidget *parent = nullptr);
    ~WindowMain();

public slots:
    void quit();
};
#endif // WINDOWMAIN_H
