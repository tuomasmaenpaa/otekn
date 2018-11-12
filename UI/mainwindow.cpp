#include "mainwindow.hh"
#include "gameboard.hh"
#include <vector>
#include <math.h>

#include "cubecoordinate.hh"

#include <QApplication>

MainWindow::MainWindow(QGraphicsView &view, std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<Common::IGameRunner> runner):
    _scene(scene)
{
    view.setScene(_scene.get());
    view.show();

}

MainWindow::~MainWindow()
{

}






