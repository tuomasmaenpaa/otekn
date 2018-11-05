#include "gameboard.hh"



GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{

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
