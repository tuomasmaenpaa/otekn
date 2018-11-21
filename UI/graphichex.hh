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

    QPointF calculatePoints(int HEXSIZE, int i, int centX, int centY);

    //Draws this particular hex on the window that is given
    //void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //Sets the hex that this graphics hex is pointing to
    void setPosition();
    void setGraphicCenter();
    QColor setColor();
    QPolygonF polygon();


private:




    QRectF boundingRect() const;
    QPainterPath shape();
    Common::CubeCoordinate center;
    //QPolygonF _hexagon;

    //The hex that this graphichex represents
    std::shared_ptr <Common::Hex> _hexPtr;
    int _axialQ;
    int _axialR;
    double _graphicX;
    double _graphicY;
};
}

#endif // GRAPHICHEX_HH
