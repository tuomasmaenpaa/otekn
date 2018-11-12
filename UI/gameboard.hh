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
    void addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord);
    void addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord);
    void movePawn(int, int);
    void movePawn(int, Common::CubeCoordinate);
    void moveActor(int, Common::CubeCoordinate);
    void moveTransport(int id, Common::CubeCoordinate coord);
    void removeTransport(int id);
    void removeActor(int);
    void addHex(std::shared_ptr<Common::Hex> newHex);
    void removePawn(int);

private:

    //This map contains all the hexes with their cubecoordinate as the key
    std::map <Common::CubeCoordinate, std::shared_ptr<Common::Hex>> _hexMap;

    //Ths map contains the pawns with their id as the key
    std::map <int,std::shared_ptr <Common::Pawn>> _pawnMap;
    std::shared_ptr <QMainWindow> window;
    std::shared_ptr <QGraphicsScene> _scene;

};
#endif // GAMEBOARD_HH
