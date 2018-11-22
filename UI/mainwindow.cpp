#include "mainwindow.hh"
#include "gameboard.hh"
#include <vector>
#include <math.h>
#include <QHBoxLayout>
#include <QPushButton>

#include "cubecoordinate.hh"

#include <QApplication>

namespace Student {


MainWindow::MainWindow(QGraphicsView &view, std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<Common::IGameRunner> runner):
    _scene(scene)
{



    view.setScene(_scene.get());
    view.show();



}

MainWindow::~MainWindow()
{

}
}





