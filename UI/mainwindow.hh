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


class MainWindow : public QMainWindow
{


public:
    MainWindow(QGraphicsView& view);
    ~MainWindow();

    void drawMap();
    void addRowToMap(std::vector<Common::CubeCoordinate>& coordinates, int rowLenght, int rowNumber, bool widens);

    //This map contains the hexes that the graphichexes represent
    std::map< Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexMap;
    std::map< Common::CubeCoordinate, std::shared_ptr<Common::Hex>>* hexMapPtr;

private:
    QGraphicsScene* _scene;
    std::shared_ptr <GameBoard> _board;
    std::shared_ptr <GameState> _state;
    std::shared_ptr <Logic::GameEngine> _engine;
    std::vector<std::shared_ptr<Player>> _players={};

};

#endif // MAINWINDOW_HH
