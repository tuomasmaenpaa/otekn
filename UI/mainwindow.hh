#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH


#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <map>
#include "graphichex.hh"


class MainWindow : public QMainWindow
{


public:
    MainWindow(QGraphicsView& view);
    ~MainWindow();

    void drawMap();
    void addRowToMap(std::vector<Common::CubeCoordinate>& coordinates, int rowLenght, int rowNumber, bool widens);

    //This map contains the hexes that the graphichexes represent
    std::map< Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexMap;

private:
    QGraphicsScene* _scene;

};

#endif // MAINWINDOW_HH
