#include "mainwindow.hh"
#include "gameboard.hh"
#include <vector>
#include "cubecoordinate.hh"

MainWindow::MainWindow()
{


}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Common::CubeCoordinate c(70,70,70);
    graphicHex h(c);
    h.drawHex(this);
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


