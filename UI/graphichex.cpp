
#include "graphichex.hh"
#include <QPainter>

namespace Student {
graphicHex::graphicHex(Common::CubeCoordinate center, std::shared_ptr <Common::Hex> hexPtr):
    center(center),
    _hexPtr(hexPtr),
    _axialQ(center.x),
    _axialR(center.z)
{
    //setFlag(ItemIsSelectable);

}

QPointF graphicHex::calculatePoints( int HEXSIZE, int i)
{
    double angleDegree = 60 * i-30;
    double angleRad = M_PI / 180 * angleDegree;

    return QPointF(_graphicX + HEXSIZE * cos(angleRad), _graphicY + HEXSIZE * sin(angleRad));
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



    brush.setStyle(Qt::SolidPattern);
    brush.setColor(setColor());
    painter->setBrush(brush);


    painter->drawPolygon(polygon);


}

void graphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    std::cout<<"clicked x: "<<center.x<<" y: "<<center.y<<" z: "<<center.z<<std::endl;

}


void graphicHex::setPosition()
{


    setPos(_graphicX,_graphicY);

    std::cout<<this->pos().x()<<" "<<this->pos().y()<<std::endl;
}

void graphicHex::setGraphicCenter()
{

    _graphicX = HEXSIZE * (sqrt(3) * _axialQ  +  sqrt(3)/2 * _axialR);
    _graphicY = HEXSIZE * ( 3./2 * _axialR);



}

QColor graphicHex::setColor()
{

    std::map<std::string,QColor> typeColorMap = {{"Peak",Qt::darkGray},
                                                {"Mountain",Qt::gray},
                                                 {"Beach",Qt::yellow},
                                                 {"Water",Qt::cyan},
                                                 {"Coral",Qt::magenta},
                                                {"Forest",Qt::green}};

    std::string pieceType = _hexPtr->getPieceType();

    if(typeColorMap.find(pieceType)!=typeColorMap.end()){
        return typeColorMap.at(pieceType);
    }else{
        return Qt::white;
    }


}



QRectF graphicHex::boundingRect() const
{
    return QRectF(-HEXSIZE*sqrt(3),-HEXSIZE,HEXSIZE*sqrt(3),HEXSIZE);

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
