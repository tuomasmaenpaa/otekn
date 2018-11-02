#include "graphichex.hh"
#include <QPainter>


graphicHex::graphicHex(Common::CubeCoordinate center): center(center)
{


}

QPointF graphicHex::calculatePoints(Common::CubeCoordinate center, int HEXSIZE, int i)
{
    double angleDegree = 60 * i-30;
    double angleRad = M_PI / 180 * angleDegree;
    return QPointF(center.x + HEXSIZE * cos(angleRad), center.y + HEXSIZE * sin(angleRad));
}

void graphicHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0)
{
    QPolygonF polygon;
    QPainterPath path;
    QLinearGradient grad;
    QPen pen;

    for(int i=1; i<7;i++){
        polygon << calculatePoints(center,HEXSIZE,i);
    }

    path.addPolygon(polygon);

    painter->setBrush(grad);
    painter->setPen(pen);
    path.closeSubpath();

    painter->drawPath(path);

}

void graphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{



}



QRectF graphicHex::boundingRect() const
{

}

QPainterPath graphicHex::shape()
{
    QPolygonF polygon;
    QPainterPath path;

    for(int i=1; i<7;i++){
        polygon << calculatePoints(center,HEXSIZE,i);
    }

    path.addPolygon(polygon);
    return path;

}

