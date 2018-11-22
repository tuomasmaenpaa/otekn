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



namespace Student {
const int HEXSIZE = 25;


class graphicHex : public QGraphicsPolygonItem
{
public:

    graphicHex(Common::CubeCoordinate center, std::shared_ptr<Common::Hex> hexPtr);
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


private:

    //The cubecoordinate of this hex
    Common::CubeCoordinate center;

    //The hex that this graphichex represents
    std::shared_ptr <Common::Hex> _hexPtr;

    QGraphicsSimpleTextItem* _pawnDisplayPtr;

    int _axialQ;
    int _axialR;
    double _graphicX;
    double _graphicY;
};
}

#endif // GRAPHICHEX_HH
