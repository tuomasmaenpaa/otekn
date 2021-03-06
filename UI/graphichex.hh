/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */

#ifndef GRAPHICHEX_HH
#define GRAPHICHEX_HH


#include <QPoint>
#include <QPolygon>
#include <math.h>
#include <QMainWindow>
#include <QGraphicsItem>

#include "hex.hh"
#include "cubecoordinate.hh"
#include "actor.hh"
#include "transport.hh"
#include <QGraphicsObject>

/* This is the headerfile for Student::graphicHex class.
 * This class is the graphic version if games hexes.
 * Class is derived from QGraphicsPolygonItem.
 */


namespace Student {
const int HEXSIZE = 25;



class graphicHex :public QObject, public QGraphicsPolygonItem
{
       Q_OBJECT

public:

    graphicHex(Common::CubeCoordinate _center, std::shared_ptr<Common::Hex> hexPtr);
    ~graphicHex();


    // Calculates the corners of the hex from its local center.
    QPointF calculatePoints(int HEXSIZE, int i, int centX, int centY);

    // Emits signal to mainuiwindow to handle the clicks
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //Sets the position of the hex
    void setPosition();

    //Calculates the graphic centerpoints of the hex
    void setGraphicCenter();

    //Sets the corect colour of the hex
    QColor setColor();

    //Creates the polygon that this graphichex represents
    QPolygonF polygon();

    // Draws the pawn on this graphichex.
    void addPawn(std::shared_ptr<Common::Pawn> pawn);

    // Removes the pawn from this graphichex.
    void removePawn(std::shared_ptr<Common::Pawn> pawn);

    // Draws the actor on this graphichex.
    void addActor(std::shared_ptr<Common::Actor> actor);

    // Removes the actor from this graphichex.
    void removeActor();

    // Draws the transport on this graphichex.
    void addTransport(std::shared_ptr<Common::Transport> trans);

    // Removes the transport from this graphicHex
    void removeTransport();

    // Changes the color of the hex to match the piece type.
    void changeColor();

signals:

    // Signal that is emitted when hex is clicked.
    void clickHappened( std::shared_ptr <Common::Hex> _hexPtr);

private:

    //The cubecoordinate of this hex.
    Common::CubeCoordinate _center;

    //The hex that this graphichex represents.
    std::shared_ptr <Common::Hex> _hexPtr = nullptr;

    //Stores the graphical representations of the pawns.
    std::vector<QGraphicsSimpleTextItem*> _pawnDisplayVector = {(nullptr), (nullptr), (nullptr)};

    //Stores the graphical representation of the actor on the tile.
    QGraphicsSimpleTextItem* _actorDisplayPtr = nullptr;

    //Stores the graphical representation of the transport on the tile.
    QGraphicsSimpleTextItem* _transportDisplayPtr = nullptr;

    // The brush that colors the hex.
    QBrush _brush;

    // This hexes axial coordinates.
    int _axialQ;
    int _axialR;

    // This hexes graphical coordinates.
    double _graphicX;
    double _graphicY;
};
}

#endif // GRAPHICHEX_HH
