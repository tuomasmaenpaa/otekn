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

    void drawMap();
    void addRowToMap(std::vector<Common::CubeCoordinate>& coordinates, int rowLenght, int rowNumber, bool widens);

private:
    QGraphicsScene* _scene;

};

#endif // MAINWINDOW_HH
