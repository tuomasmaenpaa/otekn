#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "hex.hh"
#include "mainwindow.hh"
#include "gameengine.hh"
#include "openingdialog.hh"
#include <iostream>
#include <cubecoordinate.hh>


#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QGraphicsView view;
    std::shared_ptr<QGraphicsScene> scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene(-500,-500,1000,1000,&view));

    std::shared_ptr <Student::GameBoard> board = std::shared_ptr<Student::GameBoard>(new Student::GameBoard());


    board->setScene(scene);

    std::shared_ptr <Student::GameState> state = std::shared_ptr<Student::GameState>(new Student::GameState());
    std::vector<std::shared_ptr<Common::IPlayer>> players;



    OpeningDialog dialog;

    int playerCount;

    if(dialog.exec() == QDialog::Accepted){
       std::cout<<dialog.getSpinBoxValue()<<std::endl;
       playerCount = dialog.getSpinBoxValue();

    }else{
        return EXIT_FAILURE;
    }

    // Adds the amount of players to the game that the user wanted
    for(int i= 0; i<playerCount;++i){
        std::shared_ptr<Student::Player> player =std::shared_ptr<Student::Player>(new Student::Player(i+1));
        players.push_back(player);
        board->addPlayer(player);
    }



    std::shared_ptr <Common::IGameRunner> runner;

    runner = Common::Initialization::getGameRunner(board, state, players);

    board->getCornerTiles();
    board->createPawns();
    Student::MainWindow w(view, scene, runner);


    return a.exec();


}
