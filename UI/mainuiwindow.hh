/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */

#ifndef MAINUIWINDOW_HH
#define MAINUIWINDOW_HH

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

/* Headerfile for the mainwindow of the game.
 */

namespace Ui {
class MainUiWindow;
}

class MainUiWindow : public QMainWindow
{
    //Q_OBJECT

public:
    explicit MainUiWindow(std::shared_ptr<QGraphicsScene> scene,
                          std::shared_ptr<Student::GameBoard> board,
                          std::shared_ptr <Common::IGameRunner> runner,
                          std::shared_ptr <Student::GameState> state,
                          QWidget *parent = 0);
    ~MainUiWindow();

    // Updates the labels in the mainwindow.
    void updateLabels();

    // Checks if there is a winner.
    bool victoryRoyale();

public slots:

    // Handles clicks happening on hexes.
    void tileClicked(std::shared_ptr<Common::Hex> clickedHex);

    // Spins the wheel.
    void spinWheel();

    // Ends players turn if they decide to do so.
    void endTurn();

private:
    Ui::MainUiWindow *ui;
    std::shared_ptr<QGraphicsScene> _scene;
    std::shared_ptr<Student::GameBoard> _board;
    std::shared_ptr <Common::IGameRunner> _runner;
    std::shared_ptr <Student::GameState> _state;

    // Values from the spinwheel.
    std::pair <std::string,std::string> _wheelValues;
};

#endif // MAINUIWINDOW_HH
