#include "graphichex.hh"

graphicHex::graphicHex()
{


}

QPointF graphicHex::calculatePoints(Common::CubeCoordinate center, int HEXSIZE, int i)
{
    double angleDegree = 60 * i;
    double angleRad = M_PI / 180 * angleDegree;
    return QPointF(center.x + HEXSIZE * cos(angleRad), center.y + HEXSIZE * sin(angleRad));
}

