#include "pawn.hh"
#include "graphichex.hh"
#include <QPainter>
#include <string>


namespace Student {

const std::vector<QPointF> PAWNPLACEMENTVECTOR = {QPointF(-18,-18),QPointF(12,-18),QPointF(-4,0)};

graphicHex::graphicHex(Common::CubeCoordinate center, std::shared_ptr <Common::Hex> hexPtr):
    _center(center),
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

graphicHex::~graphicHex()
{
    for(auto a:_pawnDisplayVector){

        delete a;
    }
}

QPointF graphicHex::calculatePoints( int HEXSIZE, int i, int centX, int centY)
{
    double angleDegree = 60 * i-30;
    double angleRad = M_PI / 180 * angleDegree;

    return QPointF(centX+ HEXSIZE * cos(angleRad), centY + HEXSIZE * sin(angleRad));
}

void graphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    std::cout<<"clicked x: "<<_center.x<<" y: "<<_center.y<<" z: "<<_center.z<<std::endl;
    //emit clickHappened(center);
    //removePawn(_hexPtr->getPawns().at(0));

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

    int pawnNumber = pawn->getId();
    QString qstr = QString::number(pawnNumber);


    for(int i=0; i<_pawnDisplayVector.size();++i){

        if(_pawnDisplayVector.at(i) == nullptr){

            _pawnDisplayVector.at(i) = new QGraphicsSimpleTextItem(qstr,this);
            _pawnDisplayVector.at(i)->setPos(PAWNPLACEMENTVECTOR.at(i));
            break;
        }

    }

    this->update();

}

void graphicHex::removePawn(std::shared_ptr<Common::Pawn> pawn)
{
    //Remove the graphical representation
    for(auto a:_pawnDisplayVector){

        if(a->text().toInt() == pawn->getId()){

            delete a;
            break;
        }
    }

    _hexPtr->removePawn(pawn);

    this->update();

}
}
