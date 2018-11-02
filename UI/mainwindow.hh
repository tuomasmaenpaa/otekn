#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH


#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "graphichex.hh"


class MainWindow : public QMainWindow
{


public:
    MainWindow(QGraphicsView& view);
    ~MainWindow();

private:
    QGraphicsScene* _scene;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_HH
