#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "hex.hh"
#include "mainwindow.hh"


#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QGraphicsView view;
    MainWindow w(view);


    return a.exec();


}
