/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */

#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "hex.hh"
#include "gameengine.hh"
#include "openingdialog.hh"
#include <iostream>
#include <cubecoordinate.hh>
#include "mainuiwindow.hh"


#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    //Create the scene where game is presented and a gameboard.
    std::shared_ptr<QGraphicsScene> scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene(-500,-500,1000,1000));
    std::shared_ptr <Student::GameBoard> board = std::shared_ptr<Student::GameBoard>(new Student::GameBoard());

    // Give the scene to the board.
    board->setScene(scene);

    // Create a gamestate object and a vector for players.
    std::shared_ptr <Student::GameState> state = std::shared_ptr<Student::GameState>(new Student::GameState());
    std::vector<std::shared_ptr<Common::IPlayer>> players;


    // Ask the user how many players they want (1-6).
    OpeningDialog dialog;

    int playerCount;

    if(dialog.exec() == QDialog::Accepted){
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


    // Initialize runner.
    std::shared_ptr <Common::IGameRunner> runner;

    runner = Common::Initialization::getGameRunner(board, state, players);
    // Set the gameboard ready for the game.
    board->setGameState(state);
    board->getCornerTiles();
    board->createPawns();
    board->setRunner(runner);

    // Create and show the mainwindow.
    MainUiWindow w(scene,board,runner,state);

    w.show();


    return a.exec();


}
