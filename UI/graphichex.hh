#ifndef GRAPHICHEX_HH
#define GRAPHICHEX_HH


#include <QPainter>
#include <QPoint>
#include <QPolygon>
#include <QPen>
#include <math.h>
#include <QMainWindow>
#include <QGraphicsItem>
#include <iostream>

#include "hex.hh"
#include "cubecoordinate.hh"
#include "actor.hh"
#include "transport.hh"
#include <QGraphicsObject>


namespace Student {
const int HEXSIZE = 25;



class graphicHex :public QObject, public QGraphicsPolygonItem
{
       Q_OBJECT

public:

    graphicHex(Common::CubeCoordinate _center, std::shared_ptr<Common::Hex> hexPtr);
    ~graphicHex();

    QPointF calculatePoints(int HEXSIZE, int i, int centX, int centY);


    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //Sets the position of the hex
    void setPosition();

    //Calculates the graphic centerpoints of the hex
    void setGraphicCenter();

    //Sets the corect colour of the hex
    QColor setColor();

    //Creates the polygon that this graphichex represents
    QPolygonF polygon();

    //Draws the pawn on this graphichex and adds it to the
    // hex graphichex represents
    void addPawn(std::shared_ptr<Common::Pawn> pawn);
    void removePawn(std::shared_ptr<Common::Pawn> pawn);

    void addActor(std::shared_ptr<Common::Actor> actor);
    void removeActor(std::shared_ptr<Common::Actor> actor);

    void addTransport(std::shared_ptr<Common::Transport> trans);
    void removeTransport();

    void changeColor();

signals:

    void clickHappened( std::shared_ptr <Common::Hex> _hexPtr);

private:

    //The cubecoordinate of this hex
    Common::CubeCoordinate _center;

    //The hex that this graphichex represents
    std::shared_ptr <Common::Hex> _hexPtr = nullptr;

    //Stores the graphical representations of the pawns
    std::vector<QGraphicsSimpleTextItem*> _pawnDisplayVector = {(nullptr), (nullptr), (nullptr)};

    //Stores the graphical representation of the actor on the tile
    QGraphicsSimpleTextItem* _actorDisplayPtr = nullptr;

    QBrush _brush;

    int _axialQ;
    int _axialR;
    double _graphicX;
    double _graphicY;
};
}

#endif // GRAPHICHEX_HH
