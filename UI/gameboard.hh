/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */



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
#include "igamerunner.hh"


/* Headerfile for Student::GameBoard class that is derived from Common::IGameBoard.
 *
 * Class handles the logical components of the game and calls the graphic components
 * to do the same actions
 */


namespace Student {


class GameBoard : public Common::IGameBoard
{
public: 


    // SEE IGAMEBOARD FOR DOCUMENTATION OF FUNCTIONS BELOW.
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
    void movePawn(int pawnId, Common::CubeCoordinate target);
    void moveActor(int Id, Common::CubeCoordinate coord);
    void moveTransport(int Id, Common::CubeCoordinate coord);
    void removeTransport(int id);
    void removeActor(int);
    void addHex(std::shared_ptr<Common::Hex> newHex);
    void removePawn(int id);
    // SEE IGAMEBOARD FOR DOCUMENTATION OF FUNCTIONS ABOVE.


    /* Function gives gameboard a pointer to the scene where the graphical components
     * are.
     */
    void setScene(std::shared_ptr <QGraphicsScene> scene);

    /* Function gives gameboard a pointer to a Student::GameState
     * object that keeps track of games events.
     */
    void setGameState(std::shared_ptr<GameState> state);

    /*Function gives gameboard a pointer to the gameengine.
     */
    void setRunner(std::shared_ptr <Common::IGameRunner> runner);

    /* Function adds pointer to a player in to the _players vector
     */
    void addPlayer(std::shared_ptr<Player> player);

    /* Function returns a map of graphic hexes and their respective cubecoordinates.
     */
    std::map<Common::CubeCoordinate, std::shared_ptr<graphicHex>>& getGraphicHexMap();

    /* Function returns a vector that contains the cubecoordinates of
     * gameboard's corners.
     */
    std::vector<Common::CubeCoordinate> getCornerTiles();

    /* Function creates the pawns in the game
     */
    void createPawns();

    /* Functiom handles the logical side of clicks happening in MOVEMENT gamephase.
     */
    void setClickedMovement(std::shared_ptr<Common::Hex> selectedHex);


    /* Functiom handles the logical side of clicks happening in SINKING gamephase.
     */
    void setClickedSinking(std::shared_ptr<Common::Hex> selectedHex);


    /* Functiom handles the logical side of clicks happening in SPINNING gamephase.
     */
    void setClickedSpinning(std::shared_ptr<Common::Hex> selectedHex, std::pair<std::string,std::string> wheelValues);

    /* Function checks whether the player in turn has a pawn on a set hex.
     * Returns true if yes and false if not.
     */
    bool playersPawnOnHex(std::shared_ptr<Common::Hex> selectedHex);

    /* Function checks whether there is a given type of actor on set hex.
     */
    bool actorOnHex(std::shared_ptr<Common::Hex> selectedHex, std::string actorType);

    /* Function checks whether there is a given type of actor on set hex.
     */
    bool transportOnHex(std::shared_ptr<Common::Hex> selectedHex, std::string transportType);

    /* Function returns the id of the pawn that is on the hex.
     * Pre-Condition: There has to be a pawn on the source hex.
     */
    int getPawn(Common::Hex* source);

    /* Function sets the _firstClicked and _secondClicked pointer back to nullptr.
     */
    void resetSelected();

    /* Function changes the players turn in _gameState that keeps track of the games state.
     */
    void nextPlayer();

    /* Function checks if there is a winner in the game, in this case, someone made it to the
     * center of the map.
     */
    bool winCheck();

    /* Function checks if moving an actor to target hex can be allowed.
     * Returns true if allowed and false if not.
     */
    void checkActorMovement(Common::Hex *target);

    /* Function checks if moving a transport to target hex can be allowed.
     * Returns true if allowed and false if not.
     */
    void checkTransportMovement(Common::Hex *origin, Common::Hex* target);





private:

    // This map contains all the hexes with their cubecoordinate as the key
    std::map <Common::CubeCoordinate, std::shared_ptr<Common::Hex>> _hexMap;

    // This map contains all the graphichexes with their cubecoordinate as the key
    std::map <Common::CubeCoordinate, std::shared_ptr<graphicHex>> _graphicHexMap;

    // This map contains the pawns with their id as the key
    std::map <int,std::shared_ptr <Common::Pawn>> _pawnMap;

    // Contains actors and their id as the key
    std::map <int,std::shared_ptr<Common::Actor>> _actorMap;

    // This map contains all the transports and their ids as keys.
    std::map <int,std::shared_ptr<Common::Transport>> _transportMap;

    // This vector contains the players of the game
    std::vector<std::shared_ptr<Common::IPlayer>> _players;

    // A pointer to the GameState object
    std::shared_ptr<GameState> _gameState;

    // A pointer to the IGameRunner
    std::shared_ptr <Common::IGameRunner> _runner;


    /*
     * Pointers to the hexes that are clicked.
     * If the click was not legal, pointer will remain nullptr
     */
    Common::Hex* _firstClick = nullptr;
    Common::Hex* _secondClick = nullptr;

    // A pointer to the scene where the game is presented.
    std::shared_ptr <QGraphicsScene> _scene;

};
}
#endif // GAMEBOARD_HH
