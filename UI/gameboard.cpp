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
    std::shared_ptr<Common::Hex> hex;

    //if the hex exsists
    /*if(_graphicHexMap.find(coord) != _graphicHexMap.end()){


        gHex = _graphicHexMap.at(coord);

        std::shared_ptr<Common::Pawn> pawn = std::shared_ptr<Common::Pawn>(new Common::Pawn());
        pawn->setId(pawnId, playerId);

        gHex->addPawn(pawn);
        _pawnMap[pawnId] = pawn;

    }*/

    //If the hex exsists add the pawn to the hex
    if(_hexMap.find(coord) != _hexMap.end()){

        hex = _hexMap.at(coord);

        std::shared_ptr<Common::Pawn> pawn = std::shared_ptr<Common::Pawn>(new Common::Pawn());
        pawn->setId(pawnId, playerId);
        pawn->setCoordinates(coord);

        hex->addPawn(pawn);
        _pawnMap[pawnId] = pawn;

        //If the scene exsists create the graphical representation
        //for the pawn on the hex
        if(_scene != nullptr){

            gHex = _graphicHexMap.at(coord);
            gHex->addPawn(pawn);
        }
    }

}

void GameBoard::addPawn(int playerId, int pawnId)
{
    Common::Pawn newPawn;
    newPawn.setId(pawnId, playerId);
}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{
    //If the hex or the actor don't exsist return
    if((_hexMap.find(actorCoord) == _hexMap.end()) or (actor == nullptr)){

        return;
    }

    std::shared_ptr<Common::Hex> hex;
    hex = getHex(actorCoord);
    hex->addActor(actor);

    /*TODO
     * Graphical representation of the actor
     */
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{
    //If the hex or the transport don't exsist return
    if((_hexMap.find(coord) == _hexMap.end()) or (transport == nullptr)){

        return;
    }

    std::shared_ptr<Common::Hex> hex;
    hex = getHex(coord);
    hex->addTransport(transport);

    /*TODO
     * Graphical representation of the actor
     */
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
    //If the hex doesnt exist
    if(newHex == nullptr){

        return;
    }

    Common::CubeCoordinate coord = newHex->getCoordinates();

    _hexMap[coord] = newHex;

    std::shared_ptr <graphicHex> hex = std::shared_ptr<graphicHex>(new graphicHex(coord, newHex));

    //also add item to the scene if it exists
    if(_scene != nullptr){

        _graphicHexMap[coord] = hex;

        _scene->addItem(hex.get());

        hex->setGraphicCenter();
        hex->setPosition();
        hex->update();
    }
}

void GameBoard::removePawn(int id)
{
    //If the pawn exsists
    /*if(_pawnMap.find(id) == _pawnMap.end()){

        return;
    }

    //Get the coordinates of the pawn
    std::shared_ptr <Common::Pawn> pawn = _pawnMap.at(id);
    Common::CubeCoordinate coord = pawn->getCoordinates();

    //if the scene exsists remove the graphical representation of the pawn
    if(_scene != nullptr){

        std::shared_ptr<graphicHex> gHex = _graphicHexMap.at(coord);
        gHex->removePawn(pawn);
    }

    //Remove the pawn from the logic hex
    std::shared_ptr <Common::Hex> hex = _hexMap.at(coord);
    hex->removePawn(pawn);*/

}

void GameBoard::setScene(std::shared_ptr<QGraphicsScene> scene)
{

    _scene = scene;
}

void GameBoard::setGameState(std::shared_ptr<GameState> state)
{
    _gameState = state;
}

void GameBoard::addPlayer(std::shared_ptr<Player> player)
{
    _players.push_back(player);
}

std::map<Common::CubeCoordinate, std::shared_ptr<graphicHex> > &GameBoard::getGraphicHexMap()
{
    return _graphicHexMap;
}

std::vector<Common::CubeCoordinate> GameBoard::getCornerTiles()
{

    std::vector<Common::CubeCoordinate> cornerCoords;

    for (auto tile : _hexMap){

        if(tile.second->getPieceType() == "Coral" and (tile.first.x==0 or tile.first.y == 0 or tile.first.z == 0)){
                cornerCoords.push_back(tile.first);
    }

    }

    return cornerCoords;
}

void GameBoard::createPawns()
{

   std::vector<Common::CubeCoordinate> corners = getCornerTiles();

   //Adding the pawns according to the amount of players in the game.
   //Players have only one pawn and the pawns id is the same as the players.
   for(int i = 0; i<_players.size();i++){
       addPawn(_players.at(i)->getPlayerId(),_players.at(i)->getPlayerId(),corners.at(i));
   }



}


}
