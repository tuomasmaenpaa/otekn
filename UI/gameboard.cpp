#include "gameboard.hh"

namespace Student {



GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{

}


int GameBoard::checkTileOccupation(Common::CubeCoordinate coord) const
{
    std::shared_ptr<Common::Hex> hex;
    hex = getHex(coord);

    //if the tile doesn't exist return -1
    if(hex == nullptr){

        int a = -1;
        return a;
    }


    return hex->getPawnAmount();
}

bool GameBoard::isWaterTile(Common::CubeCoordinate coord) const
{
    std::shared_ptr<Common::Hex> hex;
    hex = getHex(coord);

    //if the tile doesn't exist return false
    if(hex == nullptr){

        return false;
    }

    //if the tile is a watertile return true otherwise
    //return false
    if(hex->isWaterTile()){

        return true;
    }
    else{

        return false;
    }
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

void GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{

    std::shared_ptr<graphicHex> gHex;

    //if the hex exsists
    if(_graphicHexMap.find(coord) != _graphicHexMap.end()){

        gHex = _graphicHexMap.at(coord);

        std::shared_ptr<Common::Pawn> pawn = std::shared_ptr<Common::Pawn>(new Common::Pawn());
        pawn->setId(pawnId, playerId);

        gHex->addPawn(pawn);

        //TODO:

        //Draw pawn on the hex

    }




}

void GameBoard::addPawn(int playerId, int pawnId)
{
    Common::Pawn newPawn;
    newPawn.setId(pawnId, playerId);
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

    std::shared_ptr <graphicHex> hex = std::shared_ptr<graphicHex>(new graphicHex(coord, newHex));

    //also add item to the scene

    _graphicHexMap[coord] = hex;

    _scene->addItem(hex.get());

    hex->setGraphicCenter();
    hex->setPosition();
    hex->update();

}

void GameBoard::removePawn(int)
{

}

void GameBoard::setScene(std::shared_ptr<QGraphicsScene> scene)
{

    _scene = scene;
}
}
