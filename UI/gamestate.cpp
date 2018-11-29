/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */

#include "gamestate.hh"

/* The implementation of GameState functions.
 */
namespace Student {


GameState::GameState()
{

}

GameState::~GameState()
{

}

Common::GamePhase GameState::currentGamePhase() const
{   
    return _currentPhase;
}

int GameState::currentPlayer() const
{
    return _currentPlayer;
}

void GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    _currentPhase=nextPhase;
}

void GameState::changePlayerTurn(int nextPlayer)
{
    // Changing player also changes the phase to MOVEMENT.
    _currentPlayer = nextPlayer;
    changeGamePhase(Common::MOVEMENT);

}

}
