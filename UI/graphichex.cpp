/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */

#include "pawn.hh"
#include "graphichex.hh"
#include <QPainter>
#include <string>


/* The implementation of the graphichex class.
 * Class is derived from QGraphicsPolygonItem.
 */

namespace Student {

// Const values where pawns should be drawn.
const std::vector<QPointF> PAWNPLACEMENTVECTOR = {QPointF(-18,-18),QPointF(12,-18),QPointF(-4,0)};

// Const values of how actors and transports should be represented.
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
    // Delete the items drawn on this hex.
    for(auto a:_pawnDisplayVector){

        delete a;
    }

    delete _actorDisplayPtr;
    delete _transportDisplayPtr;
}

QPointF graphicHex::calculatePoints( int HEXSIZE, int i, int centX, int centY)
{

    // Calculates a corner of the hex and returns it as a QPointF.

    double angleDegree = 60 * i-30;
    double angleRad = M_PI / 180 * angleDegree;

    return QPointF(centX+ HEXSIZE * cos(angleRad), centY + HEXSIZE * sin(angleRad));
}

void graphicHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Emits the signal to MainUiWindow.
    Q_UNUSED(event);
    emit clickHappened(_hexPtr);
}


void graphicHex::setPosition()
{
    // Sets the hex in the correct position.
    setPos(_graphicX,_graphicY);

}

void graphicHex::setGraphicCenter()
{

    // Calculate the graphic center of the hex in scenes coordinates.
    _graphicX = HEXSIZE * (sqrt(3) * _axialQ  +  sqrt(3)/2 * _axialR);
    _graphicY = HEXSIZE * ( 3./2 * _axialR);



}

QColor graphicHex::setColor()
{
    // A map of possible piecetypes and their colors.
    std::map<std::string,QColor> typeColorMap = {{"Peak",Qt::darkGray},
                                                {"Mountain",Qt::gray},
                                                 {"Beach",Qt::yellow},
                                                 {"Water",Qt::cyan},
                                                 {"Coral",Qt::magenta},
                                                {"Forest",Qt::green}};

    std::string pieceType = _hexPtr->getPieceType();
    // Return the correct color.
    if(typeColorMap.find(pieceType)!=typeColorMap.end()){
        return typeColorMap.at(pieceType);
    }else{
        return Qt::white;
    }


}

QPolygonF graphicHex::polygon()
{
    /* Function creates a QPolygon that is given to QGraphicsPolygonItem, that
     * can then paint itself with it.
     */

    QPolygonF polygon;
    for(int i=0; i<6;i++){
        polygon << calculatePoints(HEXSIZE,i,0,0);
    }

    return polygon;

}

void graphicHex::addPawn(std::shared_ptr<Common::Pawn> pawn)
{
    // Get the id of the pawn and create a matching QString.
    int pawnNumber = pawn->getId();
    QString qstr = QString::number(pawnNumber);

    // Find a free slot for the pawn in the _pawnDisplayVector
    for(unsigned int i=0; i<_pawnDisplayVector.size();++i){

        if(_pawnDisplayVector.at(i) == nullptr){

            // Create a textItem to present the pawn.
            _pawnDisplayVector.at(i) = new QGraphicsSimpleTextItem(qstr,this);

            // Set the position of the pawn.
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

        // Creates a textItem to present the actor on the hex.
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

        // Creates a textItem to present the transport on the hex.
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
    // Function recolors the hex when its type has changed.
    _brush.setColor(setColor());

    this->setBrush(_brush);
    this->update();


}

}
