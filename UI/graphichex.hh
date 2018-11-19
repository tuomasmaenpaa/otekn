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


class graphicHex : public QGraphicsItem
{
public:

    graphicHex(Common::CubeCoordinate center, std::shared_ptr<Common::Hex> hexPtr);

    QPointF calculatePoints(int HEXSIZE, int i);

    //Draws this particular hex on the window that is given
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //Sets the hex that this graphics hex is pointing to
    void setHex(std::shared_ptr <Common::Hex> hexPtr);
    void setPosition();


private:




    QRectF boundingRect() const;
    QPainterPath shape();
    Common::CubeCoordinate center;

    //The hex that this graphichex represents
    std::shared_ptr <Common::Hex> _hexPtr;
    int _axialQ;
    int _axialR;
};
}

#endif // GRAPHICHEX_HH
