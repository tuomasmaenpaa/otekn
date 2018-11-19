#include "gameboard.hh"

namespace Student {



GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{

}


int GameBoard::checkTileOccupation(Common::CubeCoordinate coord) const
{//auto a = std::make_shared<Student::graphicHex>(coord, newHex);

    //if the tile doesn't exist return -1
    if(_hexMap.find(coord) == _hexMap.end()){

        int a = -1;
        return a;
    }

    std::shared_ptr <Common::Hex> wanted;
    wanted = _hexMap.at(coord);

    return wanted->getPawnAmount();
}

bool GameBoard::isWaterTile(Common::CubeCoordinate coord) const
{
    //if the tile doesn't exist return false
    if(_hexMap.find(coord) == _hexMap.end()){

        return false;
    }

    std::shared_ptr <Common::Hex> wanted;
    wanted = _hexMap.at(coord);

    //if the tile is a watertile return true otherwise
    //return false
    if(wanted->isWaterTile()){

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

    std::shared_ptr <graphicHex> hex = std::shared_ptr<graphicHex>(new graphicHex(coord, newHex));

    //also add item to the scene

    _graphicHexMap[coord] = hex;

    _scene->addItem(hex.get());
    hex->setHex(newHex);
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
