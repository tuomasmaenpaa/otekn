#include "mainwindow.hh"
#include "gameboard.hh"
#include <vector>
#include <math.h>

#include "cubecoordinate.hh"

#include <QApplication>

MainWindow::MainWindow(QGraphicsView &view):
    _scene(new QGraphicsScene(0,0,500,500,&view))
{



    view.setScene(_scene);
    drawMap();
    view.show();

}

MainWindow::~MainWindow()
{
    delete _scene;
}

void MainWindow::drawMap()
{

    std::vector<Common::CubeCoordinate> coordinates;

    // top half of the map
    for (int i=1; i<6; i++){

        addRowToMap(coordinates,5+i,i,true);
    }
    // bottom half of the map
    for ( int i = 1; i<5; ++i){
        addRowToMap(coordinates,10-i,5+i,false);
    }

    graphicHex* hp;
    for(auto coord : coordinates){
        hp = new graphicHex(coord);
        _scene->addItem(hp);
    }

}

void MainWindow::addRowToMap(std::vector<Common::CubeCoordinate> &coordinates, int rowLenght, int rowNumber, bool widens)
{

    int x_coord;
    int y_coord;
    int z_coord;


    for(int i = 1; i < rowLenght; ++i){


        y_coord = HEXSIZE * rowNumber * 1.5;

        // depends on whether the coordinates are for top or bottom
        // half of the map
        if(widens){

            x_coord = i * HEXSIZE * sqrt(3.0) - HEXSIZE * rowNumber;
            z_coord = -x_coord - y_coord;

            coordinates.push_back(Common::CubeCoordinate(x_coord,y_coord,z_coord));
        }else{

            x_coord = i * HEXSIZE * sqrt(3.0) + HEXSIZE * (rowNumber-10);
            z_coord = -x_coord - y_coord;

            coordinates.push_back(Common::CubeCoordinate(x_coord,y_coord,z_coord));
        }
    }

}




