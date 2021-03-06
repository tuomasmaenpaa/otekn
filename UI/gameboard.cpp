/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */


#include "gameboard.hh"
#include "illegalmoveexception.hh"
#include "gameexception.hh"
#include "boat.hh"
#include "dolphin.hh"


/*
 * The implementation of gameboard functions
 */


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
    /*
     * Empty function that is never used, but is necessary
     * to match the interface IGameBoard.
     */
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate target)
{

    // If the hex exsists, move the pawn accordingly.
    if(_hexMap.find(target) != _hexMap.end()){

        removePawn(pawnId);
        addPawn(pawnId,pawnId,target);
    }
}

void GameBoard::moveActor(int Id, Common::CubeCoordinate coord)
{

    // If the actor and hex exsist, move the actor accordingly.
    if((_actorMap.find(Id) != _actorMap.end()) and (_hexMap.find(coord) != _hexMap.end()) ){

        std::shared_ptr<Common::Actor> actor = _actorMap.at(Id);
        removeActor(Id);
        addActor(actor,coord);
    }
}

void GameBoard::moveTransport(int Id, Common::CubeCoordinate coord)
{

    // If the transport and hex exsist, move the transport.
    if((_transportMap.find(Id) != _transportMap.end()) and (_hexMap.find(coord) != _hexMap.end())){


        std::shared_ptr<Common::Transport> trans = _transportMap.at(Id);
        std::shared_ptr<Common::Hex> origin = trans->getHex();

        // Move the pawns with the transport.
        for(auto pawn : origin->getPawns()){
            movePawn(pawn->getId(),coord);
        }


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

        // Update the graphics.
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

                gHex->removeActor();
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

        // Calculate the correct centerpoint for the graphic hex and
        // set the hex there;
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

    // Function finds the corners of the map for pawns to be placed in.
    // Corners are Coral type and contain a 0 in its cubecoordinates,
    // meaning its at the end of a coordinate axel.

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
   for(unsigned int i = 0; i<_players.size();i++){
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

        if(_firstClick->getTransports().size() == 0){

            try {

                // if movement is successful, move on to next phase
                _runner->movePawn(_firstClick->getCoordinates(),_secondClick->getCoordinates(),getPawn(_firstClick));
                _gameState->changeGamePhase(Common::SINKING);

            }catch(const Common::IllegalMoveException&){
                // no need to do anything, player tries again.

            }
            resetSelected();

        }else{
            // get transport from origin hex.
            std::shared_ptr<Common::Transport> trans = _firstClick->getTransports().at(0);

            try{


                // If trying to move from transport to a land piece AKA not water or to another transport

                if((_secondClick->getPieceType()!="Water") or (_secondClick->getTransports().size()>0)){

                    _runner->movePawn(_firstClick->getCoordinates(),_secondClick->getCoordinates(),getPawn(_firstClick));

                }else{
                    checkTransportMovement(_firstClick,_secondClick);
                    _runner->moveTransport(_firstClick->getCoordinates(),_secondClick->getCoordinates(),trans->getId());
                }
                _gameState->changeGamePhase(Common::SINKING);

            }catch(...){
                /*
                 * Catches Common::IllegalMoveException and std::exception because
                 * throwing our own IllegalMoveException didn't work for some reason
                 * that nobody (even the TAs) seemed to know.
                 */
                //nothing done, player tries again.
            }
            resetSelected();

        }


    }

}

void GameBoard::setClickedSinking(std::shared_ptr<Common::Hex> selectedHex)
{
    try{
       _runner->flipTile(selectedHex->getCoordinates());

        // Change the graphic hex to a water tile
        if(_graphicHexMap.find(selectedHex->getCoordinates()) != _graphicHexMap.end()){
            _graphicHexMap.at(selectedHex->getCoordinates())->changeColor();
            _gameState->changeGamePhase(Common::SPINNING);
        }


    }catch(const Common::IllegalMoveException&){

        // Player gets to try sinking again if they couldn't click a hex that was sinkable.

    }

}

void GameBoard::setClickedSpinning(std::shared_ptr<Common::Hex> selectedHex, std::pair<std::string, std::string> wheelValues)
{
    // When called first time, function saves the hex that was chosen.
    // When called again, function saves the second clicked hex.
    // These will then be used for checking movements and moving
    // items on board.

    if((_firstClick == nullptr) and
            ((actorOnHex(selectedHex,wheelValues.first))or(transportOnHex(selectedHex,wheelValues.first)))){

        _firstClick = selectedHex.get();


    }else if((_secondClick == nullptr) and (_firstClick != nullptr)){

        _secondClick = selectedHex.get();


        // Check if the movable thing in spinning phase is a dolphin(transport) or
        // an actor.
        if(wheelValues.first != "dolphin"){
            try{

                std::vector<std::shared_ptr<Common::Actor>> actorVector= _firstClick->getActors();

                for(auto actor : actorVector){

                    if(actor->getActorType() == wheelValues.first){

                        checkActorMovement(_secondClick);
                        _runner->moveActor(_firstClick->getCoordinates(), _secondClick->getCoordinates(),actor->getId(),wheelValues.second);

                        nextPlayer();
                        resetSelected();
                        break;

                    }

                }
            }catch(...){
                /*
                 * Catches Common::IllegalMoveException and std::exception because
                 * throwing our own IllegalMoveException didn't work for some reason
                 * that nobody (even the TAs) seemed to know.
                 */
                //nothing done, player tries again.
                resetSelected();

            }

        }else{

            try{

                std::vector<std::shared_ptr<Common::Transport>> transports = _firstClick->getTransports();

                for(auto transport : transports){

                    if(transport->getTransportType() == wheelValues.first){
                        checkTransportMovement(_firstClick,_secondClick);
                        _runner->moveTransportWithSpinner(_firstClick->getCoordinates(),_secondClick->getCoordinates(),transport->getId(),wheelValues.second);

                        nextPlayer();
                        resetSelected();
                        break;
                    }
                }
            }catch(...){
                /*
                 * Catches Common::IllegalMoveException and std::exception because
                 * throwing our own IllegalMoveException didn't work for some reason
                 * that nobody (even the TAs) seemed to know.
                 */
                //nothing done, player tries again.
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
    // Set the selected hex-pointers back to nullptr

    _firstClick = nullptr;
    _secondClick = nullptr;
}

void GameBoard::nextPlayer()
{
    // Restore the actions of player ending their turn
    _runner->getCurrentPlayer()->setActionsLeft(3);

     unsigned int currentPlayer = _runner->currentPlayer();

    //If the current player is the last in turn change the player to first in the rotation
    if(currentPlayer == _players.size()){

        _gameState->changePlayerTurn(_players.at(0)->getPlayerId());

    }else{

        int counter = 0;

        int cPlayer = currentPlayer;

        //Set the next player as the player in turn
        for(auto player:_players){

            if(player->getPlayerId() == cPlayer){

                _gameState->changePlayerTurn(_players.at(counter+1)->getPlayerId());

            }

            ++counter;

        }
    }

}

bool GameBoard::winCheck()
{
    std::shared_ptr<Common::Hex> center;


    // Find the center of the map.
    for(auto tile : _hexMap){

        if((tile.first.x == 0) and (tile.first.y == 0) and (tile.first.z == 0)){

            center = tile.second;
        }

    }

    // If someone has made it to the center, they win.
    if(center->getPawnAmount() > 0){

        return true;
    }

    return false;
}

void GameBoard::checkActorMovement(Common::Hex* target)
{

    // Moving two actors to the same hex is not allowed

    if(target->getActors().size() > 0){
        throw std::exception();
    }
}

void GameBoard::checkTransportMovement(Common::Hex* origin,Common::Hex *target)
{
    if(target->getTransports().size()>0){
        throw std::exception();

    // Check if pawns in transport + pawns in target hex amount to more than 3.
    }else if(origin->getPawnAmount() + target->getPawnAmount() > 3){
        throw std::exception();
    }
}






bool Student::GameBoard::actorOnHex(std::shared_ptr<Common::Hex> selectedHex, std::string actorType)
{

    // Check if set type of actor is on the hex.
    for(std::string type : selectedHex->getActorTypes()){

        if(type == actorType){

            return true;
        }
    }

    return false;
}

bool Student::GameBoard::transportOnHex(std::shared_ptr<Common::Hex> selectedHex, std::string transportType)
{
    // Check if set type of transport is on the hex.
    for(auto transport : selectedHex->getTransports()){

        if(transport->getTransportType() == transportType){

            return true;
        }
    }

    return false;


}

}
