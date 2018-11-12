#include "graphichex.hh"
#include <QPainter>


graphicHex::graphicHex(Common::CubeCoordinate center, std::shared_ptr <Common::Hex> hexPtr):
    center(center),
    _hexPtr(hexPtr),
    _axialQ(center.x),
    _axialR(center.z)
{


}

QPointF graphicHex::calculatePoints( int HEXSIZE, int i)
{
    double angleDegree = 60 * i-30;
    double angleRad = M_PI / 180 * angleDegree;


    double graphicX = HEXSIZE * (sqrt(3) * _axialQ  +  sqrt(3)/2 * _axialR);
    double graphicY = HEXSIZE * ( 3./2 * _axialR);


    return QPointF(graphicX + HEXSIZE * cos(angleRad), graphicY + HEXSIZE * sin(angleRad));
}

void graphicHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0)
{
    QPolygonF polygon;
    QPainterPath path;
    QLinearGradient grad;
    QPen pen;



    for(int i=1; i<7;i++){
        polygon << calculatePoints(HEXSIZE,i);
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

void graphicHex::setHex(std::shared_ptr<Common::Hex> hexPtr)
{
    _hexPtr = hexPtr;
}



QRectF graphicHex::boundingRect() const
{

}

QPainterPath graphicHex::shape()
{
    QPolygonF polygon;
    QPainterPath path;


    for(int i=1; i<7;i++){
        polygon << calculatePoints(HEXSIZE,i);
    }

    path.addPolygon(polygon);
    return path;

}

