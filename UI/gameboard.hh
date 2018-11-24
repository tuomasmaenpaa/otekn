#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <hex.hh>

#include "igameboard.hh"
#include "graphichex.hh"
#include "QGraphicsScene"
#include "pawn.hh"
#include "iplayer.hh"
#include "player.hh"
#include "gamestate.hh"

namespace Student {


class GameBoard : public Common::IGameBoard
{
public: 



    GameBoard();
    ~GameBoard();

    int checkTileOccupation(Common::CubeCoordinate coord) const;
    bool isWaterTile(Common::CubeCoordinate coord) const;
    std::shared_ptr< Common::Hex > getHex(Common::CubeCoordinate coord) const;
    void addPawn(int playerId, int pawnId,Common::CubeCoordinate coord);
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
    void removePawn(int id);

    void setScene(std::shared_ptr <QGraphicsScene> scene);
    void setGameState(std::shared_ptr<GameState> state);
    void addPlayer(std::shared_ptr<Player> player);
    std::map<Common::CubeCoordinate, std::shared_ptr<graphicHex>>& getGraphicHexMap();

    std::vector<Common::CubeCoordinate> getCornerTiles();

    void createPawns();

    //TODO
    /*  Clicking hgex sends signal to slot
     * check what phase it is
     * if movement phase, check legal moves
     * if sinking phase check if sinkable tile
     * if spinning check actor movement
     *
     */

private:

    //This map contains all the hexes with their cubecoordinate as the key
    std::map <Common::CubeCoordinate, std::shared_ptr<Common::Hex>> _hexMap;


    std::map <Common::CubeCoordinate, std::shared_ptr<graphicHex>> _graphicHexMap;

    //Ths map contains the pawns with their id as the key
    std::map <int,std::shared_ptr <Common::Pawn>> _pawnMap;

    std::vector<std::shared_ptr<Common::IPlayer>> _players;

    std::shared_ptr<GameState> _gameState;

    std::shared_ptr <QMainWindow> window;
    std::shared_ptr <QGraphicsScene> _scene;

};
}
#endif // GAMEBOARD_HH
