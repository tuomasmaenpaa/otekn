#include "gameboard.hh"



GameBoard::GameBoard()
{

    //window->show();
}

GameBoard::~GameBoard()
{

}

void GameBoard::addHex(std::shared_ptr<graphicHex> newHex)
{
    //newHex->drawHex(window);
}

int GameBoard::checkTileOccupation(Common::CubeCoordinate) const
{

}

bool GameBoard::isWaterTile(Common::CubeCoordinate) const
{

}

std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate) const
{

}

void GameBoard::addPawn(int, int)
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

void GameBoard::removeActor(int)
{

}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{

}

void GameBoard::removePawn(int)
{

}
