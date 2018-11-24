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
    explicit MainUiWindow(QGraphicsView* view, std::shared_ptr<QGraphicsScene> scene,
                          std::shared_ptr<Student::GameBoard> board,
                          std::shared_ptr <Common::IGameRunner> runner,
                          QWidget *parent = 0);
    ~MainUiWindow();

public slots:
    void tileClicked();
    void spinWheel();

private:
    Ui::MainUiWindow *ui;
    std::shared_ptr<QGraphicsScene> _scene;
    std::shared_ptr<Student::GameBoard> _board;
    std::shared_ptr <Common::IGameRunner> _runner;
};

#endif // MAINUIWINDOW_HH
