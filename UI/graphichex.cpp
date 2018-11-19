#include "graphichex.hh"
#include <QPainter>

namespace Student {
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
    QBrush brush;



    for(int i=0; i<6;i++){
        polygon << calculatePoints(HEXSIZE,i);
    }

    path.addPolygon(polygon);

    painter->setBrush(grad);
    painter->setPen(pen);
    path.closeSubpath();


    painter->setBrush(brush);

    painter->drawPath(path);


}

void graphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    std::cout<<"clicked x: "<<center.x<<" y: "<<center.y<<" z: "<<center.z<<std::endl;

}

void graphicHex::setHex(std::shared_ptr<Common::Hex> hexPtr)
{
    _hexPtr = hexPtr;
}

void graphicHex::setPosition()
{

    double xPos = _axialQ;//HEXSIZE * (sqrt(3) * _axialQ  +  sqrt(3)/2 * _axialR) - HEXSIZE*8;
    double yPos = _axialR;//HEXSIZE * ( 3./2 * _axialR) - HEXSIZE*8;
    setPos(xPos,yPos);


}



QRectF graphicHex::boundingRect() const
{
    return QRectF(-HEXSIZE,-HEXSIZE,HEXSIZE,HEXSIZE);

}

QPainterPath graphicHex::shape()
{
    QPolygonF polygon;
    QPainterPath path;


    for(int i=0; i<6;i++){
        polygon << calculatePoints(HEXSIZE,i);
    }

    path.addPolygon(polygon);
    return path;

}
}
