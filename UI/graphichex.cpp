#include "graphichex.hh"
#include <QPainter>

graphicHex::graphicHex(Common::CubeCoordinate center): center(center)
{


}

QPointF graphicHex::calculatePoints(Common::CubeCoordinate center, int HEXSIZE, int i)
{
    double angleDegree = 60 * i;
    double angleRad = M_PI / 180 * angleDegree;
    return QPointF(center.x + HEXSIZE * cos(angleRad), center.y + HEXSIZE * sin(angleRad));
}

void graphicHex::drawHex(QMainWindow* window)
{
    QPolygonF polygon;
    QPainterPath path;
    QLinearGradient grad;
    QPen pen;

    for(int i=1; i<7;i++){
        polygon << calculatePoints(center,HEXSIZE,i);
    }

    path.addPolygon(polygon);

    QPainter painter(window);

    painter.setBrush(grad);
    painter.setPen(pen);
    path.closeSubpath();

    painter.drawPath(path);
}

