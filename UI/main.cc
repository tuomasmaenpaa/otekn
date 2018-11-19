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

    std::shared_ptr <Student::GameBoard> board = std::shared_ptr<Student::GameBoard>(new Student::GameBoard());

    board->setScene(scene);

    std::shared_ptr <Student::GameState> state = std::shared_ptr<Student::GameState>(new Student::GameState());
    std::vector<std::shared_ptr<Common::IPlayer>> players;
    std::shared_ptr <Common::IGameRunner> runner;

    runner = Common::Initialization::getGameRunner(board, state, players);

    Student::MainWindow w(view, scene, runner);


    return a.exec();


}
