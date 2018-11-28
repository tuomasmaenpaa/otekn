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
    void updateLabels();

    bool victoryRoyale();

public slots:
    void tileClicked(std::shared_ptr<Common::Hex> clickedHex);
    void spinWheel();
    void endTurn();

private:
    Ui::MainUiWindow *ui;
    std::shared_ptr<QGraphicsScene> _scene;
    std::shared_ptr<Student::GameBoard> _board;
    std::shared_ptr <Common::IGameRunner> _runner;
    std::shared_ptr <Student::GameState> _state;

    std::pair <std::string,std::string> _wheelValues;
};

#endif // MAINUIWINDOW_HH
