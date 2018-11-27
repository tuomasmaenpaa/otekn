#include "gameboard.hh"
#include "illegalmoveexception.hh"
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
    if((_hexMap.find(actorCoord) == _hexMap.end()) or (actor == nullptr) or
            (_hexMap.find(actorCoord) == _hexMap.end())){

        return;
    }

    //Add actor to the map
    _actorMap[actor->getId()] = actor;

    std::shared_ptr<Common::Hex> hex;
    hex = getHex(actorCoord);
    hex->addActor(actor);

    //Give the actor its hex
    actor->addHex(hex);

    //If scene exsists add graphical actor to acording hex
    if(_scene != nullptr){

        std::shared_ptr<graphicHex> gHex;
        gHex = _graphicHexMap.at(actorCoord);
        gHex->addActor(actor);

    }
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{
    //If the hex or the transport don't exsist return
    if((_hexMap.find(coord) == _hexMap.end()) or (transport == nullptr)){

        return;
    }

    //Give the transport to the hex
    std::shared_ptr<Common::Hex> hex;
    hex = getHex(coord);
    hex->addTransport(transport);

    //Give the hex to the transport
    transport->addHex(hex);

    //add transport to the map
    _transportMap[transport->getId()] = transport;

    //Add graphic transport
    if(_scene != nullptr){

        std::shared_ptr<graphicHex> gHex;
        gHex = _graphicHexMap.at(coord);
        gHex->addTransport(transport);
    }
}

void GameBoard::movePawn(int, int)
{

}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate target)
{
    //TODO NONEXSISTENT TILE CHECK
    if(_hexMap.find(target) != _hexMap.end()){

        removePawn(pawnId);
        addPawn(pawnId,pawnId,target);
    }




}

void GameBoard::moveActor(int Id, Common::CubeCoordinate coord)
{
    if((_actorMap.find(Id) != _actorMap.end()) and (_hexMap.find(coord) != _hexMap.end()) ){

        std::shared_ptr<Common::Actor> actor = _actorMap.at(Id);
        removeActor(Id);
        addActor(actor,coord);
    }
}

void GameBoard::moveTransport(int Id, Common::CubeCoordinate coord)
{
    //TODO NONEXSISTENT TILE CHECK
    if((_transportMap.find(Id) != _transportMap.end()) and (_hexMap.find(coord) != _hexMap.end())){

        std::shared_ptr<Common::Transport> trans = _transportMap.at(Id);
        removeTransport(Id);
        addTransport(trans, coord);
    }
}

void GameBoard::removeTransport(int id)
{
    if(_transportMap.find(id) != _transportMap.end()){

        std::shared_ptr<Common::Transport> trans = _transportMap.at(id);
        std::shared_ptr<Common::Hex> hex = trans->getHex();

        hex->removeTransport(trans);

        if(_scene != nullptr){

            std::shared_ptr<graphicHex> gHex;
            gHex = _graphicHexMap.at(hex->getCoordinates());

            gHex->removeTransport();
        }

    }
}

void GameBoard::removeActor(int Id)
{
    if((_actorMap.find(Id) != _actorMap.end())){

        std::shared_ptr<Common::Actor> actor = _actorMap.at(Id);
        std::shared_ptr<Common::Hex> hex = actor->getHex();

        if(hex != nullptr){

            hex->removeActor(actor);

            //Remove the graphical representation if scene exsists
            if(_scene != nullptr){

                Common::CubeCoordinate coord = hex->getCoordinates();
                std::shared_ptr<graphicHex> gHex;
                gHex = _graphicHexMap.at(coord);

                gHex->removeActor(actor);
            }
        }
    }

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
    if(_pawnMap.find(id) == _pawnMap.end()){

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
    hex->removePawn(pawn);


}

void GameBoard::setScene(std::shared_ptr<QGraphicsScene> scene)
{
    _scene = scene;
}

void GameBoard::setGameState(std::shared_ptr<GameState> state)
{
    _gameState = state;
}


void GameBoard::setRunner(std::shared_ptr<Common::IGameRunner> runner)
{
    _runner = runner;
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

void GameBoard::setClickedMovement(std::shared_ptr<Common::Hex> selectedHex)
{

    // When called first time, function saves the hex that was chosen.
    // When called again, function saves the second clicked hex.
    // These will then be used for checking movements and moving
    // items on board.

    if((_firstClick == nullptr) and (playersPawnOnHex(selectedHex))){
        _firstClick = selectedHex.get();


    }else if((_secondClick == nullptr) and (_firstClick != nullptr)){

        _secondClick = selectedHex.get();

        try {

            // if movement is successful, move on to next phase
            _runner->movePawn(_firstClick->getCoordinates(),_secondClick->getCoordinates(),getPawn(_firstClick));
            _gameState->changeGamePhase(Common::SINKING);

        }catch(Common::IllegalMoveException){
            // no need to do anything

        }
        resetSelected();


    }

}

void GameBoard::setClickedSinking(std::shared_ptr<Common::Hex> selectedHex)
{
    try{
        std::cout<<_runner->flipTile(selectedHex->getCoordinates())<<std::endl;

        //TODO add actor

        // Change the graphic hex to a water tile
        if(_graphicHexMap.find(selectedHex->getCoordinates()) != _graphicHexMap.end()){
            _graphicHexMap.at(selectedHex->getCoordinates())->changeColor();
            _gameState->changeGamePhase(Common::SPINNING);
        }


    }catch(Common::IllegalMoveException){

    }

}

void GameBoard::setClickedSpinning(std::shared_ptr<Common::Hex> selectedHex, std::pair<std::string, std::string> wheelValues)
{
    if((_firstClick == nullptr) and
            ((actorOnHex(selectedHex,wheelValues.first))or(transportOnHex(selectedHex,wheelValues.first)))){

        _firstClick = selectedHex.get();


    }else if((_secondClick == nullptr) and (_firstClick != nullptr)){

        _secondClick = selectedHex.get();

        // TODO mitä liikutetaan actor/trans/ei liiku



        if(wheelValues.first != "dolphin"){
            try{

                std::vector<std::shared_ptr<Common::Actor>> actorVector= _firstClick->getActors();

                for(auto actor : actorVector){

                    if(actor->getActorType() == wheelValues.first){

                        _runner->moveActor(_firstClick->getCoordinates(), _secondClick->getCoordinates(),actor->getId(),wheelValues.second);

                        nextPlayer();
                        resetSelected();
                        break;

                    }

                }
            }catch(Common::IllegalMoveException){
                resetSelected();

            }

        }else{



            try{

                std::vector<std::shared_ptr<Common::Transport>> transports = _firstClick->getTransports();

                for(auto transport : transports){

                    if(transport->getTransportType() == wheelValues.first){

                        _runner->moveTransportWithSpinner(_firstClick->getCoordinates(),_secondClick->getCoordinates(),transport->getId(),wheelValues.second);

                        nextPlayer();
                        resetSelected();
                        break;
                    }
                }



            }catch(Common::IllegalMoveException){
                resetSelected();

            }

        }


        }


}

bool GameBoard::playersPawnOnHex(std::shared_ptr<Common::Hex> selectedHex)
{

    // checking if current player has a pawn on given hex

    int playerId = _gameState->currentPlayer();
    for(auto pawn : selectedHex->getPawns()){
        if(pawn->getId()==playerId){
            return true;
        }
    }
    return false;
}

int GameBoard::getPawn(Common::Hex *source)
{
    //PRE: Only use when there are player pawns on the hex

    for(auto pawn : source->getPawns()){

        if(pawn->getPlayerId() == _runner->currentPlayer()){
            return pawn->getId();
        }
    }

    return 0;
}

void GameBoard::resetSelected()
{
    _firstClick = nullptr;
    _secondClick = nullptr;
}

void GameBoard::nextPlayer()
{
    int currentPlayer = _runner->currentPlayer();

    //If the current player is the last in turn change the player to first in the rotation
    if(currentPlayer == _players.size()){

        _gameState->changePlayerTurn(_players.at(0)->getPlayerId());

    }else{

        int counter = 0;

        //Set the next player as the player in turn
        for(auto player:_players){

            if(player->getPlayerId() == currentPlayer){

                _gameState->changePlayerTurn(_players.at(counter+1)->getPlayerId());

            }

            ++counter;

        }
    }

}

bool GameBoard::winCheck()
{
    std::shared_ptr<Common::Hex> center;

    for(auto tile : _hexMap){

        if((tile.first.x == 0) and (tile.first.y == 0) and (tile.first.z == 0)){

            center = tile.second;
        }

    }

    //Victory royale
    if(center->getPawnAmount() > 0){

        return true;
    }

    return false;
}




bool Student::GameBoard::actorOnHex(std::shared_ptr<Common::Hex> selectedHex, std::string actorType)
{
    for(std::string type : selectedHex->getActorTypes()){

        if(type == actorType){

            return true;
        }
    }

    return false;
}

bool Student::GameBoard::transportOnHex(std::shared_ptr<Common::Hex> selectedHex, std::string transportType)
{

    for(auto transport : selectedHex->getTransports()){

        if(transport->getTransportType() == transportType){

            return true;
        }
    }

    return false;


}

}
