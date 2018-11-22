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

namespace Student {


class MainWindow : public QMainWindow
{


public:
    MainWindow(QGraphicsView& view, std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<Common::IGameRunner> runner);
    ~MainWindow();


private:
    std::shared_ptr<QGraphicsScene> _scene;
    std::shared_ptr <Common::IGameRunner> _runner;


};
}

#endif // MAINWINDOW_HH
