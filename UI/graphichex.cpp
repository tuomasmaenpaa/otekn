
#include "graphichex.hh"
#include <QPainter>

namespace Student {
graphicHex::graphicHex(Common::CubeCoordinate center, std::shared_ptr <Common::Hex> hexPtr):
    center(center),
    _hexPtr(hexPtr),
    _axialQ(center.x),
    _axialR(center.z)
{

    //Setting the color of the hex
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(setColor());
    setBrush(brush);
    //Creates the polygon that this graphichex represents
    setPolygon(polygon());

}

QPointF graphicHex::calculatePoints( int HEXSIZE, int i, int centX, int centY)
{
    double angleDegree = 60 * i-30;
    double angleRad = M_PI / 180 * angleDegree;

    return QPointF(centX+ HEXSIZE * cos(angleRad), centY + HEXSIZE * sin(angleRad));
}

void graphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    std::cout<<"clicked x: "<<center.x<<" y: "<<center.y<<" z: "<<center.z<<std::endl;

}


void graphicHex::setPosition()
{

    setPos(_graphicX,_graphicY);

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

QPolygonF graphicHex::polygon()
{
    QPolygonF polygon;



    for(int i=0; i<6;i++){
        polygon << calculatePoints(HEXSIZE,i,0,0);
    }


    return polygon;

}

void graphicHex::addPawn(std::shared_ptr<Common::Pawn> pawn)
{
    _hexPtr->addPawn(pawn);
}
}
