#include "gameboard.hh"



GameBoard::GameBoard(std::shared_ptr<QGraphicsScene> scene):
    _scene(scene)
{

}

GameBoard::~GameBoard()
{

}


int GameBoard::checkTileOccupation(Common::CubeCoordinate coord) const
{
    /*Common::Hex hex = _hexMap[coord];

    return hex.getPawnAmount();*/
}

bool GameBoard::isWaterTile(Common::CubeCoordinate coord) const
{
    /*std::shared_ptr<Common::Hex> hex;
    hex = _hexMap.at(coord);

    //If the hex is a water tile return true otherwise return false
    if(hex->isWaterTile()){

        return true;

    }else{

        return false;
    }*/
}

std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate coord) const
{
    //If the hex doesn't exist
    if(_hexMap.find(coord) == _hexMap.end()){

        return nullptr;
    }

    std::shared_ptr<Common::Hex> wantedHex;
    wantedHex = _hexMap.at(coord);

    return wantedHex;
}

void GameBoard::addPawn(int playerId, int pawnId)
{

}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{

}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{

}

void GameBoard::movePawn(int, int)
{

}

void GameBoard::movePawn(int, Common::CubeCoordinate)
{

}

void GameBoard::moveActor(int, Common::CubeCoordinate)
{

}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{

}

void GameBoard::removeTransport(int id)
{

}

void GameBoard::removeActor(int)
{

}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    Common::CubeCoordinate coord = newHex->getCoordinates();

    _hexMap[coord] = newHex;

    graphicHex* hex = new graphicHex(coord, newHex);
    _scene->addItem(hex);
    hex->setHex(newHex);
}

void GameBoard::removePawn(int)
{

}
