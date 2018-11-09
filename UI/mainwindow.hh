#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH


#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <map>
#include <gamestate.hh>
#include <gameengine.hh>

#include "gameboard.hh"
#include "graphichex.hh"
#include "player.hh"
#include "initialize.hh"


class MainWindow : public QMainWindow
{


public:
    MainWindow(QGraphicsView& view, std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<Common::IGameRunner> runner);
    ~MainWindow();

    void drawMap();
    void addRowToMap(std::vector<Common::CubeCoordinate>& coordinates, int rowLenght, int rowNumber, bool widens);

private:
    std::shared_ptr<QGraphicsScene> _scene;
    std::shared_ptr <Common::IGameRunner> _runner;

};

#endif // MAINWINDOW_HH
