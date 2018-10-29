#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH


#include <QMainWindow>
#include "graphichex.hh"


class MainWindow : public QMainWindow
{


public:
    MainWindow();


protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_HH
