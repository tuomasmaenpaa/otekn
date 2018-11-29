/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */
#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "igamestate.hh"

/* Headerfile for Student::GameState class that inherits Common::IGameState.
 *
 * This class keeps track of the state of the game: who is in turn, who is next and
 * what phase it is.
 */

namespace Student {


class GameState : public Common::IGameState
{
public:


    // SEE IGAMESTATE FOR DOCUMENTATION OF FUNCTIONS BELOW.
    GameState();
    ~GameState();

    Common::GamePhase currentGamePhase() const;
    int currentPlayer() const;
    void changeGamePhase(Common::GamePhase nextPhase);
    void changePlayerTurn(int nextPlayer);
    // SEE IGAMESTATE FOR DOCUMENTATION OF FUNCTIONS ABOVE.
private:

    // Current phase of the game.
    Common::GamePhase _currentPhase = Common::MOVEMENT;

    // Player in turn.
    int _currentPlayer = 1;


};
}

#endif // GAMESTATE_HH
