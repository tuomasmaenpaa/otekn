#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <hex.hh>

#include "igameboard.hh"
#include "graphichex.hh"
#include "QGraphicsScene"


class GameBoard : public Common::IGameBoard
{
public:
    GameBoard(std::shared_ptr<QGraphicsScene> scene);
    ~GameBoard();

    int checkTileOccupation(Common::CubeCoordinate coord) const;
    bool isWaterTile(Common::CubeCoordinate coord) const;
    std::shared_ptr< Common::Hex > getHex(Common::CubeCoordinate coord) const;
    void addPawn(int playerId, int pawnId);
    void movePawn(int, int);
    void movePawn(int, Common::CubeCoordinate);
    void moveActor(int, Common::CubeCoordinate);
    void removeActor(int);
    void addHex(std::shared_ptr<Common::Hex> newHex);
    void removePawn(int);

private:

    std::map <Common::CubeCoordinate, std::shared_ptr<Common::Hex>> _hexMap;
    std::shared_ptr <QMainWindow> window;
    std::shared_ptr <QGraphicsScene> _scene;

};
#endif // GAMEBOARD_HH
