#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <hex.hh>

#include "igameboard.hh"
#include "graphichex.hh"


class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();

    int checkTileOccupation(Common::CubeCoordinate) const;
    bool isWaterTile(Common::CubeCoordinate) const;
    std::shared_ptr< Common::Hex > getHex(Common::CubeCoordinate) const;
    void addPawn(int, int);
    void movePawn(int, int);
    void movePawn(int, Common::CubeCoordinate);
    void moveActor(int, Common::CubeCoordinate);
    void removeActor(int);
    void addHex(std::shared_ptr<Common::Hex> newHex);
    void removePawn(int);

private:

    std::shared_ptr <QMainWindow> window;

};
#endif // GAMEBOARD_HH
