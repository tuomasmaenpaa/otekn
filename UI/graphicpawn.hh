#ifndef GRAPHICPAWN_HH
#define GRAPHICPAWN_HH

#include "QGraphicsItem"
#include "pawn.hh"

namespace Student{

class GraphicPawn : public QGraphicsItem
{
public:
    GraphicPawn();
    ~GraphicPawn();

    //Draws this particular pawn on the hex that is given
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:

    int _playerId;
    int _pawnId;

    std::shared_ptr<Common::Pawn> _pawnPtr;
};
}
#endif // GRAPHICPAWN_HH
