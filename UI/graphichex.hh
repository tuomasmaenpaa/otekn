#ifndef GRAPHICHEX_HH
#define GRAPHICHEX_HH

#include <QPainter>
#include <QPoint>
#include <QFrame>
#include <QPolygon>
#include <QPen>
#include <math.h>
#include <QMainWindow>

#include "hex.hh"
#include "cubecoordinate.hh"

const int HEXSIZE = 25;

class graphicHex : public Common::Hex, public QFrame
{
public:

    graphicHex(Common::CubeCoordinate center);

    QPointF calculatePoints(Common::CubeCoordinate center,int HEXSIZE,int i);

    //Draws this particular hex on the window that is given
    void drawHex(QMainWindow *window);

private:

    Common::CubeCoordinate center;
};

#endif // GRAPHICHEX_HH
