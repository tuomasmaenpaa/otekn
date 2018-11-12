#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "hex.hh"
#include "mainwindow.hh"
#include "gameengine.hh"


#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QGraphicsView view;
    std::shared_ptr<QGraphicsScene> scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene(&view));

    std::shared_ptr <GameBoard> board = std::shared_ptr<GameBoard>(new GameBoard(scene));
    std::shared_ptr <GameState> state = std::shared_ptr<GameState>(new GameState());
    std::vector<std::shared_ptr<Common::IPlayer>> players;
    std::shared_ptr <Common::IGameRunner> runner;

    runner = Common::Initialization::getGameRunner(board, state, players);

    MainWindow w(view, scene, runner);


    return a.exec();


}
