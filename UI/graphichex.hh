#ifndef GRAPHICHEX_HH
#define GRAPHICHEX_HH

#include <QPainter>
#include <QPoint>
#include <QFrame>
#include <QPolygon>
#include <QPen>
#include <math.h>

#include "hex.hh"
#include "cubecoordinate.hh"

const int HEXSIZE = 25;

class graphicHex : public Common::Hex, public QFrame
{
public:
    graphicHex();

    QPointF calculatePoints(Common::CubeCoordinate center,int HEXSIZE,int i);

};

#endif // GRAPHICHEX_HH
