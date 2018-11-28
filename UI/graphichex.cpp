#include "pawn.hh"
#include "graphichex.hh"
#include <QPainter>
#include <string>


namespace Student {

const std::vector<QPointF> PAWNPLACEMENTVECTOR = {QPointF(-18,-18),QPointF(12,-18),QPointF(-4,0)};

const std::map<std::string, QString> ACTORMAP = {{"vortex","V"},{"shark","S"},{"seamunster","SM"},
                                                 {"kraken","K"},{"dolphin","D"},{"boat","B"}};

graphicHex::graphicHex(Common::CubeCoordinate center, std::shared_ptr <Common::Hex> hexPtr):
    _center(center),
    _hexPtr(hexPtr),
    _axialQ(center.x),
    _axialR(center.z)


{

    //Setting the color of the hex

    _brush.setStyle(Qt::SolidPattern);
    _brush.setColor(setColor());
    setBrush(_brush);

    //Creates the polygon that this graphichex represents
    setPolygon(polygon());

}

graphicHex::~graphicHex()
{
    for(auto a:_pawnDisplayVector){

        delete a;
    }

    delete _actorDisplayPtr;
}

QPointF graphicHex::calculatePoints( int HEXSIZE, int i, int centX, int centY)
{
    double angleDegree = 60 * i-30;
    double angleRad = M_PI / 180 * angleDegree;

    return QPointF(centX+ HEXSIZE * cos(angleRad), centY + HEXSIZE * sin(angleRad));
}

void graphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    Q_UNUSED(event);
    emit clickHappened(_hexPtr);
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


    for(unsigned int i=0; i<_pawnDisplayVector.size();++i){

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
    //Remove the graphical representation of the pawn

    for(unsigned int i = 0; i<_pawnDisplayVector.size();++i){

        // When the correct pawn is found, delete the SimpleTextItem that
        // represents the pawn. Then set the pointer to nullptr

        if(_pawnDisplayVector.at(i) != nullptr){

            if(_pawnDisplayVector.at(i)->text().toInt() == pawn->getId()){

                delete _pawnDisplayVector.at(i);
                _pawnDisplayVector[i] = nullptr;
                break;
            }
         }
    }
    this->update();

}

void graphicHex::addActor(std::shared_ptr<Common::Actor> actor)
{
    if(ACTORMAP.find(actor->getActorType()) != ACTORMAP.end()){

        _actorDisplayPtr = new QGraphicsSimpleTextItem(ACTORMAP.at(actor->getActorType()),this);
        _actorDisplayPtr->setPos(-4,-8);
        this->update();
    }
}

void graphicHex::removeActor()
{
    delete _actorDisplayPtr;
    _actorDisplayPtr = nullptr;

    this->update();
}

void graphicHex::addTransport(std::shared_ptr<Common::Transport> trans)
{
    if(ACTORMAP.find(trans->getTransportType()) != ACTORMAP.end()){

        _transportDisplayPtr = new QGraphicsSimpleTextItem(ACTORMAP.at(trans->getTransportType()),this);
        _transportDisplayPtr->setPos(-12,-10);
        this->update();
    }
}

void graphicHex::removeTransport()
{
    delete _transportDisplayPtr;
    _transportDisplayPtr = nullptr;

    this->update();
}



void graphicHex::changeColor()
{
    _brush.setColor(setColor());

    this->setBrush(_brush);
    this->update();


}

}
