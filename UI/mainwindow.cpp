#include "mainwindow.hh"
#include "gameboard.hh"
#include <vector>
#include "cubecoordinate.hh"

#include <QApplication>

MainWindow::MainWindow(QGraphicsView &view):
    _scene(new QGraphicsScene(0,0,500,500,&view))
{



    view.setScene(_scene);

    Common::CubeCoordinate c(70,70,70);
    graphicHex*hp =new graphicHex(c);
    _scene->addItem(hp);
    view.show();

}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    /*Common::CubeCoordinate c(70,70,70);
    graphicHex h(c);

    h.paint(this);
*/

   /* QPolygonF polygon;
    QPainterPath path;
    QLinearGradient grad;
    QPen pen;
    graphicHex hex;


    Common::CubeCoordinate c(70,70,70) ;

    for(int i=1; i<7;i++){
        polygon << hex.calculatePoints(c,HEXSIZE,i);
    }

    path.addPolygon(polygon);
    QPainter painter(this);
    painter.setBrush(grad);
    painter.setPen(pen);
    path.closeSubpath();

    painter.drawPath(path); */

}


